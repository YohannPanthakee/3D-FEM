#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
public:
    static Logger& getInstance();

    void setLogFile(const std::string& filename);
    void log(LogLevel level, const std::string& message);

private:
    Logger(); // Private constructor for singleton
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string getTimestamp();
    std::string levelToString(LogLevel level);

    std::ofstream logFile;
    std::mutex logMutex;
};

#endif // LOGGER_H