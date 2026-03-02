#include "FileReader.h"
#include "../utils/StringUtils.h"
#include <fstream>
#include <iostream>

// ─── Importar Estudiantes ─────────────────────────────────────────────────────────
std::vector<Estudiante> FileReader::leerEstudiantes(const std::string& ruta) {
    std::vector<Estudiante> lista;
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir: " << ruta << std::endl;
        return lista;
    }

    std::string linea;
    bool primeraLinea = true;

    while (std::getline(archivo, linea)) {
        if (primeraLinea) { primeraLinea = false; continue; }

        linea = StringUtils::trim(linea);
        if (linea.empty()) continue;

        std::vector<std::string> campos = StringUtils::split(linea, ',');
        if (campos.size() != 5) continue;

        Estudiante e(
            StringUtils::toInt(campos[0]),
            StringUtils::trim(campos[1]),
            StringUtils::trim(campos[2]),
            StringUtils::trim(campos[3]),
            StringUtils::toInt(campos[4])
        );

        lista.push_back(e);
    }

    archivo.close();
    std::cout << "[OK] " << lista.size() << " estudiantes cargados" << std::endl;
    return lista;
}

// ─── Importar Cursos ──────────────────────────────────────────────────────────────
std::vector<Curso> FileReader::leerCursos(const std::string& ruta) {
    std::vector<Curso> lista;
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir: " << ruta << std::endl;
        return lista;
    }

    std::string linea;
    bool primeraLinea = true;

    while (std::getline(archivo, linea)) {
        if (primeraLinea) { primeraLinea = false; continue; }

        linea = StringUtils::trim(linea);
        if (linea.empty()) continue;

        std::vector<std::string> campos = StringUtils::split(linea, ',');
        if (campos.size() != 5) continue;

        Curso c(
            StringUtils::toInt(campos[0]),
            StringUtils::trim(campos[1]),
            StringUtils::toInt(campos[2]),
            StringUtils::toInt(campos[3]),
            StringUtils::trim(campos[4])
        );

        lista.push_back(c);
    }

    archivo.close();
    std::cout << "[OK] " << lista.size() << " cursos cargados" << std::endl;
    return lista;
}

// ─── Importar Notas ───────────────────────────────────────────────────────────────
std::vector<Nota> FileReader::leerNotas(const std::string& ruta) {
    std::vector<Nota> lista;
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir: " << ruta << std::endl;
        return lista;
    }

    std::string linea;
    bool primeraLinea = true;

    while (std::getline(archivo, linea)) {
        if (primeraLinea) { primeraLinea = false; continue; }

        linea = StringUtils::trim(linea);
        if (linea.empty()) continue;

        std::vector<std::string> campos = StringUtils::split(linea, ',');
        if (campos.size() != 5) continue;

        Nota n(
            StringUtils::toInt(campos[0]),
            StringUtils::toInt(campos[1]),
            StringUtils::toDouble(campos[2]),
            StringUtils::trim(campos[3]),
            StringUtils::toInt(campos[4])
        );

        lista.push_back(n);
    }

    archivo.close();
    std::cout << "[OK] " << lista.size() << " notas cargadas" << std::endl;
    return lista;
}