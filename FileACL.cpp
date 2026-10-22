
#include "FileACL.h"
#include <iostream>

FileACL::FileACL() : filename("") {}

FileACL::FileACL(const std::string& filename)
    : filename(filename) {}

std::string FileACL::getFilename() const {
    return filename;
}

void FileACL::grantPermission(
    const std::string& username,
    Permission permission
) {
    permissions[username].insert(permission);
}

void FileACL::revokePermission(
    const std::string& username,
    Permission permission
) {
    auto it = permissions.find(username);

    if (it != permissions.end()) {
        it->second.erase(permission);
    }
}

bool FileACL::hasPermission(
    const std::string& username,
    Permission permission
) const {
    auto it = permissions.find(username);

    if (it == permissions.end()) {
        return false;
    }

    return it->second.count(permission) > 0;
}

void FileACL::showPermissions() const {
    std::cout << "\nFile: " << filename << "\n";

    for (const auto& user : permissions) {
        std::cout << user.first << ": ";

        for (Permission permission : user.second) {
            std::cout << permissionToString(permission)
                << " ";
        }

        std::cout << "\n";
    }
}
