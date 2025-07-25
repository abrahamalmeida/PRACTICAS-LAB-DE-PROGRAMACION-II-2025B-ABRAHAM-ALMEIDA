#include "matriz.hpp"
#include <iostream>

using namespace std;
using namespace MatrizLib;

int main() {
    try {
        // crear matrices A y B de 2x2
        Matriz matrizA = crearMatriz(2, 2);
        Matriz matrizB = crearMatriz(2, 2);

        cout << "Llenar matriz A:" << endl;
        matrizA.llenarMatriz();

        cout << "\nLlenar matriz B:" << endl;
        matrizB.llenarMatriz();

        cout << "\nMatriz A:" << endl;
        matrizA.mostrarMatriz();

        cout << "\nMatriz B:" << endl;
        matrizB.mostrarMatriz();

        // Suma
        cout << "\nSuma A + B:" << endl;
        Matriz suma = matrizA.suma(matrizB);
        suma.mostrarMatriz();

        // Multiplicacion
        cout << "\nProducto A * B:" << endl;
        Matriz producto = matrizA.multiplicacion(matrizB);
        producto.mostrarMatriz();

        // Transpuesta de A
        cout << "\nTranspuesta de A:" << endl;
        Matriz transpuesta = matrizA.transpuesta();
        transpuesta.mostrarMatriz();

        // Determinante
        cout << "\nDeterminante de A: " << matrizA.determinante() << endl;

        // Comparacion
        cout << "\nA y B son iguales? ";
        cout << (matrizA.esIgual(matrizB) ? "Si" : "No") << endl;

        // Añadir fila y columna a A
        cout << "\nAgregando una fila a A..." << endl;
        matrizA.anadirFila();
        matrizA.mostrarMatriz();

        cout << "\nAgregando una columna a A..." << endl;
        matrizA.anadirColumna();
        matrizA.mostrarMatriz();

        // Suma con dimensiones distintas
        cout << "\nIntentando sumar A y B con distintas dimensiones:" << endl;
        try {
            Matriz sumaInvalida = matrizA.suma(matrizB);
            sumaInvalida.mostrarMatriz();
        } catch (exception& e) {
            cout << "Error esperado: " << e.what() << endl;
        }

        // Determinante de matriz no cuadrada
        cout << "\nProbando determinante de matriz no cuadrada:" << endl;
        try {
            Matriz noCuadrada = crearMatriz(2, 3);
            noCuadrada.llenarMatriz();
            double det = noCuadrada.determinante();
            cout << "\nDeterminante: " << det << endl;
        } catch (exception& e) {
            cout << "\nError esperado: " << e.what() << endl;
        }

    } catch (exception& e) {
        cout << "\nError en el programa: " << e.what() << endl;
    }

    system("pause");
    return 0;
}
