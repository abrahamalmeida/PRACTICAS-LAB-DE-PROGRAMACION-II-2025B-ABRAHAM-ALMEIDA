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

// Prototipos
void mostrarMenu();
void agregarProducto();
void mostrarProductosActivos();
void mostrarProductosPorCategoria();
void buscarProductoPorCodigo();
void modificarProducto();
void eliminarProducto();
void recuperarProducto();
void guardarEnArchivo(const string& nombreArchivo);
void cargarDesdeArchivo(const string& nombreArchivo);

void mostrarMenu() {
    cout << COLOR_NARANJA << "\n    Menu del Inventario de Abraham   \n\n" << RESET_COLOR;
    cout << "1. Agregar un nuevo producto\n";
    cout << "2. Mostrar todos los productos activos\n";
    cout << "3. Mostrar productos por categoria\n";
    cout << "4. Buscar un producto por codigo\n";
    cout << "5. Modificar un producto\n";
    cout << "6. Eliminar un producto (borrado logico)\n";
    cout << "7. Recuperar un producto borrado\n";
    cout << "8. Guardar datos en archivo binario\n";
    cout << "9. Cargar datos desde archivo binario\n";
    cout << "10. Salir\n";
    cout << "\nSeleccione una opcion: ";
}

int main() {
    string nombreArchivo = "inventario.bin";
    int opcion;

    do {
        limpiarPantalla();
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                mostrarProductosActivos();
                break;
            case 3:
                mostrarProductosPorCategoria();
                break;
            case 4:
                buscarProductoPorCodigo();
                break;
            case 5:
                modificarProducto();
                break;
            case 6:
                eliminarProducto();
                break;
            case 7:
                recuperarProducto();
                break;
            case 8:
                guardarEnArchivo(nombreArchivo);
                break;
            case 9:
                cargarDesdeArchivo(nombreArchivo);
                break;
            case 10:
                cout << "Saliendo del programa\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
        if (opcion != 10) {
            cout << "\nPorfavor, presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 10);

    return 0;
}
