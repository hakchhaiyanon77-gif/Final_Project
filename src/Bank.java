import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Bank {
    private final List<User> users = new ArrayList<>();
    private final String dataFile = "data/accounts.dat";

    public Bank() {
        createDemoData();
    }

    private void createDemoData() {
        Account a1 = new Account("100001", "Alice Johnson", 1500);
        Account a2 = new Account("100002", "Bob Smith", 900);
        Account a3 = new Account("100003", "Charlie Brown", 2500);

        users.add(new User("admin", "admin123", "Bank Administrator", true, null));
        users.add(new User("alice", "1234", "Alice Johnson", false, a1));
        users.add(new User("bob", "1234", "Bob Smith", false, a2));
        users.add(new User("charlie", "1234", "Charlie Brown", false, a3));
    }

    public User login(String username, String password) {
        for (User user : users) {
            if (user.getUsername().equals(username) && user.checkPassword(password)) {
                return user;
            }
        }
        return null;
    }

    public Account findAccount(String number) {
        for (User user : users) {
            if (!user.isAdmin() && user.getAccount().getAccountNumber().equals(number)) {
                return user.getAccount();
            }
        }
        return null;
    }

    public void printAllAccounts() {
        System.out.println("\n--- ALL ACCOUNTS ---");
        for (User user : users) {
            if (!user.isAdmin()) {
                Account a = user.getAccount();
                System.out.printf("%s | %-18s | $%.2f%n",
                        a.getAccountNumber(), a.getOwnerName(), a.getBalance());
            }
        }
    }

    public void save() {
        try {
            File file = new File(dataFile);
            File parent = file.getParentFile();
            if (parent != null) parent.mkdirs();

            try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(file))) {
                out.writeObject(users);
            }
        } catch (IOException e) {
            System.out.println("Could not save data: " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    public void load() {
        File file = new File(dataFile);
        if (!file.exists()) return;

        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(file))) {
            List<User> loaded = (List<User>) in.readObject();
            users.clear();
            users.addAll(loaded);
        } catch (Exception e) {
            System.out.println("Could not load saved data. Starting with demo data.");
            users.clear();
            createDemoData();
        }
    }
}
