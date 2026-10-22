
#include "AuditLogger.h"
#include <iostream>

void AuditLogger::log(const std::string& message) {
    logs.push_back(message);
}

void AuditLogger::showLogs() const {
    std::cout << "\n--- Audit Logs ---\n";

    for (const std::string& entry : logs) {
        std::cout << entry << "\n";
    }
}

