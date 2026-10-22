
#ifndef ACLMANAGER_H
#define ACLMANAGER_H

#include "FileACL.h"
#include "AuditLogger.h"
#include <map>
#include <string>

class ACLManager {
private:
    std::map<std::string, FileACL> files;
    AuditLogger auditLogger;

public:
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
