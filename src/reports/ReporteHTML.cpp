#include "ReporteHTML.h"
#include <iostream>
#include <filesystem>

// ─── Constructor ──────────────────────────────────────────────────────────────
ReporteHTML::ReporteHTML(DataController& controller, const std::string& carpetaOutput) 
    : controller(controller), carpetaOutput(carpetaOutput) {
    std::filesystem::create_directories(carpetaOutput);
}

// ─── Utilidades HTML ──────────────────────────────────────────────────────────
bool ReporteHTML::crearArchivo(std::ofstream& archivo, const std::string& nombreArchivo) {
    archivo.open(carpetaOutput + "/" + nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "[ERROR] No se pudo crear: " << nombreArchivo << std::endl;
        return false;
    }
    return true;
}

void ReporteHTML::escribirCabecera(std::ofstream& archivo, const std::string& titulo) {
    archivo << "<!DOCTYPE html>"                                                << std::endl;
    archivo << "<html lang='es'>"                                               << std::endl;
    archivo << "<head>"                                                         << std::endl;
    archivo << "  <meta charset='UTF-8'>"                                       << std::endl;
    archivo << "  <title>" << titulo << "</title>"                              << std::endl;
    archivo << "  <style>"                                                      << std::endl;
    archivo << "    body  { font-family: Arial; margin: 20px; }"               << std::endl;
    archivo << "    h1    { color: #2c3e50; }"                                  << std::endl;
    archivo << "    table { border-collapse: collapse; width: 100%; }"         << std::endl;
    archivo << "    th    { background-color: #2c3e50; color: white; padding: 10px; }" << std::endl;
    archivo << "    td    { border: 1px solid #ddd; padding: 8px; }"           << std::endl;
    archivo << "    tr:nth-child(even) { background-color: #f2f2f2; }"         << std::endl;
    archivo << "    .aprobado  { color: green; font-weight: bold; }"           << std::endl;
    archivo << "    .reprobado { color: red;   font-weight: bold; }"           << std::endl;
    archivo << "  </style>"                                                     << std::endl;
    archivo << "</head>"                                                        << std::endl;
    archivo << "<body>"                                                         << std::endl;
    archivo << "  <h1>" << titulo << "</h1>"                                    << std::endl;
}

void ReporteHTML::escribirPiePagina(std::ofstream& archivo) {
    archivo << "</body>" << std::endl;
    archivo << "</html>" << std::endl;
    archivo.close();
}

// ─── Reporte 1: Estadísticas por Curso ───────────────────────────────────────
void ReporteHTML::generarEstadisticasPorCurso(const std::vector<Curso>& cursos) {
    std::ofstream archivo;
    if (!crearArchivo(archivo, "estadisticas_curso.html")) return;

    escribirCabecera(archivo, "Estadisticas por Curso");

    archivo << "  <table>"                         << std::endl;
    archivo << "    <tr>"                          << std::endl;
    archivo << "      <th>Codigo</th>"             << std::endl;
    archivo << "      <th>Nombre</th>"             << std::endl;
    archivo << "      <th>Estudiantes</th>"        << std::endl;
    archivo << "      <th>Promedio</th>"           << std::endl;
    archivo << "      <th>Nota Maxima</th>"        << std::endl;
    archivo << "      <th>Nota Minima</th>"        << std::endl;
    archivo << "      <th>Desviacion</th>"         << std::endl;
    archivo << "      <th>Mediana</th>"            << std::endl;
    archivo << "    </tr>"                         << std::endl;

    for (Curso c : cursos) {
        archivo << "    <tr>"                                                           << std::endl;
        archivo << "      <td>" << c.codigo                                    << "</td>" << std::endl;
        archivo << "      <td>" << c.nombre                                    << "</td>" << std::endl;
        archivo << "      <td>" << controller.getCantEstudiantesCurso(c.codigo)<< "</td>" << std::endl;
        archivo << "      <td>" << controller.getPromedioPorCurso(c.codigo)    << "</td>" << std::endl;
        archivo << "      <td>" << controller.getNotaMaximaPorCurso(c.codigo)  << "</td>" << std::endl;
        archivo << "      <td>" << controller.getNotaMinimaPorCurso(c.codigo)  << "</td>" << std::endl;
        archivo << "      <td>" << controller.getDesviacionPorCurso(c.codigo)  << "</td>" << std::endl;
        archivo << "      <td>" << controller.getMedianaPorCurso(c.codigo)     << "</td>" << std::endl;
        archivo << "    </tr>"                                                           << std::endl;
    }

    archivo << "  </table>" << std::endl;
    escribirPiePagina(archivo);
    std::cout << "[OK] Reporte generado: estadisticas_curso.html" << std::endl;
}

