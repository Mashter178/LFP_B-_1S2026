#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <vector>
#include "../data/types/Estudiante.h"
#include "../data/types/Curso.h"
#include "../data/types/Nota.h"

class DataController {
private:
    std::vector<Estudiante> estudiantes;
    std::vector<Curso>      cursos;
    std::vector<Nota>       notas;

public:
    // ─── Constructor ──────────────────────────────────────────────────────
    DataController(
        std::vector<Estudiante> estudiantes,
        std::vector<Curso>      cursos,
        std::vector<Nota>       notas
    );

    // ─── Reporte 1: Estadísticas por Curso ────────────────────────────────
    double  getPromedioPorCurso     (int codigoCurso);
    double  getNotaMaximaPorCurso   (int codigoCurso);
    double  getNotaMinimaPorCurso   (int codigoCurso);
    double  getDesviacionPorCurso   (int codigoCurso);
    double  getMedianaPorCurso      (int codigoCurso);
    int     getCantEstudiantesCurso (int codigoCurso);

    // ─── Reporte 2: Rendimiento por Estudiante ────────────────────────────
    double  getPromedioEstudiante   (int carnet);
    int     getCursosAprobados      (int carnet);
    int     getCursosReprobados     (int carnet);
    int     getCreditosAcumulados   (int carnet);

    // ─── Reporte 3: Top 10 ────────────────────────────────────────────────
    std::vector<Estudiante> getTop10Estudiantes();

    // ─── Reporte 4: Mayor Reprobación ─────────────────────────────────────
    double  getPorcentajeReprobacion        (int codigoCurso);
    int     getAprobadosPorCurso            (int codigoCurso);
    int     getReprobadosPorCurso           (int codigoCurso);
    std::vector<Curso> getCursosOrdenadosPorReprobacion();

    // ─── Reporte 5: Análisis por Carrera ──────────────────────────────────
    std::vector<Estudiante> getEstudiantesPorCarrera (const std::string& carrera);
    std::vector<Curso>      getCursosPorCarrera      (const std::string& carrera);
    double                  getPromedioPorCarrera     (const std::string& carrera);
    std::vector<std::string>getCarreras              ();
};

#endif