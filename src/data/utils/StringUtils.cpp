#include "StringUtils.h"
#include <sstream>

// ─── trim ────────────────────────────────────────────────────────────────────
std::string StringUtils::trim(const std::string& str) {
    int inicio = 0;
    int fin = str.size() - 1;

    while (inicio <= fin && str[inicio] == ' ') inicio++;
    while (fin >= inicio && str[fin] == ' ') fin--;

    return str.substr(inicio, fin - inicio + 1);
}

// ─── split ───────────────────────────────────────────────────────────────────
std::vector<std::string> StringUtils::split(const std::string& str, char separador) {
    std::vector<std::string> resultado;
    std::stringstream ss(str);
    std::string parte;

    while (std::getline(ss, parte, separador)) {
        resultado.push_back(parte);
    }

    return resultado;
}

// ─── toInt / toDouble ────────────────────────────────────────────────────────
int StringUtils::toInt(const std::string& str) {
    return std::stoi(str);
}

double StringUtils::toDouble(const std::string& str) {
    return std::stod(str);
}