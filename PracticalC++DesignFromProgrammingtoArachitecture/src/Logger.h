#ifndef LOGGER_H
#define LOGGER_H
#include <sstream>
#include <iostream>
#include <filesystem>

#define LOG(...) LogImpl(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

template <typename ...Args>
void LogImpl(const char* file_name, int line, const char* function_name, Args&&...args)
{
    std::ostringstream stream;

    stream << std::filesystem::path(file_name).filename() << "(" << line << "):" << function_name << " > ";
    (stream << ... << std::forward<Args>(args)) << std::endl;
    std::cout << stream.str();
}
#endif  // LOGGER_H
