import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Transaction implements Serializable {
    private final LocalDateTime dateTime;
    private final String description;
    private final double amount;

    public Transaction(String description, double amount) {
        this.dateTime = LocalDateTime.now();
        this.description = description;
        this.amount = amount;
    }

    @Override
    public String toString() {
        String sign = amount >= 0 ? "+" : "";
        return dateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm"))
                + " | " + description + " | " + sign + String.format("$%.2f", amount);
    }
}
