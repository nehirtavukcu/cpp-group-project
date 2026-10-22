
#ifndef PERMISSION_H
#define PERMISSION_H

#include <string>

enum class Permission {
    Read,
    Write,
    Execute
};

std::string permissionToString(Permission permission);

#endif
