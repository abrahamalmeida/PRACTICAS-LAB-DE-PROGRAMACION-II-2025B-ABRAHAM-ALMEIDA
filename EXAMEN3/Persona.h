#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
public:
    std::string nombre;
    std::string apellido;
    int cedula;
    int edad;
    bool activo;

    Persona(std::string nom = "", std::string ape = "", int ci = 0, int ed = 0, bool act = true);

    void mostrar() const;
};

#endif
