#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct FileACL {
    map<string, set<string>> permissions;
};

struct SharedData {
    vector<string> users = { "Ali", "Ayse", "Mehmet" };
    map<string, FileACL> acl;
    vector<string> auditLog;
};
