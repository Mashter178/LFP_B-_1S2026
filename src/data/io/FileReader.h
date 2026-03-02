#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>
#include "../types/Estudiante.h"
#include "../types/Curso.h"
#include "../types/Nota.h"

class FileReader {
public:
    static std::vector<Estudiante> leerEstudiantes(const std::string& ruta);
    static std::vector<Curso> leerCursos(const std::string& ruta);
    static std::vector<Nota> leerNotas(const std::string& ruta);
};

#endif