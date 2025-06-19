#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

#define COLOR_NARANJA "\033[38;5;208m"
#define RESET_COLOR "\033[0m"

struct Producto {
    char codigo[10]; 
    char nombre[30];
    float precio;
    int stock;
    char categoria[30];
    bool activo;
};

vector<Producto> productos;

void limpiarPantalla() {
    system("cls");
}

int main() {
    return 0;
}
