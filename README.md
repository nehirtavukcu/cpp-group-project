# Access Control List (ACL) File Management System
COME 361 Operating Systems Term Project

A role and user-based Access Control List (ACL) simulation developed in C++17. The system models file permission enforcement (Read, Write, Execute), user identity handling, and tamper-evident audit trail logging.

## 👥 Project Team & Responsibilities
* *Nehir T.:* User & File Management Module (addUser, listUsers, createFile, validFilename, getPath)
* *Elif:* ACL Engine & Permission Matrix (hasPermission, changePermission, showACL, choosePermission)
* *Nehir K.:* File I/O Interceptors, Security Audit Trail & CLI Application Core (readFile, writeFile, executeCheck, logEvent, showAuditLog, showMenu, main)

*Course Instructor:* Yasemin Karagül

## 🛠️ Technical Specifications
* *Language Standard:* C++17 (std::filesystem)
* *Supported Compilers:* GCC (MinGW) / MSVC (Visual Studio 2022)

## 🚀 How to Compile and Run
### Using MSVC:
```cmd
cl /std:c++17 /EHsc main.cpp
main.exe
