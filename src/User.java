import java.io.Serializable;

public class User implements Serializable {
    private final String username;
    private String password;
    private final String fullName;
    private final boolean admin;
    private final Account account;

    public User(String username, String password, String fullName, boolean admin, Account account) {
        this.username = username;
        this.password = password;
        this.fullName = fullName;
        this.admin = admin;
        this.account = account;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public String getUsername() { return username; }
    public String getFullName() { return fullName; }
    public boolean isAdmin() { return admin; }
    public Account getAccount() { return account; }
    public void setPassword(String password) { this.password = password; }
}
