#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type, unsigned long long password_);
    virtual ~User();

    double getBalance() const;
    unsigned long long getPassword() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);

private:
    std::string name_;
    double balance_;
    int type_;
    unsigned long long password_;
};
#endif