// ─── Reporte 2: Rendimiento por Estudiante ────────────────────────────────────
void ReporteHTML::generarRendimientoPorEstudiante(const std::vector<Estudiante>& estudiantes) {
    std::ofstream archivo;
    if (!crearArchivo(archivo, "rendimiento_estudiante.html")) return;

    escribirCabecera(archivo, "Rendimiento por Estudiante");

    archivo << "  <table>"                         << std::endl;
    archivo << "    <tr>"                          << std::endl;
    archivo << "      <th>Nombre</th>"             << std::endl;
    archivo << "      <th>Carnet</th>"             << std::endl;
    archivo << "      <th>Carrera</th>"            << std::endl;
    archivo << "      <th>Semestre</th>"           << std::endl;
    archivo << "      <th>Promedio</th>"           << std::endl;
    archivo << "      <th>Aprobados</th>"          << std::endl;
    archivo << "      <th>Reprobados</th>"         << std::endl;
    archivo << "      <th>Creditos</th>"           << std::endl;
    archivo << "    </tr>"                         << std::endl;

    for (Estudiante e : estudiantes) {
        double promedio = controller.getPromedioEstudiante(e.carnet);

        archivo << "    <tr>"                                                                      << std::endl;
        archivo << "      <td>" << e.nombre << " " << e.apellido                          << "</td>" << std::endl;
        archivo << "      <td>" << e.carnet                                               << "</td>" << std::endl;
        archivo << "      <td>" << e.carrera                                              << "</td>" << std::endl;
        archivo << "      <td>" << e.semestre                                             << "</td>" << std::endl;
        archivo << "      <td class='" << (promedio >= 61 ? "aprobado" : "reprobado") << "'>"       << std::endl;
        archivo << "          " << promedio                                               << "</td>" << std::endl;
        archivo << "      <td>" << controller.getCursosAprobados(e.carnet)                << "</td>" << std::endl;
        archivo << "      <td>" << controller.getCursosReprobados(e.carnet)               << "</td>" << std::endl;
        archivo << "      <td>" << controller.getCreditosAcumulados(e.carnet)             << "</td>" << std::endl;
        archivo << "    </tr>"                                                                      << std::endl;
    }

    archivo << "  </table>" << std::endl;
    escribirPiePagina(archivo);
    std::cout << "[OK] Reporte generado: rendimiento_estudiante.html" << std::endl;
}

// ─── Reporte 3: Top 10 ────────────────────────────────────────────────────────
void ReporteHTML::generarTop10Estudiantes() {
    std::ofstream archivo;
    if (!crearArchivo(archivo, "top10_estudiantes.html")) return;

    escribirCabecera(archivo, "Top 10 Mejores Estudiantes");

    archivo << "  <table>"                 << std::endl;
    archivo << "    <tr>"                  << std::endl;
    archivo << "      <th>Posicion</th>"   << std::endl;
    archivo << "      <th>Carnet</th>"     << std::endl;
    archivo << "      <th>Nombre</th>"     << std::endl;
    archivo << "      <th>Carrera</th>"    << std::endl;
    archivo << "      <th>Semestre</th>"   << std::endl;
    archivo << "      <th>Promedio</th>"   << std::endl;
    archivo << "    </tr>"                 << std::endl;

    std::vector<Estudiante> top10 = controller.getTop10Estudiantes();
    int posicion = 1;

    for (Estudiante e : top10) {
        archivo << "    <tr>"                                                          << std::endl;
        archivo << "      <td>" << posicion++                                << "</td>" << std::endl;
        archivo << "      <td>" << e.carnet                                  << "</td>" << std::endl;
        archivo << "      <td>" << e.nombre << " " << e.apellido             << "</td>" << std::endl;
        archivo << "      <td>" << e.carrera                                 << "</td>" << std::endl;
        archivo << "      <td>" << e.semestre                                << "</td>" << std::endl;
        archivo << "      <td>" << controller.getPromedioEstudiante(e.carnet)<< "</td>" << std::endl;
        archivo << "    </tr>"                                                          << std::endl;
    }

    archivo << "  </table>" << std::endl;
    escribirPiePagina(archivo);
    std::cout << "[OK] Reporte generado: top10_estudiantes.html" << std::endl;
}

