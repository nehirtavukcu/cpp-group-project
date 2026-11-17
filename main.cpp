#include <iostream>
#include <string>
#include <limits>
#include "Permission.h"
#include "FileACL.h"
#include "AuditLogger.h"
#include "ACLManager.h"
#include "User.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Permission selectPermission() {
    int permChoice = 0;
    while (true) {
        std::cout << "Select Permission:\n";
        std::cout << "  1. Read\n";
        std::cout << "  2. Write\n";
        std::cout << "  3. Execute\n";
        std::cout << "Choice: ";

        if (!(std::cin >> permChoice)) {
            std::cout << "Invalid input! Please enter a number (1-3).\n";
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (permChoice) {
        case 1: return Permission::Read;
        case 2: return Permission::Write;
        case 3: return Permission::Execute;
        default:
            std::cout << "Invalid selection! Please choose 1, 2, or 3.\n";
        }
    }
}

void userMenu(ACLManager& manager) {
    int subChoice = 0;
    while (true) {
        std::cout << "\n--- User Management ---\n";
        std::cout << "1. Add User\n";
        std::cout << "2. Remove User\n";
        std::cout << "3. List Users\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choice: ";

        if (!(std::cin >> subChoice)) {
            std::cout << "Invalid input! Please enter a number.\n";
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (subChoice == 0) {
            break;
        }

        std::string username;
        switch (subChoice) {
        case 1:
            std::cout << "Enter username to add: ";
            std::getline(std::cin, username);
            manager.addUser(username);
            break;

        case 2:
            std::cout << "Enter username to remove: ";
            std::getline(std::cin, username);
            manager.removeUser(username);
            break;

        case 3:
            manager.showUsers();
            break;

        default:
            std::cout << "Invalid option! Please try again.\n";
        }
    }
}

int main() {
    ACLManager manager;
    int choice = -1;

    std::cout << "=========================================\n";
    std::cout << "   OS-ACL Access Control List Manager    \n";
    std::cout << "=========================================\n";

    while (true) {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. User Management (Add / Remove / List)\n";
        std::cout << "2. Add File\n";
        std::cout << "3. Grant Permission\n";
        std::cout << "4. Revoke Permission\n";
        std::cout << "5. Check Permission\n";
        std::cout << "6. Show File ACL\n";
        std::cout << "7. Show Audit Logs\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input! Please enter a number.\n";
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 0) {
            std::cout << "Exiting program...\n";
            break;
        }

        std::string username, filename;

        switch (choice) {
        case 1:
            userMenu(manager);
            break;

        case 2:
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            if (filename.empty()) {
                std::cout << "Filename cannot be empty!\n";
            }
            else {
                manager.addFile(filename);
                std::cout << "File '" << filename << "' processed.\n";
            }
            break;

        case 3: {
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            Permission perm = selectPermission();
            manager.grantPermission(username, filename, perm);
            break;
        }

        case 4: {
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            Permission perm = selectPermission();
            manager.revokePermission(username, filename, perm);
            break;
        }

        case 5: {
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            Permission perm = selectPermission();

            if (manager.hasPermission(username, filename, perm)) {
                std::cout << "[ACCESS GRANTED] " << username << " has "
                    << permissionToString(perm) << " permission on " << filename << ".\n";
            }
            else {
                std::cout << "[ACCESS DENIED] " << username << " does NOT have "
                    << permissionToString(perm) << " permission on " << filename << ".\n";
            }
            break;
        }

        case 6:
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            manager.showACL(filename);
            break;

        case 7:
            manager.showAuditLogs();
            break;

        default:
            std::cout << "Invalid choice! Please select a valid option.\n";
        }
    }

    return 0;
}
    }

    return 0;
}
