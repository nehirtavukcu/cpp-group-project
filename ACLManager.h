#ifndef ACLMANAGER_H
#define ACLMANAGER_H

#include "FileACL.h"
#include "AuditLogger.h"
#include "User.h"
#include "Permission.h"
#include <map>
#include <string>

class ACLManager {
private:
    std::map<std::string, FileACL> files;
    std::map<std::string, User> users; // Kayıtlı kullanıcılar
    AuditLogger auditLogger;

public:
    // Kullanıcı Yönetimi
    void addUser(const std::string& username);
    void removeUser(const std::string& username);
    bool userExists(const std::string& username) const;
    void showUsers() const;

    // Dosya ve İzin Yönetimi
    void addFile(const std::string& filename);

    void grantPermission(
        const std::string& username,
        const std::string& filename,
        Permission permission
    );

    void revokePermission(
        const std::string& username,
        const std::string& filename,
        Permission permission
    );

    bool hasPermission(
        const std::string& username,
        const std::string& filename,
        Permission permission
    ) const;

    void showACL(const std::string& filename) const;
    void showAuditLogs() const;
};

#endif
