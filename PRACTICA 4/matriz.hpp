#ifndef MATRIZ_HPP
#define MATRIZ_HPP

namespace MatrizLib {

class Matriz {
private:
    double** datos;
    int filas;
    int columnas;

    void reservarMemoria();
    void liberarMemoria();

public:
    Matriz();
    Matriz(int cantidadFilas, int cantidadColumnas);
    ~Matriz();

    void llenarMatriz();
    void mostrarMatriz() const;
    Matriz transpuesta() const;
    double determinante() const;
    Matriz suma(const Matriz& otra) const;
    Matriz multiplicacion(const Matriz& otra) const;
    bool esIgual(const Matriz& otra) const;

    void anadirFila();
    void anadirColumna();
};

Matriz crearMatriz(int cantidadFilas, int cantidadColumnas);

} 

#endif
