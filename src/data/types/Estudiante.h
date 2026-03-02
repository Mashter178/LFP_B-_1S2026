#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

struct Estudiante {
    int carnet;
    std::string nombre;
    std::string apellido;
    std::string carrera;
    int semestre;        

    // Constructor
    Estudiante(int carnet, std::string nombre, std::string apellido,
            std::string carrera, int semestre) {
        this->carnet   = carnet;
        this->nombre   = nombre;
        this->apellido = apellido;
        this->carrera  = carrera;
        this->semestre = semestre;
    }
};

#endif