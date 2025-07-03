#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
using namespace std;

void limpiarPantalla() {
    system("cls");
}

void setColor(int codigoColor) {
    cout << "\033[38;5;" << codigoColor << "m";
}

void resetearColor() {
    cout << "\033[0m";
}

class Publicacion {
protected:
    string titulo;
    string autor;
    int year;

public:
    Publicacion(string titulo, string autor, int year)
        : titulo(titulo), autor(autor), year(year) {}

    virtual void mostrarInformacion() {
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Año de publicacion: " << year << endl;
    }

    string obtenerTitulo() const { return titulo; }
    int obtenerYear() const { return year; }

    virtual ~Publicacion() {}
};

class Libro : public Publicacion {
private:
    int numeroPaginas;

public:
    Libro(string titulo, string autor, int year, int numeroPaginas)
        : Publicacion(titulo, autor, year), numeroPaginas(numeroPaginas) {}

    void mostrarInformacion() override {
        Publicacion::mostrarInformacion();
        cout << "Numero de paginas: " << numeroPaginas << endl;
        cout << "Tipo: Libro" << endl;
    }
};

class Revista : public Publicacion {
private:
    int numeroEdicion;

public:
    Revista(string titulo, string autor, int year, int numeroEdicion)
        : Publicacion(titulo, autor, year), numeroEdicion(numeroEdicion) {}

    void mostrarInformacion() override {
        Publicacion::mostrarInformacion();
        cout << "Numero de edicion: " << numeroEdicion << endl;
        cout << "Tipo: Revista" << endl;
    }
};

class Periodico : public Publicacion {
private:
    string fecha;

public:
    Periodico(string titulo, string autor, int year, string fecha)
        : Publicacion(titulo, autor, year), fecha(fecha) {}

    void mostrarInformacion() override {
        Publicacion::mostrarInformacion();
        cout << "Fecha del periodico: " << fecha << endl;
        cout << "Tipo: Periodico" << endl;
    }
};

bool validarTexto(const string& texto) {
    return !texto.empty();
}

bool validarYear(int year) {
    return year >= 1500 && year <= 2025;
}

bool validarPositivo(int numero) {
    return numero > 0;
}

void mostrarMenu() {
    limpiarPantalla();
    setColor(208);
    cout << "\n    Menu de Gestion de Biblioteca    \n" << endl;
    resetearColor();
    cout << "1. Agregar Publicacion" << endl;
    cout << "2. Mostrar todas las publicaciones registradas" << endl;
    cout << "3. Salir del programa" << endl;
    cout << "\nIngrese su opcion: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Publicacion** listaPublicaciones = new Publicacion*[10];
    int capacidad = 10;
    int cantidad = 0;

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                if (cantidad >= capacidad) {
                    capacidad *= 2;
                    Publicacion** temporal = new Publicacion*[capacidad];
                    for (int i = 0; i < cantidad; i++)
                        temporal[i] = listaPublicaciones[i];
                    delete[] listaPublicaciones;
                    listaPublicaciones = temporal;
                }

                string titulo, autor;
                int year, tipo;

                setColor(208);
                cout << "\n     Tipo de Publicacion\n\n";
                resetearColor();
                cout << "1. Libro" << endl;
                cout << "2. Revista" << endl;
                cout << "3. Periodico" << endl;
                cout << "\nSeleccione una opcion: ";
                cin >> tipo;
                cin.ignore();

                cout << "\nIngrese el titulo: ";
                getline(cin, titulo);
                if (!validarTexto(titulo)) { cout << "Titulo no valido.\n"; break; }

                cout << "Ingrese el autor: ";
                getline(cin, autor);
                if (!validarTexto(autor)) { cout << "Autor no valido.\n"; break; }

                cout << "Ingrese el año de publicacion: ";
                cin >> year;
                if (!validarYear(year)) { cout << "Año invalido.\n"; break; }

                // Por ahora no pedimos datos extras (paginas, edición, fecha)
                if (tipo == 1) {
                    listaPublicaciones[cantidad++] = new Libro(titulo, autor, year, 0);
                } else if (tipo == 2) {
                    listaPublicaciones[cantidad++] = new Revista(titulo, autor, year, 0);
                } else if (tipo == 3) {
                    listaPublicaciones[cantidad++] = new Periodico(titulo, autor, year, "");
                } else {
                    cout << "Opcion no valida.\n";
                }
                break;
            }

            case 2: {
                limpiarPantalla();
                if (cantidad == 0)
                    cout << "\nNo hay publicaciones registradas.\n";
                else {
                    for (int i = 0; i < cantidad; i++) {
                        cout << "\nPublicacion #" << i + 1 << ":\n";
                        listaPublicaciones[i]->mostrarInformacion();
                    }
                }
                break;
            }

            case 3: {
                cout << "\nSaliendo del programa..." << endl;
                break;
            }

            default:
                cout << "\nOpcion no valida. Intente de nuevo.\n";
        }

        if (opcion != 3) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
        }

    } while (opcion != 3);

    for (int i = 0; i < cantidad; i++) {
        delete listaPublicaciones[i];
    }
    delete[] listaPublicaciones;

    return 0;
}