// ─── Reporte 4: Mayor Reprobación ─────────────────────────────────────────────
void ReporteHTML::generarCursosMayorReprobacion(const std::vector<Curso>& cursos) {
    std::ofstream archivo;
    if (!crearArchivo(archivo, "cursos_reprobacion.html")) return;

    escribirCabecera(archivo, "Cursos con Mayor Indice de Reprobacion");

    archivo << "  <table>"                         << std::endl;
    archivo << "    <tr>"                          << std::endl;
    archivo << "      <th>Codigo</th>"             << std::endl;
    archivo << "      <th>Nombre</th>"             << std::endl;
    archivo << "      <th>Total</th>"              << std::endl;
    archivo << "      <th>Aprobados</th>"          << std::endl;
    archivo << "      <th>Reprobados</th>"         << std::endl;
    archivo << "      <th>% Reprobacion</th>"      << std::endl;
    archivo << "    </tr>"                         << std::endl;

    std::vector<Curso> ordenados = controller.getCursosOrdenadosPorReprobacion();

    for (Curso c : ordenados) {
        int total      = controller.getCantEstudiantesCurso(c.codigo);
        int aprobados  = controller.getAprobadosPorCurso(c.codigo);
        int reprobados = controller.getReprobadosPorCurso(c.codigo);

        archivo << "    <tr>"                                                              << std::endl;
        archivo << "      <td>" << c.codigo                                      << "</td>" << std::endl;
        archivo << "      <td>" << c.nombre                                      << "</td>" << std::endl;
        archivo << "      <td>" << total                                         << "</td>" << std::endl;
        archivo << "      <td>" << aprobados                                     << "</td>" << std::endl;
        archivo << "      <td>" << reprobados                                    << "</td>" << std::endl;
        archivo << "      <td>" << controller.getPorcentajeReprobacion(c.codigo) << "%</td>" << std::endl;
        archivo << "    </tr>"                                                              << std::endl;
    }

    archivo << "  </table>" << std::endl;
    escribirPiePagina(archivo);
    std::cout << "[OK] Reporte generado: cursos_reprobacion.html" << std::endl;
}

// ─── Reporte 5: Análisis por Carrera ──────────────────────────────────────────
void ReporteHTML::generarAnalisisPorCarrera() {
    std::ofstream archivo;
    if (!crearArchivo(archivo, "analisis_carrera.html")) return;

    escribirCabecera(archivo, "Analisis por Carrera");

    archivo << "  <table>"                             << std::endl;
    archivo << "    <tr>"                              << std::endl;
    archivo << "      <th>Carrera</th>"                << std::endl;
    archivo << "      <th>Total Estudiantes</th>"      << std::endl;
    archivo << "      <th>Promedio General</th>"       << std::endl;
    archivo << "      <th>Cursos Disponibles</th>"     << std::endl;
    archivo << "      <th>Distribucion Semestres</th>" << std::endl;
    archivo << "    </tr>"                             << std::endl;

    std::vector<std::string> carreras = controller.getCarreras();

    for (std::string carrera : carreras) {
        std::vector<Estudiante> estudiantesCarrera = controller.getEstudiantesPorCarrera(carrera);
        std::vector<Curso>      cursosCarrera      = controller.getCursosPorCarrera(carrera);

        std::string distribucion = "";
        for (int s = 1; s <= 10; s++) {
            int cantidad = 0;
            for (Estudiante e : estudiantesCarrera) {
                if (e.semestre == s) cantidad++;
            }
            if (cantidad > 0) {
                distribucion += "S" + std::to_string(s) + ":" + std::to_string(cantidad) + " ";
            }
        }

        archivo << "    <tr>"                                                                   << std::endl;
        archivo << "      <td>" << carrera                                             << "</td>" << std::endl;
        archivo << "      <td>" << estudiantesCarrera.size()                           << "</td>" << std::endl;
        archivo << "      <td>" << controller.getPromedioPorCarrera(carrera)           << "</td>" << std::endl;
        archivo << "      <td>" << cursosCarrera.size()                                << "</td>" << std::endl;
        archivo << "      <td>" << distribucion                                        << "</td>" << std::endl;
        archivo << "    </tr>"                                                                   << std::endl;
    }

    archivo << "  </table>" << std::endl;
    escribirPiePagina(archivo);
    std::cout << "[OK] Reporte generado: analisis_carrera.html" << std::endl;
}