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

    string obtenerTitulo() const {
        return titulo;
    }

    int obtenerYear() const {
        return year;
    }

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

// Funciones auxiliares
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
    cout << "3. Buscar publicacion por titulo" << endl;
    cout << "4. Buscar publicaciones por año" << endl;
    cout << "5. Eliminar publicacion por titulo" << endl;
    cout << "6. Mostrar estadisticas" << endl;
    cout << "7. Salir del programa" << endl;
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

                if (tipo == 1) {
                    int paginas;
                    cout << "Ingrese el numero de paginas: ";
                    cin >> paginas;
                    if (!validarPositivo(paginas)) { cout << "Numero invalido.\n"; break; }
                    listaPublicaciones[cantidad++] = new Libro(titulo, autor, year, paginas);
                } else if (tipo == 2) {
                    int edicion;
                    cout << "Ingrese el numero de edicion: ";
                    cin >> edicion;
                    if (!validarPositivo(edicion)) { cout << "Numero invalido.\n"; break; }
                    listaPublicaciones[cantidad++] = new Revista(titulo, autor, year, edicion);
                } else if (tipo == 3) {
                    string fecha;
                    cout << "Ingrese la fecha (DD/MM/AAAA): ";
                    cin.ignore();
                    getline(cin, fecha);
                    if (!validarTexto(fecha)) { cout << "Fecha invalida.\n"; break; }
                    listaPublicaciones[cantidad++] = new Periodico(titulo, autor, year, fecha);
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
                limpiarPantalla();
                string busqueda;
                cout << "Ingrese el titulo a buscar: ";
                getline(cin, busqueda);
                bool encontrado = false;

                for (int i = 0; i < cantidad; i++) {
                    if (listaPublicaciones[i]->obtenerTitulo() == busqueda) {
                        listaPublicaciones[i]->mostrarInformacion();
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) cout << "No se encontro una publicacion con ese titulo.\n";
                break;
            }

            case 4: {
                limpiarPantalla();
                int yearBusqueda;
                cout << "Ingrese el año de publicacion a buscar: ";
                cin >> yearBusqueda;
                bool encontrados = false;

                for (int i = 0; i < cantidad; i++) {
                    if (listaPublicaciones[i]->obtenerYear() == yearBusqueda) {
                        listaPublicaciones[i]->mostrarInformacion();
                        encontrados = true;
                    }
                }

                if (!encontrados) cout << "No se encontraron publicaciones en ese año.\n";
                break;
            }

            case 5: {
                limpiarPantalla();
                string tituloEliminar;
                cout << "Ingrese el titulo de la publicacion a eliminar: ";
                getline(cin, tituloEliminar);

                bool eliminado = false;
                for (int i = 0; i < cantidad; i++) {
                    if (listaPublicaciones[i]->obtenerTitulo() == tituloEliminar) {
                        delete listaPublicaciones[i];
                        for (int j = i; j < cantidad - 1; j++) {
                            listaPublicaciones[j] = listaPublicaciones[j + 1];
                        }
                        cantidad--;
                        eliminado = true;
                        cout << "Publicacion eliminada correctamente.\n";
                        break;
                    }
                }

                if (!eliminado) cout << "No se encontro la publicacion.\n";
                break;
            }

            case 6: {
                limpiarPantalla();
                int libros = 0, revistas = 0, periodicos = 0;

                for (int i = 0; i < cantidad; i++) {
                    if (dynamic_cast<Libro*>(listaPublicaciones[i])) libros++;
                    else if (dynamic_cast<Revista*>(listaPublicaciones[i])) revistas++;
                    else if (dynamic_cast<Periodico*>(listaPublicaciones[i])) periodicos++;
                }

                cout << "\nEstadisticas:\n";
                cout << "Libros: " << libros << endl;
                cout << "Revistas: " << revistas << endl;
                cout << "Periodicos: " << periodicos << endl;
                cout << "Total: " << cantidad << " publicaciones\n";
                break;
            }

            case 7: {
                cout << "\nSaliendo del programa...\n";
                break;
            }

            default:
                cout << "\nOpcion no valida. Intente de nuevo.\n";
        }

        if (opcion != 7) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
        }

    } while (opcion != 7);

    for (int i = 0; i < cantidad; i++) {
        delete listaPublicaciones[i];
    }
    delete[] listaPublicaciones;

    return 0;
}
