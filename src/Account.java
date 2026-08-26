import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Account implements Serializable {
    private final String accountNumber;
    private final String ownerName;
    private double balance;
    private final List<Transaction> transactions = new ArrayList<>();

    public Account(String accountNumber, String ownerName, double openingBalance) {
        this.accountNumber = accountNumber;
        this.ownerName = ownerName;
        this.balance = openingBalance;
        if (openingBalance > 0) {
            addTransaction("Opening balance", openingBalance);
        }
    }

    public void deposit(double amount) {
        if (amount <= 0) throw new IllegalArgumentException("Amount must be greater than 0.");
        balance += amount;
        addTransaction("Deposit", amount);
    }

    public void withdraw(double amount) {
        if (amount <= 0) throw new IllegalArgumentException("Amount must be greater than 0.");
        if (amount > balance) throw new IllegalArgumentException("Insufficient balance.");
        balance -= amount;
        addTransaction("Withdrawal", -amount);
    }

    public void addTransaction(String description, double amount) {
        transactions.add(new Transaction(description, amount));
    }

    public String getAccountNumber() { return accountNumber; }
    public String getOwnerName() { return ownerName; }
    public double getBalance() { return balance; }
    public List<Transaction> getTransactions() { return transactions; }
}
