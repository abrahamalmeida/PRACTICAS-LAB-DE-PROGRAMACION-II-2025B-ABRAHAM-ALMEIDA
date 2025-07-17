#include "GestorPersonas.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void GestorPersonas::mostrarMenu() {
    cout << "\n   Menu de Gestion de Personas | Evaluacion 3    \n";
    cout << "\n 1. Agregar una persona\n 2. Buscar por cedula\n 3. Listar personas activas\n";
    cout << " 4. Buscar persona por edad\n 5. Eliminar persona (logicamente)\n 6. Editar una persona\n";
    cout << " 7. Mostrar personas mayores\n 8. Listar todas las personas (Activas|Inactivas)\n 9. Salir del programa\n\nOpcion: ";
}

void GestorPersonas::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#endif
}

vector<Persona> GestorPersonas::leerArchivo() {
    vector<Persona> personas;
    ifstream archivoBin(archivo, ios::binary);
    if (!archivoBin) return personas;

    while (true) {
        size_t tamNom, tamApe;
        Persona p;

        archivoBin.read(reinterpret_cast<char*>(&tamNom), sizeof(tamNom));
        if (archivoBin.eof()) break;
        p.nombre.resize(tamNom);
        archivoBin.read(&p.nombre[0], tamNom);

        archivoBin.read(reinterpret_cast<char*>(&tamApe), sizeof(tamApe));
        p.apellido.resize(tamApe);
        archivoBin.read(&p.apellido[0], tamApe);

        archivoBin.read(reinterpret_cast<char*>(&p.cedula), sizeof(p.cedula));
        archivoBin.read(reinterpret_cast<char*>(&p.edad), sizeof(p.edad));
        archivoBin.read(reinterpret_cast<char*>(&p.activo), sizeof(p.activo));

        personas.push_back(p);
    }

    archivoBin.close();
    return personas;
}

void GestorPersonas::guardarArchivo(const vector<Persona>& personas) {
    ofstream archivoBin(archivo, ios::binary);
    for (const auto& p : personas) {
        size_t tamNom = p.nombre.size();
        archivoBin.write(reinterpret_cast<const char*>(&tamNom), sizeof(tamNom));
        archivoBin.write(p.nombre.c_str(), tamNom);

        size_t tamApe = p.apellido.size();
        archivoBin.write(reinterpret_cast<const char*>(&tamApe), sizeof(tamApe));
        archivoBin.write(p.apellido.c_str(), tamApe);

        archivoBin.write(reinterpret_cast<const char*>(&p.cedula), sizeof(p.cedula));
        archivoBin.write(reinterpret_cast<const char*>(&p.edad), sizeof(p.edad));
        archivoBin.write(reinterpret_cast<const char*>(&p.activo), sizeof(p.activo));
    }
}

void GestorPersonas::agregarPersona() {
    Persona p;
    cout << " Nombre: "; getline(cin, p.nombre);
    cout << " Apellido: "; getline(cin, p.apellido);
    cout << " Cedula: "; cin >> p.cedula;
    cout << " Edad: "; cin >> p.edad;
    p.activo = true;
    cin.ignore();

    auto personas = leerArchivo();
    personas.push_back(p);
    guardarArchivo(personas);
    cout << " Persona agregada exitosamente.\n";
}

void GestorPersonas::buscarPorCedula() {
    int ci;
    cout << " \n Ingrese la cedula a buscar: ";
    cin >> ci; cin.ignore();

    for (const auto& p : leerArchivo()) {
        if (p.cedula == ci) {
            cout << " \n Persona encontrada:\n";
            p.mostrar();
            return;
        }
    }

    cout << " No se encontro una persona con esa cedula.\n";
}

void GestorPersonas::listarPersonas(bool incluirInactivos) {
    auto personas = leerArchivo();
    bool mostradas = false;

    for (const auto& p : personas) {
        if (incluirInactivos || p.activo) {
            p.mostrar();
            mostradas = true;
        }
    }

    if (!mostradas) cout << " No hay personas para mostrar.\n";
}

void GestorPersonas::buscarPorEdad() {
    int edad;
    cout << " \n Ingrese edad a buscar: ";
    cin >> edad; cin.ignore();

    auto personas = leerArchivo();
    bool encontrada = false;
    for (const auto& p : personas) {
        if (p.edad == edad && p.activo) {
            p.mostrar();
            encontrada = true;
        }
    }

    if (!encontrada) cout << " No se encontraron personas con esa edad.\n";
}

void GestorPersonas::eliminarPersona() {
    int ci;
    cout << " \nIngrese cedula a eliminar: ";
    cin >> ci; cin.ignore();

    auto personas = leerArchivo();
    bool encontrada = false;

    for (auto& p : personas) {
        if (p.cedula == ci) {
            p.activo = false;
            encontrada = true;
            break;
        }
    }

    if (encontrada) {
        guardarArchivo(personas);
        cout << " Persona desactivada.\n";
    } else {
        cout << " No se encontro una persona con esa cedula.\n";
    }
}

void GestorPersonas::editarPersona() {
    int ci;
    cout << "\n Ingrese cedula a editar: ";
    cin >> ci; cin.ignore();

    auto personas = leerArchivo();
    for (auto& p : personas) {
        if (p.cedula == ci) {
            cout << "\n Datos actuales:\n";
            p.mostrar();

            string input;
            cout << " Nuevo nombre (" << p.nombre << "): ";
            getline(cin, input);
            if (!input.empty()) p.nombre = input;

            cout << " Nuevo apellido (" << p.apellido << "): ";
            getline(cin, input);
            if (!input.empty()) p.apellido = input;

            cout << " Nueva edad (" << p.edad << "): ";
            getline(cin, input);
            if (!input.empty()) p.edad = stoi(input);

            cout << " Estado (1=Activo, 0=Inactivo) [" << p.activo << "]: ";
            getline(cin, input);
            if (!input.empty()) p.activo = (input == "1");

            guardarArchivo(personas);
            cout << " Datos actualizados.\n";
            return;
        }
    }

    cout << " No se encontro una persona con esa cedula.\n";
}

void GestorPersonas::mostrarMayores() {
    auto personas = leerArchivo();
    vector<Persona> activas;

    for (const auto& p : personas)
        if (p.activo) activas.push_back(p);

    if (activas.empty()) {
        cout << "No hay personas activas.\n";
        return;
    }

    int maxEdad = max_element(activas.begin(), activas.end(),
        [](const Persona& a, const Persona& b) { return a.edad < b.edad; })->edad;

    cout << " Personas de mayor edad (" << maxEdad << "):\n";
    for (const auto& p : activas)
        if (p.edad == maxEdad) p.mostrar();
}
