void readFile() {
    string username, filename;

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter filename: ";
    getline(cin, filename);

    if (!userExists(username) || !acl.count(filename)) {
        cout << "Unknown user or unregistered file.\n";
        logEvent("DENIED Read: invalid user/file");
        return;
    }

    if (!hasPermission(username, filename, "Read")) {
        cout << "ACCESS DENIED: Read permission required.\n";
        logEvent("DENIED Read: " + username + " -> " + filename);
        return;
    }

    ifstream file(getPath(filename));

    if (!file) {
        cout << "Could not open file.\n";
        return;
    }

    cout << "\n--- FILE CONTENT ---\n";
    string line;

    while (getline(file, line))
        cout << line << '\n';

    logEvent("GRANTED Read: " + username + " -> " + filename);
}

void writeFile() {
    string username, filename;

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter filename: ";
    getline(cin, filename);

    if (!userExists(username) || !acl.count(filename)) {
        cout << "Unknown user or unregistered file.\n";
        logEvent("DENIED Write: invalid user/file");
        return;
    }

    if (!hasPermission(username, filename, "Write")) {
        cout << "ACCESS DENIED: Write permission required.\n";
        logEvent("DENIED Write: " + username + " -> " + filename);
        return;
    }

    cout << "Enter one line to append to the file: ";
    string text;
    getline(cin, text);

    ofstream file(getPath(filename), ios::app);

    if (!file) {
        cout << "Could not open file for writing.\n";
        return;
    }

    file << text << '\n';
    file.close();

    logEvent("GRANTED Write: " + username + " -> " + filename);
}

void executeCheck() {
    string username, filename;

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter filename: ";
    getline(cin, filename);

    if (!userExists(username) || !acl.count(filename)) {
        cout << "Unknown user or unregistered file.\n";
        logEvent("DENIED Execute: invalid user/file");
        return;
    }

    if (!hasPermission(username, filename, "Execute")) {
        cout << "ACCESS DENIED: Execute permission required.\n";
        logEvent("DENIED Execute: " + username + " -> " + filename);
        return;
    }

    cout << "ACCESS GRANTED: Execute permission verified.\n";
    cout << "Execution is simulated; no program is launched.\n";

    logEvent("GRANTED Execute check: " +
             username + " -> " + filename);
}
void showMenu() {
    cout << "\n========== ACL MANAGER ==========\n";
    cout << "1.  List users\n";
    cout << "2.  Add user\n";
    cout << "3.  List files\n";
    cout << "4.  Create file\n";
    cout << "5.  Show file ACL\n";
    cout << "6.  Grant permission\n";
    cout << "7.  Revoke permission\n";
    cout << "8.  Read file\n";
    cout << "9.  Write to file\n";
    cout << "10. Check Execute permission\n";
    cout << "11. Show audit log\n";
    cout << "0.  Exit\n";
    cout << "Select option: ";
}

void setupDemo() {
    fs::create_directories(DATA_DIR);

    vector<string> demoFiles = {"report.txt", "notes.txt"};

    for (const string& filename : demoFiles) {
        string path = getPath(filename);

        if (!fs::exists(path)) {
            ofstream file(path);
            if (file)
                file << "Sample content in " << filename << '\n';
        }

        for (const string& user : users)
            acl[filename].permissions[user] = {};
    }

    acl["report.txt"].permissions["Elif"]    = {"Read", "Write"};
    acl["report.txt"].permissions["NehirK"]  = {"Read"};
    acl["report.txt"].permissions["NehirT"]  = {};
    acl["report.txt"].permissions["Yasemin"] = {};

    acl["notes.txt"].permissions["Elif"]    = {"Read", "Write", "Execute"};
    acl["notes.txt"].permissions["NehirK"]  = {"Read", "Write"};
    acl["notes.txt"].permissions["NehirT"]  = {"Read"};
    acl["notes.txt"].permissions["Yasemin"] = {};
}

int main() {
    try {
        setupDemo();
    } catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << '\n';
        return 1;
    }

    string choice;

    while (true) {
        showMenu();
        if (!getline(cin, choice)) {
            cout << "\nInput closed. Exiting.\n";
            break;
        }
        try {
            if (choice == "1") listUsers();
            else if (choice == "2") addUser();
            else if (choice == "3") listFiles();
            else if (choice == "4") createFile();
            else if (choice == "5") showACL();
            else if (choice == "6") changePermission(true);
            else if (choice == "7") changePermission(false);
            else if (choice == "8") readFile();
            else if (choice == "9") writeFile();
            else if (choice == "10") executeCheck();
            else if (choice == "11") showAuditLog();
            else if (choice == "0") {
                cout << "Exiting ACL Manager.\n";
                break;
            } else {
                cout << "Invalid option. Try again.\n";
            }
        } catch (const fs::filesystem_error& e) {
            cout << "Filesystem error: " << e.what() << '\n';
        }
    }

    return 0;
}
