
#include "UserManager.h"
#include <iostream>

using namespace std;

bool UserManager::userExists(const string& name) {
    for (const string& user : users) {
        if (user == name) {
            return true;
        }
    }

    return false;
}

void UserManager::addUser(map<string, FileACL>& acl) {
    string name;

    cout << "Enter new username: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "Username cannot be empty.\n";
        return;
    }

    if (userExists(name)) {
        cout << "User already exists.\n";
        return;
    }

    users.push_back(name);

    for (auto& fileEntry : acl) {
        fileEntry.second.permissions[name] = {};
    }

    cout << "User added successfully: " << name << '\n';
}

void UserManager::listUsers() {
    cout << "\n--- USERS ---\n";

    if (users.empty()) {
        cout << "No users found.\n";
        return;
    }

    for (const string& user : users) {
        cout << "- " << user << '\n';
    }
}
