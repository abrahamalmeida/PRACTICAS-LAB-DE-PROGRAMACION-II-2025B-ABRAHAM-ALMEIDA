#include <iostream>
#include "GestorPersonas.h"

using namespace std;

int main() {
    GestorPersonas gestor;
    int opcion;

    do {
        gestor.limpiarPantalla();
        gestor.mostrarMenu();
        cin >> opcion;
        cin.ignore();
        gestor.limpiarPantalla();

        switch (opcion) {
            case 1: gestor.agregarPersona(); break;
            case 2: gestor.buscarPorCedula(); break;
            case 3: gestor.listarPersonas(false); break;
            case 4: gestor.buscarPorEdad(); break;
            case 5: gestor.eliminarPersona(); break;
            case 6: gestor.editarPersona(); break;
            case 7: gestor.mostrarMayores(); break;
            case 8: gestor.listarPersonas(true); break;
            case 9: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opción no válida." << endl; break;
        }

        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }

    } while (opcion != 9);

    return 0;
}
