#include "Menu.h"
#include "../data/io/FileReader.h"
#include <iostream>

// ─── Mostrar menú ─────────────────────────────────────────────────────────────
void Menu::mostrar() {
    int opcion;

    do {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║       SISTEMA DE ESTUDIANTES       ║" << std::endl;
        std::cout << "╠════════════════════════════════════╣" << std::endl;
        std::cout << "║  1. Cargar estudiantes             ║" << std::endl;
        std::cout << "║  2. Cargar cursos                  ║" << std::endl;
        std::cout << "║  3. Cargar notas                   ║" << std::endl;
        std::cout << "╠════════════════════════════════════╣" << std::endl;
        std::cout << "║  4. Estadisticas por curso         ║" << std::endl;
        std::cout << "║  5. Rendimiento por estudiante     ║" << std::endl;
        std::cout << "║  6. Top 10 mejores estudiantes     ║" << std::endl;
        std::cout << "║  7. Cursos con mayor reprobacion   ║" << std::endl;
        std::cout << "║  8. Analisis por carrera           ║" << std::endl;
        std::cout << "╠════════════════════════════════════╣" << std::endl;
        std::cout << "║  9. Salir                          ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "\n  Opcion: ";
        std::cin  >> opcion;

        switch(opcion) {
            case 1: cargarEstudiantes(); break;
            case 2: cargarCursos();      break;
            case 3: cargarNotas();       break;
            case 4: reporteEstadisticasPorCurso();       break;
            case 5: reporteRendimientoPorEstudiante();   break;
            case 6: reporteTop10Estudiantes();           break;
            case 7: reporteCursosMayorReprobacion();     break;
            case 8: reporteAnalisisPorCarrera();         break;
            case 9: std::cout << "\nHasta luego!\n";     break;
            default: std::cout << "\nOpcion invalida\n"; break;
        }

    } while(opcion != 9);
}

// ─── Carga de archivos ────────────────────────────────────────────────────────
void Menu::cargarEstudiantes() {
    estudiantes = FileReader::leerEstudiantes("test/estudiante.lfp");
}

void Menu::cargarCursos() {
    cursos = FileReader::leerCursos("test/curso.lfp");
}

void Menu::cargarNotas() {
    notas = FileReader::leerNotas("test/notas.lfp");
}

// ─── Reportes (por implementar) ───────────────────────────────────────────────
void Menu::reporteEstadisticasPorCurso() {
    std::cout << "\n[EN CONSTRUCCION] Estadisticas por curso" << std::endl;
}

void Menu::reporteRendimientoPorEstudiante() {
    std::cout << "\n[EN CONSTRUCCION] Rendimiento por estudiante" << std::endl;
}

void Menu::reporteTop10Estudiantes() {
    std::cout << "\n[EN CONSTRUCCION] Top 10 estudiantes" << std::endl;
}

void Menu::reporteCursosMayorReprobacion() {
    std::cout << "\n[EN CONSTRUCCION] Cursos con mayor reprobacion" << std::endl;
}

void Menu::reporteAnalisisPorCarrera() {
    std::cout << "\n[EN CONSTRUCCION] Analisis por carrera" << std::endl;
}