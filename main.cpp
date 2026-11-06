#include <iostream>
#include <string>
#include "Permission.h"
#include "FileACL.h"
#include "AuditLogger.h"
#include "ACLManager.h"
#include "User.h" 

int main() {
    ACLManager manager;

    std::string name1, name2;

    std::cout << "Enter the first username: ";
    std::getline(std::cin, name1);

    std::cout << "Enter the second username: ";
    std::getline(std::cin, name2);

    User user1(name1);
    User user2(name2);

    std::cout << "\nUsers registered successfully:\n";
    user1.displayInfo();
    user2.displayInfo();

    manager.addFile("report.txt");
    manager.addFile("notes.txt");

    manager.grantPermission(
        user1.getName(), "report.txt", Permission::Read
    );

    manager.grantPermission(
        user1.getName(), "report.txt", Permission::Write
    );

    manager.grantPermission(
        user2.getName(), "notes.txt", Permission::Read
    );

    manager.showACL("report.txt");
    manager.showACL("notes.txt");

    std::cout << "\n--- Permission Check ---\n";

    if (manager.hasPermission(user1.getName(), "report.txt", Permission::Read)) {
        std::cout << user1.getName() << " can read report.txt\n";
    }
    else {
        std::cout << user1.getName() << " cannot read report.txt\n";
    }

    manager.revokePermission(
        user1.getName(), "report.txt", Permission::Write
    );

    std::cout << "\n--- After Revoking Write Permission ---\n";
    manager.showACL("report.txt");

    manager.showAuditLogs();

    return 0;
}
