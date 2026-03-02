#include "Menu.h"
#include "../data/io/FileReader.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>  // Para listar archivos

namespace fs = std::filesystem;

// ─── Constructor / Destructor ─────────────────────────────────────────────────
Menu::Menu() {
    controller = nullptr;
    reporte    = nullptr;
}

Menu::~Menu() {
    delete controller;
    delete reporte;
}

// ─── Mostrar menú ─────────────────────────────────────────────────────────────
void Menu::mostrar() {
    int opcion;

    do {
        system("cls");
        std::cout << "\n+====================================+" << std::endl;
        std::cout << "|       SISTEMA DE ESTUDIANTES       |" << std::endl;
        std::cout << "+====================================+" << std::endl;
        std::cout << "|  1. Cargar estudiantes             |" << std::endl;
        std::cout << "|  2. Cargar cursos                  |" << std::endl;
        std::cout << "|  3. Cargar notas                   |" << std::endl;
        std::cout << "+====================================+" << std::endl;
        std::cout << "|  4. Estadisticas por curso         |" << std::endl;
        std::cout << "|  5. Rendimiento por estudiante     |" << std::endl;
        std::cout << "|  6. Top 10 mejores estudiantes     |" << std::endl;
        std::cout << "|  7. Cursos con mayor reprobacion   |" << std::endl;
        std::cout << "|  8. Analisis por carrera           |" << std::endl;
        std::cout << "+====================================+" << std::endl;
        std::cout << "|  9. Salir                          |" << std::endl;
        std::cout << "+====================================+" << std::endl;
        std::cout << "\n  Opcion: ";
        std::cin  >> opcion;

        switch(opcion) {
            case 1: cargarEstudiantes();                break;
            case 2: cargarCursos();                     break;
            case 3: cargarNotas();                      break;
            case 4: reporteEstadisticasPorCurso();      break;
            case 5: reporteRendimientoPorEstudiante();  break;
            case 6: reporteTop10Estudiantes();          break;
            case 7: reporteCursosMayorReprobacion();    break;
            case 8: reporteAnalisisPorCarrera();        break;
            case 9: std::cout << "\nHasta luego!\n";    break;
            default: std::cout << "\nOpcion invalida\n";break;
        }

        if (opcion != 9) {
            std::cout << "\nPresiona ENTER para continuar...";
            std::cin.ignore();
            std::cin.get();
        }

    } while(opcion != 9);
}

// ─── Utilidades ───────────────────────────────────────────────────────────────
std::string Menu::elegirArchivo() {
    std::vector<std::string> archivos;

    // Listar archivos .lfp en la carpeta test/
    for (fs::directory_entry entry : fs::directory_iterator("test")) {
        if (entry.path().extension() == ".lfp") {
            archivos.push_back(entry.path().filename().string());
        }
    }

    if (archivos.empty()) {
        std::cout << "\n  [ERROR] No hay archivos .lfp en la carpeta test/" << std::endl;
        return "";
    }

    // Mostrar archivos disponibles
    std::cout << "\n  Archivos disponibles en test/:" << std::endl;
    for (int i = 0; i < archivos.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << archivos[i] << std::endl;
    }

    // Pedir seleccion
    int seleccion;
    std::cout << "\n  Elige un archivo (1-" << archivos.size() << "): ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > archivos.size()) {
        std::cout << "  [ERROR] Opcion invalida" << std::endl;
        return "";
    }

    return "test/" + archivos[seleccion - 1];
}

void Menu::actualizarController() {
    // Eliminar controller y reporte anteriores
    delete controller;
    delete reporte;

    // Crear nuevos con los datos actualizados
    controller = new DataController(estudiantes, cursos, notas);
    reporte    = new ReporteHTML(*controller, "output");
}

bool Menu::verificarDatos() {
    if (estudiantes.empty() || cursos.empty() || notas.empty()) {
        std::cout << "\n[AVISO] Debes cargar todos los archivos primero" << std::endl;
        std::cout << "  Estudiantes: " << (estudiantes.empty() ? "[NO]" : "[OK]") << std::endl;
        std::cout << "  Cursos:      " << (cursos.empty()      ? "[NO]" : "[OK]") << std::endl;
        std::cout << "  Notas:       " << (notas.empty()       ? "[NO]" : "[OK]") << std::endl;
        return false;
    }
    return true;
}

// ─── Carga de archivos ────────────────────────────────────────────────────────
void Menu::cargarEstudiantes() {
    std::string ruta = elegirArchivo();
    if (ruta.empty()) return;

    estudiantes = FileReader::leerEstudiantes(ruta);
    actualizarController();
}

void Menu::cargarCursos() {
    std::string ruta = elegirArchivo();
    if (ruta.empty()) return;

    cursos = FileReader::leerCursos(ruta);
    actualizarController();
}

void Menu::cargarNotas() {
    std::string ruta = elegirArchivo();
    if (ruta.empty()) return;

    notas = FileReader::leerNotas(ruta);
    actualizarController();
}

// ─── Reportes ─────────────────────────────────────────────────────────────────
void Menu::reporteEstadisticasPorCurso() {
    if (!verificarDatos()) return;
    reporte->generarEstadisticasPorCurso(cursos);
}

void Menu::reporteRendimientoPorEstudiante() {
    if (!verificarDatos()) return;
    reporte->generarRendimientoPorEstudiante(estudiantes);
}

void Menu::reporteTop10Estudiantes() {
    if (!verificarDatos()) return;
    reporte->generarTop10Estudiantes();
}

void Menu::reporteCursosMayorReprobacion() {
    if (!verificarDatos()) return;
    reporte->generarCursosMayorReprobacion(cursos);
}

void Menu::reporteAnalisisPorCarrera() {
    if (!verificarDatos()) return;
    reporte->generarAnalisisPorCarrera();
}