#include <iostream>
#include "data/io/FileReader.h"

int main() {
    // ─── Cargar archivos ─────────────────────────────────────────────────────
    std::vector<Estudiante> estudiantes = FileReader::leerEstudiantes("test/estudiante.lfp");
    std::vector<Curso>      cursos      = FileReader::leerCursos("test/curso.lfp");
    std::vector<Nota>       notas       = FileReader::leerNotas("test/notas.lfp");

    // ─── Verificar carga ─────────────────────────────────────────────────────
    std::cout << "Estudiantes: " << estudiantes.size() << std::endl;
    std::cout << "Cursos: "      << cursos.size()      << std::endl;
    std::cout << "Notas: "       << notas.size()        << std::endl;

    return 0;
}