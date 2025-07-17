#include "Persona.h"
#include <iostream>

using namespace std;

Persona::Persona(string nom, string ape, int ci, int ed, bool act)
    : nombre(nom), apellido(ape), cedula(ci), edad(ed), activo(act) {}

void Persona::mostrar() const {
    cout << "\n Nombre: " << nombre << " " << apellido << endl;
    cout << " Cedula: " << cedula << endl;
    cout << " Edad: " << edad << endl;
    cout << " Estado: " << (activo ? "Activo" : "Inactivo") << endl;
}
