#ifndef GESTORPERSONAS_H
#define GESTORPERSONAS_H

#include <vector>
#include "Persona.h"

class GestorPersonas {
private:
    const std::string archivo = "personas.dat";
    std::vector<Persona> leerArchivo();
    void guardarArchivo(const std::vector<Persona>& personas);

public:
    void mostrarMenu();
    void limpiarPantalla();

    void agregarPersona();
    void buscarPorCedula();
    void listarPersonas(bool incluirInactivos = false);
    void buscarPorEdad();
    void eliminarPersona();
    void editarPersona();
    void mostrarMayores();
};

#endif
