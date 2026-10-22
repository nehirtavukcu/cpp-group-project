
#ifndef FILEACL_H
#define FILEACL_H

#include "Permission.h"
#include <map>
#include <set>
#include <string>

class FileACL {
private:
    std::string filename;
    std::map<std::string, std::set<Permission>> permissions;

public:
    FileACL();
    FileACL(const std::string& filename);

    std::string getFilename() const;

    void grantPermission(
        const std::string& username,
        Permission permission
    );

    void revokePermission(
        const std::string& username,
        Permission permission
    );

    bool hasPermission(
        const std::string& username,
        Permission permission
    ) const;

    void showPermissions() const;
};

#endif

