#include "ACLManager.h"
#include <iostream>

using namespace std;

ACLManager::ACLManager(SharedData& sharedData)
    : data(sharedData) {
}

bool ACLManager::hasPermission(
    const string& username,
    const string& filename,
    const string& permission
) const {
    auto fileIt = data.acl.find(filename);

    if (fileIt == data.acl.end()) {
        return false;
    }

    auto userIt = fileIt->second.permissions.find(username);

    if (userIt == fileIt->second.permissions.end()) {
        return false;
    }

    return userIt->second.count(permission) > 0;
}

string ACLManager::choosePermission() {
    cout << "\nSelect permission:\n";
    cout << "1. Read\n";
    cout << "2. Write\n";
    cout << "3. Execute\n";
    cout << "Choice: ";

    string choice;
    getline(cin, choice);

    if (choice == "1") return "Read";
    if (choice == "2") return "Write";
    if (choice == "3") return "Execute";

    return "";
}

void ACLManager::showACL() {
    string filename;

    cout << "Enter filename: ";
    getline(cin, filename);

    auto fileIt = data.acl.find(filename);

    if (fileIt == data.acl.end()) {
        cout << "File is not registered in the ACL.\n";
        return;
    }

    cout << "\n--- ACL for " << filename << " ---\n";

    for (const auto& entry : fileIt->second.permissions) {
        cout << entry.first << ": ";

        if (entry.second.empty()) {
            cout << "No permissions";
        }
        else {
            for (const string& permission : entry.second) {
                cout << permission << " ";
            }
        }

        cout << '\n';
    }
}

void ACLManager::changePermission(bool grant) {
    string filename;
    string username;

    cout << "Enter filename: ";
    getline(cin, filename);

    auto fileIt = data.acl.find(filename);

    if (fileIt == data.acl.end()) {
        cout << "Unknown file.\n";
        return;
    }

    cout << "Enter username: ";
    getline(cin, username);

    auto userIt = fileIt->second.permissions.find(username);

    if (userIt == fileIt->second.permissions.end()) {
        cout << "User is not registered for this file.\n";
        return;
    }

    string permission = choosePermission();

    if (permission.empty()) {
        cout << "Invalid permission choice.\n";
        return;
    }

    if (grant) {
        auto result = userIt->second.insert(permission);

        if (result.second) {
            cout << "Permission granted: "
                << permission << " to " << username << ".\n";

            data.auditLog.push_back(
                "Granted " + permission + " to " +
                username + " for " + filename
            );
        }
        else {
            cout << "The user already has this permission.\n";
        }
    }
    else {
        if (userIt->second.erase(permission) == 0) {
            cout << "The user does not have this permission.\n";
            return;
        }

        cout << "Permission revoked: "
            << permission << " from " << username << ".\n";

        data.auditLog.push_back(
            "Revoked " + permission + " from " +
            username + " for " + filename
        );
    }
}

void ACLManager::setupDemoPermissions() {
    data.acl["report.txt"].permissions["Ali"] =
    { "Read", "Write" };

    data.acl["report.txt"].permissions["Ayse"] =
    { "Read" };

    data.acl["report.txt"].permissions["Mehmet"] = {};

    data.acl["notes.txt"].permissions["Ali"] =
    { "Read", "Write", "Execute" };

    data.acl["notes.txt"].permissions["Ayse"] =
    { "Read", "Write" };

    data.acl["notes.txt"].permissions["Mehmet"] =
    { "Read" };
}