#ifndef MENU_H
#define MENU_H

#include <vector>
#include "../data/types/Estudiante.h"
#include "../data/types/Curso.h"
#include "../data/types/Nota.h"

class Menu {
private:
    std::vector<Estudiante> estudiantes;
    std::vector<Curso>      cursos;
    std::vector<Nota>       notas;

public:
    void mostrar();

private:
    // ─── Carga de archivos ────────────────────────────────────────────────
    void cargarEstudiantes();
    void cargarCursos();
    void cargarNotas();

    // ─── Reportes ─────────────────────────────────────────────────────────
    void reporteEstadisticasPorCurso();
    void reporteRendimientoPorEstudiante();
    void reporteTop10Estudiantes();
    void reporteCursosMayorReprobacion();
    void reporteAnalisisPorCarrera();
};

#endif