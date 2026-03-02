#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

class StringUtils {
public:
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char separador);
    static int toInt(const std::string& str);
    static double toDouble(const std::string& str);
};

#endif