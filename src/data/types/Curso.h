#ifndef CURSO_H
#define CURSO_H

#include <string>

struct Curso {
    int codigo;
    std::string nombre;
    int creditos;
    int semestre;
    std::string carrera;

    Curso(int codigo, std::string nombre, int creditos,
        int semestre, std::string carrera) {
        this->codigo   = codigo; 
        this->nombre   = nombre; 
        this->creditos = creditos; 
        this->semestre = semestre; 
        this->carrera  = carrera; 
    }
};

#endif