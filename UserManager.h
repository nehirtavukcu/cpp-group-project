
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "FileACL.h"

using namespace std;

class UserManager {
public:
    vector<string> users = {"Elif", "NehirK", "NehirT", "Yasemin"};

    bool userExists(const string& name);
    void addUser(map<string, FileACL>& acl);
    void listUsers();
};

#endif
