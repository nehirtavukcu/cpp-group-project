
#include "ACLManager.h"
#include <iostream>

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
}

void ACLManager::revokePermission(
    const std::string& username,
    const std::string& filename,
    Permission permission
) {
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

