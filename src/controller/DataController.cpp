#include "DataController.h"
#include <algorithm>
#include <cmath>
#include <numeric>

// ─── Constructor ──────────────────────────────────────────────────────────────
DataController::DataController(
    std::vector<Estudiante> estudiantes,
    std::vector<Curso>      cursos,
    std::vector<Nota>       notas
) {
    this->estudiantes = estudiantes;
    this->cursos      = cursos;
    this->notas       = notas;
}

// ─── Reporte 1: Estadísticas por Curso ───────────────────────────────────────

std::vector<double> getNotasDeCurso(std::vector<Nota>& notas, int codigoCurso) {
    std::vector<double> notasCurso;
    for (Nota n : notas) {
        if (n.codigo_curso == codigoCurso) {
            notasCurso.push_back(n.nota);
        }
    }
    return notasCurso;
}

int DataController::getCantEstudiantesCurso(int codigoCurso) {
    return getNotasDeCurso(notas, codigoCurso).size();
}

double DataController::getPromedioPorCurso(int codigoCurso) {
    std::vector<double> notasCurso = getNotasDeCurso(notas, codigoCurso);
    if (notasCurso.empty()) return 0.0;

    double suma = 0.0;
    for (double nota : notasCurso) suma += nota;
    return suma / notasCurso.size();
}

double DataController::getNotaMaximaPorCurso(int codigoCurso) {
    std::vector<double> notasCurso = getNotasDeCurso(notas, codigoCurso);
    if (notasCurso.empty()) return 0.0;

    double maxima = notasCurso[0];
    for (double nota : notasCurso) {
        if (nota > maxima) maxima = nota;
    }
    return maxima;
}

double DataController::getNotaMinimaPorCurso(int codigoCurso) {
    std::vector<double> notasCurso = getNotasDeCurso(notas, codigoCurso);
    if (notasCurso.empty()) return 0.0;

    double minima = notasCurso[0];
    for (double nota : notasCurso) {
        if (nota < minima) minima = nota;
    }
    return minima;
}

double DataController::getDesviacionPorCurso(int codigoCurso) {
    std::vector<double> notasCurso = getNotasDeCurso(notas, codigoCurso);
    if (notasCurso.empty()) return 0.0;

    double promedio = getPromedioPorCurso(codigoCurso);
    double suma     = 0.0;

    for (double nota : notasCurso) {
        suma += std::pow(nota - promedio, 2);
    }

    return std::sqrt(suma / notasCurso.size());
}

double DataController::getMedianaPorCurso(int codigoCurso) {
    std::vector<double> notasCurso = getNotasDeCurso(notas, codigoCurso);
    if (notasCurso.empty()) return 0.0;

    std::sort(notasCurso.begin(), notasCurso.end());

    int mitad = notasCurso.size() / 2;

    if (notasCurso.size() % 2 == 0) {
        return (notasCurso[mitad - 1] + notasCurso[mitad]) / 2.0;
    }

    return notasCurso[mitad];
}

// ─── Reporte 2: Rendimiento por Estudiante ────────────────────────────────────

double DataController::getPromedioEstudiante(int carnet) {
    double suma     = 0.0;
    int    cantidad = 0;

    for (Nota n : notas) {
        if (n.carnet == carnet) {
            suma += n.nota;
            cantidad++;
        }
    }

    return cantidad > 0 ? suma / cantidad : 0.0;
}

int DataController::getCursosAprobados(int carnet) {
    int aprobados = 0;
    for (Nota n : notas) {
        if (n.carnet == carnet && n.nota >= 61) aprobados++;
    }
    return aprobados;
}

int DataController::getCursosReprobados(int carnet) {
    int reprobados = 0;
    for (Nota n : notas) {
        if (n.carnet == carnet && n.nota < 61) reprobados++;
    }
    return reprobados;
}

int DataController::getCreditosAcumulados(int carnet) {
    int creditos = 0;
    for (Nota n : notas) {
        if (n.carnet == carnet && n.nota >= 61) {
            for (Curso c : cursos) {
                if (c.codigo == n.codigo_curso) {
                    creditos += c.creditos;
                }
            }
        }
    }
    return creditos;
}

// ─── Reporte 3: Top 10 ────────────────────────────────────────────────────────

std::vector<Estudiante> DataController::getTop10Estudiantes() {
    std::vector<Estudiante> ordenados = estudiantes;

    std::sort(ordenados.begin(), ordenados.end(),
        [this](Estudiante a, Estudiante b) {
            return getPromedioEstudiante(a.carnet) > getPromedioEstudiante(b.carnet);
        }
    );

    if (ordenados.size() > 10) {
        ordenados.erase(ordenados.begin() + 10, ordenados.end());
    }

    return ordenados;
}

// ─── Reporte 4: Mayor Reprobación ─────────────────────────────────────────────

double DataController::getPorcentajeReprobacion(int codigoCurso) {
    int total      = 0;
    int reprobados = 0;

    for (Nota n : notas) {
        if (n.codigo_curso == codigoCurso) {
            total++;
            if (n.nota < 61) reprobados++;
        }
    }

    return total > 0 ? (reprobados * 100.0) / total : 0.0;
}

int DataController::getAprobadosPorCurso(int codigoCurso) {
    int aprobados = 0;
    for (Nota n : notas) {
        if (n.codigo_curso == codigoCurso && n.nota >= 61) aprobados++;
    }
    return aprobados;
}

int DataController::getReprobadosPorCurso(int codigoCurso) {
    int reprobados = 0;
    for (Nota n : notas) {
        if (n.codigo_curso == codigoCurso && n.nota < 61) reprobados++;
    }
    return reprobados;
}

std::vector<Curso> DataController::getCursosOrdenadosPorReprobacion() {
    std::vector<Curso> ordenados = cursos;

    std::sort(ordenados.begin(), ordenados.end(),
        [this](Curso a, Curso b) {
            return getPorcentajeReprobacion(a.codigo) > getPorcentajeReprobacion(b.codigo);
        }
    );

    return ordenados;
}

// ─── Reporte 5: Análisis por Carrera ──────────────────────────────────────────

std::vector<std::string> DataController::getCarreras() {
    std::vector<std::string> carreras;

    for (Estudiante e : estudiantes) {
        bool existe = false;
        for (std::string c : carreras) {
            if (c == e.carrera) {
                existe = true;
                break;
            }
        }
        if (!existe) carreras.push_back(e.carrera);
    }

    return carreras;
}

std::vector<Estudiante> DataController::getEstudiantesPorCarrera(const std::string& carrera) {
    std::vector<Estudiante> resultado;
    for (Estudiante e : estudiantes) {
        if (e.carrera == carrera) resultado.push_back(e);
    }
    return resultado;
}

std::vector<Curso> DataController::getCursosPorCarrera(const std::string& carrera) {
    std::vector<Curso> resultado;
    for (Curso c : cursos) {
        if (c.carrera == carrera) resultado.push_back(c);
    }
    return resultado;
}

double DataController::getPromedioPorCarrera(const std::string& carrera) {
    std::vector<Estudiante> estudiantesCarrera = getEstudiantesPorCarrera(carrera);
    if (estudiantesCarrera.empty()) return 0.0;

    double suma = 0.0;
    for (Estudiante e : estudiantesCarrera) {
        suma += getPromedioEstudiante(e.carnet);
    }

    return suma / estudiantesCarrera.size();
}