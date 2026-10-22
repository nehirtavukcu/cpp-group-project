#pragma once

#include "Common.h"

class ACLManager {
private:
    SharedData& data;

public:
    ACLManager(SharedData& sharedData);

    bool hasPermission(
        const string& username,
        const string& filename,
        const string& permission
    ) const;

    string choosePermission();
    void showACL();
    void changePermission(bool grant);
    void setupDemoPermissions();
};