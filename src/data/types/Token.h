#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Tipos de Token
enum TokenType {
    // Datos
    ENTERO,
    DECIMAL,
    TEXTO,
    TEXTO_COMPUESTO,
    CICLO,

    // Simbolos
    COMA,

    // Especiales
    FIN_LINEA,       // Salto de linea
    FIN_ARCHIVO,     // Fin del archivo
    DESCONOCIDO      // Cualquier cosa rara
};

// Estructura del Token
struct Token {
    TokenType tipo;   // ¿Qué tipo es?
    std::string valor; // ¿Qué valor tiene?

    // Constructor
    Token(TokenType tipo, std::string valor) {
        this->tipo = tipo;
        this->valor = valor;
    }
};

#endif