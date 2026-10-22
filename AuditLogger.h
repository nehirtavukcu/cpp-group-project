
#ifndef AUDITLOGGER_H
#define AUDITLOGGER_H

#include <string>
#include <vector>

class AuditLogger {
private:
    std::vector<std::string> logs;

public:
    void log(const std::string& message);
    void showLogs() const;
};

#endif
