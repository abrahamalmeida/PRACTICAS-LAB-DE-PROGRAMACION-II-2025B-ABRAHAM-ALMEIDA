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

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Prueba básica para validar clase Libro
    Libro libroEjemplo("Cien Años de Soledad", "Gabriel Garcia Marquez", 1967, 417);
    libroEjemplo.mostrarInformacion();

    return 0;
}
