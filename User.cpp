#include "User.h"
#include <iostream>

User::User(const std::string& userName) : name(userName) {}

std::string User::getName() const {
    return name;
}

void User::displayInfo() const {
    std::cout << "\n--------------------------" << std::endl;
    std::cout << "User Name: " << name << std::endl;
    std::cout << "--------------------------" << std::endl;
}
