
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "FileACL.h"

using namespace std;

class FileManager {
public:
    map<string, FileACL> acl;

    bool validFilename(const string& name);
    string getPath(const string& filename);
    void createFile(const vector<string>& users);
    void listFiles();
};

#endif
