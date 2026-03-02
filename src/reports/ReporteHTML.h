#ifndef REPORTEHTML_H
#define REPORTEHTML_H

#include <string>
#include <vector>
#include <fstream>
#include "../data/types/Estudiante.h"
#include "../data/types/Curso.h"
#include "../data/types/Nota.h"
#include "../controller/DataController.h"

class ReporteHTML {
private:
    DataController& controller;
    std::string     carpetaOutput;

    // ─── Utilidades HTML ──────────────────────────────────────────────────
    void escribirCabecera  (std::ofstream& archivo, const std::string& titulo);
    void escribirPiePagina (std::ofstream& archivo);
    bool crearArchivo      (std::ofstream& archivo, const std::string& nombreArchivo);

public:
    // ─── Constructor ──────────────────────────────────────────────────────
    ReporteHTML(DataController& controller, const std::string& carpetaOutput);

    // ─── Reportes ─────────────────────────────────────────────────────────
    void generarEstadisticasPorCurso       (const std::vector<Curso>& cursos);
    void generarRendimientoPorEstudiante   (const std::vector<Estudiante>& estudiantes);
    void generarTop10Estudiantes           ();
    void generarCursosMayorReprobacion     (const std::vector<Curso>& cursos);
    void generarAnalisisPorCarrera         ();
};

#endif