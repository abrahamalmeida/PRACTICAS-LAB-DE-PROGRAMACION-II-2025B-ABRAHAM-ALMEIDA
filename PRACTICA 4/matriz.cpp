#include "matriz.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;
using namespace MatrizLib;

void Matriz::reservarMemoria() {
    datos = new double*[filas];
    for (int i = 0; i < filas; ++i) {
        datos[i] = new double[columnas]{}; // se inicializan en cero
    }
}

void Matriz::liberarMemoria() {
    for (int i = 0; i < filas; ++i) {
        delete[] datos[i];
    }
    delete[] datos;
}

Matriz::Matriz() : datos(nullptr), filas(0), columnas(0) {}

Matriz::Matriz(int cantidadFilas, int cantidadColumnas) : filas(cantidadFilas), columnas(cantidadColumnas) {
    if (filas <= 0 || columnas <= 0)
        throw invalid_argument("Dimensiones invalidas");
    reservarMemoria();
}

Matriz::~Matriz() {
    liberarMemoria();
}

void Matriz::llenarMatriz() {
    cout << "Ingrese los elementos de la matriz (" << filas << "x" << columnas << "):\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            while (!(cin >> datos[i][j])) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida. Reingrese: ";
            }
        }
    }
}

void Matriz::mostrarMatriz() const {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << setw(10) << datos[i][j] << " ";
        }
        cout << endl;
    }
}

Matriz Matriz::transpuesta() const {
    Matriz resultado(columnas, filas);
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            resultado.datos[j][i] = datos[i][j];
    return resultado;
}

double Matriz::determinante() const {
    if (filas != columnas)
        throw logic_error("La matriz no es cuadrada");

    if (filas == 1) return datos[0][0];
    if (filas == 2) return datos[0][0]*datos[1][1] - datos[0][1]*datos[1][0];

    double det = 0;
    for (int p = 0; p < columnas; ++p) {
        Matriz menor(filas - 1, columnas - 1);
        for (int i = 1; i < filas; ++i) {
            int colM = 0;
            for (int j = 0; j < columnas; ++j) {
                if (j == p) continue;
                menor.datos[i - 1][colM++] = datos[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * datos[0][p] * menor.determinante();
    }
    return det;
}

Matriz Matriz::suma(const Matriz& otra) const {
    if (filas != otra.filas || columnas != otra.columnas)
        throw logic_error("\nLas matrices no tienen las mismas dimensiones");
    Matriz resultado(filas, columnas);
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            resultado.datos[i][j] = datos[i][j] + otra.datos[i][j];
    return resultado;
}

Matriz Matriz::multiplicacion(const Matriz& otra) const {
    if (columnas != otra.filas)
        throw logic_error("Dimensiones incompatibles para la multiplicacion");
    Matriz resultado(filas, otra.columnas);
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < otra.columnas; ++j)
            for (int k = 0; k < columnas; ++k)
                resultado.datos[i][j] += datos[i][k] * otra.datos[k][j];
    return resultado;
}

bool Matriz::esIgual(const Matriz& otra) const {
    if (filas != otra.filas || columnas != otra.columnas)
        return false;
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            if (datos[i][j] != otra.datos[i][j])
                return false;
    return true;
}

void Matriz::anadirFila() {
    double** nuevosDatos = new double*[filas + 1];
    for (int i = 0; i < filas; ++i)
        nuevosDatos[i] = datos[i];
    nuevosDatos[filas] = new double[columnas]{};
    delete[] datos;
    datos = nuevosDatos;
    ++filas;
}

void Matriz::anadirColumna() {
    for (int i = 0; i < filas; ++i) {
        double* nuevaFila = new double[columnas + 1];
        for (int j = 0; j < columnas; ++j)
            nuevaFila[j] = datos[i][j];
        nuevaFila[columnas] = 0;
        delete[] datos[i];
        datos[i] = nuevaFila;
    }
    ++columnas;
}

Matriz MatrizLib::crearMatriz(int cantidadFilas, int cantidadColumnas) {
    return Matriz(cantidadFilas, cantidadColumnas);
}
