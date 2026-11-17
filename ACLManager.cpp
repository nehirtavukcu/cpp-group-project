
#include "ACLManager.h"
#include <iostream>

void ACLManager::addUser(const std::string& username) {
    if (username.empty()) {
        std::cout << "Username cannot be empty!\n";
        return;
    }

    if (users.find(username) != users.end()) {
        std::cout << "User '" << username << "' already exists!\n";
        return;
    }

    users.emplace(username, User(username));
    auditLogger.log("User added: " + username);
    std::cout << "User '" << username << "' added successfully.\n";
}

void ACLManager::removeUser(const std::string& username) {
    auto it = users.find(username);

    if (it == users.end()) {
        std::cout << "User '" << username << "' not found!\n";
        return;
    }

    // Kullanıcının tüm dosyalardaki izinlerini temizle
    for (auto& filePair : files) {
        filePair.second.removeUser(username);
    }

    users.erase(it);
    auditLogger.log("User removed: " + username);
    std::cout << "User '" << username << "' and their permissions removed.\n";
}

bool ACLManager::userExists(const std::string& username) const {
    return users.find(username) != users.end();
}

void ACLManager::showUsers() const {
    std::cout << "\n--- Registered Users ---\n";
    if (users.empty()) {
        std::cout << "No users registered.\n";
        return;
    }
    for (const auto& pair : users) {
        pair.second.displayInfo();
    }
}

void ACLManager::addFile(const std::string& filename) {
    if (files.find(filename) == files.end()) {
        files.emplace(filename, FileACL(filename));
        auditLogger.log("File added: " + filename);
    }
}

void ACLManager::grantPermission(
    const std::string& username,
    const std::string& filename,
    Permission permission
) {
    if (!userExists(username)) {
        std::cout << "User '" << username << "' is not registered!\n";
        return;
    }

    auto it = files.find(filename);
    if (it == files.end()) {
        std::cout << "File not found!\n";
        return;
    }

    it->second.grantPermission(username, permission);

    auditLogger.log(
        username + " received " +
        permissionToString(permission) +
        " permission for " + filename
    );
    std::cout << "Permission granted.\n";
}

void ACLManager::revokePermission(
    const std::string& username,
    const std::string& filename,
    Permission permission
) {
    if (!userExists(username)) {
        std::cout << "User '" << username << "' is not registered!\n";
        return;
    }

    auto it = files.find(filename);
    if (it == files.end()) {
        std::cout << "File not found!\n";
        return;
    }

    it->second.revokePermission(username, permission);

    auditLogger.log(
        username + " lost " +
        permissionToString(permission) +
        " permission for " + filename
    );
    std::cout << "Permission revoked.\n";
}

bool ACLManager::hasPermission(
    const std::string& username,
    const std::string& filename,
    Permission permission
) const {
    auto it = files.find(filename);
    if (it == files.end()) {
        return false;
    }
    return it->second.hasPermission(username, permission);
}

void ACLManager::showACL(const std::string& filename) const {
    auto it = files.find(filename);
    if (it == files.end()) {
        std::cout << "File not found!\n";
        return;
    }
    it->second.showPermissions();
}

void ACLManager::showAuditLogs() const {
    auditLogger.showLogs();
}

