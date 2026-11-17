#include <iostream>
#include <string>
#include <limits>
#include "Permission.h"
#include "FileACL.h"
#include "AuditLogger.h"
#include "ACLManager.h"
#include "User.h"

Permission selectPermission() {
    int permChoice;
    std::cout << "Select Permission (1: Read, 2: Write, 3: Execute): ";
    std::cin >> permChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (permChoice) {
        case 1: return Permission::Read;
        case 2: return Permission::Write;
        case 3: return Permission::Execute;
        default:
            std::cout << "Invalid choice, defaulting to Read.\n";
            return Permission::Read;
    }
}

void userMenu(ACLManager& manager) {
    int subChoice;
    std::string username;

    std::cout << "\n--- User Management ---\n";
    std::cout << "1. Add User\n";
    std::cout << "2. Remove User\n";
    std::cout << "3. List Users\n";
    std::cout << "Choice: ";
    std::cin >> subChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
            std::cout << "Invalid option!\n";
            break;
    }
}

int main() {
    ACLManager manager;

    // Başlangıç için örnek dosyalar
    manager.addFile("report.txt");
    manager.addFile("notes.txt");

    int choice = -1;
    std::string username, filename;

    while (choice != 0) {
        std::cout << "\n==============================\n";
        std::cout << "      ACL SYSTEM MENU\n";
        std::cout << "==============================\n";
        std::cout << "1. User Management (Add / Remove User)\n";
        std::cout << "2. Add File\n";
        std::cout << "3. Grant Permission\n";
        std::cout << "4. Revoke Permission\n";
        std::cout << "5. Show File ACL\n";
        std::cout << "6. Show Audit Logs\n";
        std::cout << "0. Exit\n";
        std::cout << "Select an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid number!\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                userMenu(manager);
                break;

            case 2:
                std::cout << "Enter filename to add: ";
                std::getline(std::cin, filename);
                manager.addFile(filename);
                std::cout << "File processed.\n";
                break;

            case 3:
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter filename: ";
                std::getline(std::cin, filename);
                manager.grantPermission(username, filename, selectPermission());
                break;

            case 4:
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter filename: ";
                std::getline(std::cin, filename);
                manager.revokePermission(username, filename, selectPermission());
                break;

            case 5:
                std::cout << "Enter filename: ";
                std::getline(std::cin, filename);
                manager.showACL(filename);
                break;

            case 6:
                manager.showAuditLogs();
                break;

            case 0:
                std::cout << "Exiting program...\n";
                break;

            default:
                std::cout << "Invalid option! Try again.\n";
                break;
        }
    }

    return 0;
}
