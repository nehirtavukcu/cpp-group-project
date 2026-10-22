#include <iostream>
#include "Permission.h"
#include "FileACL.h"
#include "AuditLogger.h"
#include "ACLManager.h"

int main() {
    ACLManager manager;

    manager.addFile("report.txt");
    manager.addFile("notes.txt");

    manager.grantPermission(
        "Ali", "report.txt", Permission::Read
    );

    manager.grantPermission(
        "Ali", "report.txt", Permission::Write
    );

    manager.grantPermission(
        "Ayse", "notes.txt", Permission::Read
    );

    manager.showACL("report.txt");
    manager.showACL("notes.txt");

    std::cout << "\n--- Permission Check ---\n";

    if (manager.hasPermission(
        "Ali", "report.txt", Permission::Read)) {
        std::cout << "Ali can read report.txt\n";
    }
    else {
        std::cout << "Ali cannot read report.txt\n";
    }

    manager.revokePermission(
        "Ali", "report.txt", Permission::Write
    );

    std::cout << "\n--- After Revoking Write Permission ---\n";
    manager.showACL("report.txt");

    manager.showAuditLogs();

    return 0;
}
