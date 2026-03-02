#ifndef MENU_H
#define MENU_H

#include <vector>
#include "../data/types/Estudiante.h"
#include "../data/types/Curso.h"
#include "../data/types/Nota.h"
#include "../controller/DataController.h"
#include "../reports/ReporteHTML.h"

class Menu {
private:
    // ─── Datos ────────────────────────────────────────────────────────────
    std::vector<Estudiante> estudiantes;
    std::vector<Curso>      cursos;
    std::vector<Nota>       notas;

    // ─── MVC ──────────────────────────────────────────────────────────────
    DataController* controller;
    ReporteHTML*    reporte;

public:
    Menu();
    ~Menu();
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

    // ─── Utilidades ───────────────────────────────────────────────────────
    void actualizarController();
    bool verificarDatos();
    std::string elegirArchivo();
};

#endif