#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <unordered_map>
#include <source_location>

constexpr const char* colorRed = "\x1b[31m";
constexpr const char* colorYellow = "\x1b[33m";
constexpr const char* colorBlue = "\x1b[34m";
constexpr const char* colorReset = "\x1b[0m";

const std::unordered_map<std::string, const char*> COLOR_MAP
{
    { "red", colorRed },
    { "yellow", colorYellow },
    { "blue", colorBlue },
    { "reset", colorReset },
};

class Logger
{
public:

    /* Interface */
    template<typename T>
    static void INFO(T&& param, std::source_location location = std::source_location::current())
    {
        Logger::getInstance().logINFO(std::forward<T>(param), location);
    }

    template<typename T>
    static void DEBUG(T&& param, std::source_location location = std::source_location::current())
    {
        Logger::getInstance().logDEBUG(std::forward<T>(param), location);
    }

    template<typename T>
    static void WARN(T&& param, std::source_location location = std::source_location::current())
    {
        Logger::getInstance().logWARN(std::forward<T>(param), location);
    }

    template<typename T>
    static void ERROR(T&& param, std::source_location location = std::source_location::current())
    {
        Logger::getInstance().logERROR(std::forward<T>(param), location);
    }

    /* Singleton */
    static Logger& getInstance()
    {
        static Logger logger;
        return logger;
    }

    /* Delete unnecessary special member functions */
    Logger(Logger&&) = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

private:
    Logger() = default; /* must be private */
    ~Logger() = default;

    std::mutex Mutex;

    template<typename T>
    void logINFO(T&& param, std::source_location location)
    {
        std::lock_guard<std::mutex> lock(Mutex); // Thread Safe
        std::cout << "[INFO] | FUNCNAME : " << location.function_name() << " | FUNCLINE : " << location.line() << " | " << param << std::endl;
    }

    template<typename T>
    void logDEBUG(T&& param, std::source_location location)
    {
        std::lock_guard<std::mutex> lock(Mutex); // Thread Safe
        std::cout << "[DEBUG] | FUNCNAME : " << location.function_name() << " | FUNCLINE : " << location.line() << " | " << param << std::endl;
    }

    template<typename T>
    void logWARN(T&& param, std::source_location location)
    {
        std::lock_guard<std::mutex> lock(Mutex); // Thread Safe
        std::cout << colorYellow << "[WARN] | FUNCNAME : " << location.function_name() << " | FUNCLINE : " << location.line() << " | " << param << colorReset << std::endl;
    }

    template<typename T>
    void logERROR(T&& param, std::source_location location)
    {
        std::lock_guard<std::mutex> lock(Mutex); // Thread Safe
        std::cout << colorRed << "[ERROR] | FUNCNAME : " << location.function_name() << " | FUNCLINE : " << location.line() << " | " << param << colorReset << std::endl;
    }
};

#endif