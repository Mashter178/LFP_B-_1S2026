#ifndef NOTA_H
#define NOTA_H

#include <string>

struct Nota {
    int carnet;        
    int codigo_curso;     
    double nota;          
    std::string ciclo;    
    int anio;             

    Nota(int carnet, int codigo_curso, double nota,
        std::string ciclo, int anio) {
        this->carnet       = carnet;
        this->codigo_curso = codigo_curso;
        this->nota         = nota;
        this->ciclo        = ciclo;
        this->anio         = anio;
    }
};

#endif