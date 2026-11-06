#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string name;

public:
    
    User(const std::string& userName);

    std::string getName() const;

    void displayInfo() const;
};

#endif 
