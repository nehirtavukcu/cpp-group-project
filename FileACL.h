
#ifndef FILEACL_H
#define FILEACL_H

#include <string>
#include <map>
#include <set>

using namespace std;

class FileACL {
public:
    map<string, set<string>> permissions;
};

#endif
