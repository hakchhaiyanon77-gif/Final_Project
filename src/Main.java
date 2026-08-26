import java.util.Scanner;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    private static final Bank bank = new Bank();

    public static void main(String[] args) {
        bank.load();

        while (true) {
            System.out.println("\n==============================");
            System.out.println("      SIMPLE BANK SYSTEM");
            System.out.println("==============================");
            System.out.println("1. Login");
            System.out.println("2. Exit");
            System.out.print("Choose: ");

            String choice = scanner.nextLine().trim();

            if (choice.equals("1")) {
                User user = login();
                if (user != null) {
                    if (user.isAdmin()) adminMenu(user);
                    else userMenu(user);
                }
            } else if (choice.equals("2")) {
                bank.save();
                System.out.println("Goodbye!");
                break;
            } else {
                System.out.println("Invalid choice.");
            }
        }
    }

    private static User login() {
        System.out.print("Username: ");
        String username = scanner.nextLine().trim();
        System.out.print("Password: ");
        String password = scanner.nextLine();

        User user = bank.login(username, password);
        if (user == null) {
            System.out.println("Login failed.");
        } else {
            System.out.println("Welcome, " + user.getFullName() + "!");
        }
        return user;
    }

    private static void userMenu(User user) {
        while (true) {
            System.out.println("\n--- USER MENU ---");
            System.out.println("1. My account");
            System.out.println("2. Deposit");
            System.out.println("3. Withdraw");
            System.out.println("4. Transfer");
            System.out.println("5. Transaction history");
            System.out.println("6. Change password");
            System.out.println("7. Logout");
            System.out.print("Choose: ");

            String choice = scanner.nextLine().trim();

            try {
                switch (choice) {
                    case "1" -> showAccount(user);
                    case "2" -> deposit(user);
                    case "3" -> withdraw(user);
                    case "4" -> transfer(user);
                    case "5" -> showHistory(user);
                    case "6" -> changePassword(user);
                    case "7" -> { return; }
                    default -> System.out.println("Invalid choice.");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private static void adminMenu(User admin) {
        while (true) {
            System.out.println("\n--- ADMIN MENU ---");
            System.out.println("1. View all accounts");
            System.out.println("2. View account");
            System.out.println("3. Logout");
            System.out.print("Choose: ");

            String choice = scanner.nextLine().trim();

            if (choice.equals("1")) {
                bank.printAllAccounts();
            } else if (choice.equals("2")) {
                System.out.print("Account number: ");
                Account account = bank.findAccount(scanner.nextLine().trim());
                if (account == null) System.out.println("Account not found.");
                else printAccount(account);
            } else if (choice.equals("3")) {
                return;
            } else {
                System.out.println("Invalid choice.");
            }
        }
    }

    private static void showAccount(User user) {
        printAccount(user.getAccount());
    }

    private static void printAccount(Account a) {
        System.out.println("\nAccount number: " + a.getAccountNumber());
        System.out.println("Owner: " + a.getOwnerName());
        System.out.printf("Balance: $%.2f%n", a.getBalance());
    }

    private static double amount() {
        System.out.print("Amount: $");
        double value = Double.parseDouble(scanner.nextLine().trim());
        if (value <= 0) throw new IllegalArgumentException("Amount must be greater than 0.");
        return value;
    }

    private static void deposit(User user) {
        double amount = amount();
        user.getAccount().deposit(amount);
        bank.save();
        System.out.printf("Deposited $%.2f%n", amount);
    }

    private static void withdraw(User user) {
        double amount = amount();
        user.getAccount().withdraw(amount);
        bank.save();
        System.out.printf("Withdrawn $%.2f%n", amount);
    }

    private static void transfer(User user) {
        System.out.print("Receiver account number: ");
        String receiverNumber = scanner.nextLine().trim();
        Account receiver = bank.findAccount(receiverNumber);

        if (receiver == null) {
            System.out.println("Receiver not found.");
            return;
        }

        if (receiver == user.getAccount()) {
            System.out.println("You cannot transfer to yourself.");
            return;
        }

        double amount = amount();
        user.getAccount().withdraw(amount);
        receiver.deposit(amount);
        user.getAccount().addTransaction("Transfer to " + receiver.getAccountNumber(), -amount);
        receiver.addTransaction("Transfer from " + user.getAccount().getAccountNumber(), amount);
        bank.save();

        System.out.printf("Transferred $%.2f to %s%n", amount, receiver.getOwnerName());
    }

    private static void showHistory(User user) {
        System.out.println("\n--- TRANSACTION HISTORY ---");
        if (user.getAccount().getTransactions().isEmpty()) {
            System.out.println("No transactions.");
            return;
        }
        for (Transaction t : user.getAccount().getTransactions()) {
            System.out.println(t);
        }
    }

    private static void changePassword(User user) {
        System.out.print("New password: ");
        String password = scanner.nextLine();
        if (password.length() < 4) {
            System.out.println("Password must contain at least 4 characters.");
            return;
        }
        user.setPassword(password);
        bank.save();
        System.out.println("Password changed.");
    }
}
