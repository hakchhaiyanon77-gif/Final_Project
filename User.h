#ifndef USER_LIBRARY
#define USER_LIBRARY

// {...}
class Person {
private:
    string username;
    string password;
    string fullName;

public:
    Person(const string& username = "",
           const string& password = "",
           const string& fullName = "")
        : username(username),
          password(password),
          fullName(fullName) {}

    virtual ~Person() = default;

    const string& getUsername() const {
        return username;
    }

    const string& getFullName() const {
        return fullName;
    }

    const string& getPassword() const {
        return password;
    }

    void setFullName(const string& name) {
        fullName = name;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    bool checkPassword(const string& input) const {
        return password == input;
    }

    virtual string getRole() const = 0;
    virtual void displayInfo() const = 0;
};

#endif