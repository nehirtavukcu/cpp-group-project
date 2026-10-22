
#include "Permission.h"

std::string permissionToString(Permission permission) {
    switch (permission) {
    case Permission::Read:
        return "read";

    case Permission::Write:
        return "write";

    case Permission::Execute:
        return "execute";

    default:
        return "unknown";
    }
}

