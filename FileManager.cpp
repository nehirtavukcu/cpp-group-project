
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

const string DATA_DIR = "acl_files";

bool FileManager::validFilename(const string& name) {
    if (name.size() < 5 ||
        name.substr(name.size() - 4) != ".txt") {
        return false;
    }

    for (unsigned char ch : name) {
        if (!isalnum(ch) && ch != '_' &&
            ch != '-' && ch != '.') {
            return false;
        }
    }

    if (name.find("..") != string::npos) {
        return false;
    }

    return true;
}

string FileManager::getPath(const string& filename) {
    return (fs::path(DATA_DIR) / filename).string();
}

void FileManager::createFile(const vector<string>& users) {
    string filename;

    cout << "Enter filename (e.g. report.txt): ";
    getline(cin, filename);

    if (!validFilename(filename)) {
        cout << "Invalid filename. Use a simple .txt filename.\n";
        return;
    }

    if (acl.count(filename)) {
        cout << "File is already registered.\n";
        return;
    }

    fs::create_directories(DATA_DIR);

    if (fs::exists(getPath(filename))) {
        cout << "A file with this name already exists on disk.\n";
        return;
    }

    ofstream file(getPath(filename));

    if (!file) {
        cout << "Could not create file.\n";
        return;
    }

    file << "New file: " << filename << '\n';
    file.close();

    for (const string& user : users) {
        acl[filename].permissions[user] = {};
    }

    cout << "File created successfully: " << filename << '\n';
}

void FileManager::listFiles() {
    cout << "\n--- REGISTERED FILES ---\n";

    if (acl.empty()) {
        cout << "No files registered.\n";
        return;
    }

    for (const auto& entry : acl) {
        cout << "- " << entry.first << '\n';
    }
}
