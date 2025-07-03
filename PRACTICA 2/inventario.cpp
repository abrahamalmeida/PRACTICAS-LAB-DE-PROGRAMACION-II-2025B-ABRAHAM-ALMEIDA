#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> // Para el strcmp 
#include <cstdlib> // Para system()

using namespace std;

#define COLOR_NARANJA "\033[38;5;208m"
#define RESET_COLOR "\033[0m"

// Estructura para representar un producto
struct Producto {
    char codigo[10]; 
    char nombre[30];
    float precio;
    int stock;
    char categoria[30];
    bool activo;
};

// Arreglo dinamico 
vector<Producto> productos;

void limpiarPantalla() {
        system("cls"); 
}

// Funcion para mostrar el menu
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


void agregarProducto() {
    limpiarPantalla();
    Producto nuevo;
    cout << "\n  Agregar Nuevo Producto: \n\n";
    cout << "Codigo: ";
    cin.ignore();
    cin.getline(nuevo.codigo, 10);
    cout << "Nombre: ";
    cin.getline(nuevo.nombre, 30);
    cout << "Precio: ";
    cin >> nuevo.precio;
    cout << "Stock: ";
    cin >> nuevo.stock;
    cout << "Categoria: ";
    cin.ignore();
    cin.getline(nuevo.categoria, 30);
    nuevo.activo = true;

    productos.push_back(nuevo);
    cout << "Producto agregado con exito.\n";
}

// Funcion para mostrar todos los productos activos
void mostrarProductosActivos() {
    limpiarPantalla();
    if (productos.empty()) {
        cout << "No hay productos almacenados.\n";
        return;
    }
    cout << "\n  Productos Activos: \n\n";
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].activo) {
            cout << i + 1 << ". Codigo: " << productos[i].codigo << ", Nombre: " << productos[i].nombre
                 << ", Precio: " << productos[i].precio << ", Stock: " << productos[i].stock
                 << ", Categoria: " << productos[i].categoria << endl;
        }
    }
}

// Funcion para mostrar productos por categoria
void mostrarProductosPorCategoria() {
    limpiarPantalla();
    if (productos.empty()) {
        cout << "No hay productos almacenados.\n";
        return;
    }
    char categoria[30];
    cout << "\nIngrese la categoria: ";
    cin.ignore();
    cin.getline(categoria, 30);

    cout << "\n Productos en la categoria: " << categoria << " \n\n";
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].activo && strcmp(productos[i].categoria, categoria) == 0) {
            cout << "Codigo: " << productos[i].codigo << ", Nombre: " << productos[i].nombre
                 << ", Precio: " << productos[i].precio << ", Stock: " << productos[i].stock << endl;
        }
    }
}

// Funcion para buscar un producto por codigo
void buscarProductoPorCodigo() {
    limpiarPantalla();
    if (productos.empty()) {
        cout << "No hay productos almacenados.\n";
        return;
    }
    char codigo[10];
    cout << "\nIngrese el codigo del producto: ";
    cin.ignore();
    cin.getline(codigo, 10);

    for (size_t i = 0; i < productos.size(); i++) {
        if (strcmp(productos[i].codigo, codigo) == 0 && productos[i].activo) {
            cout << "\n Producto Encontrado: \n";
            cout << "Codigo: " << productos[i].codigo << ", Nombre: " << productos[i].nombre
                 << ", Precio: " << productos[i].precio << ", Stock: " << productos[i].stock
                 << ", Categoria: " << productos[i].categoria << endl;
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// Funcion para modificar un producto
void modificarProducto() {
    limpiarPantalla();
    if (productos.empty()) {
        cout << "No hay productos almacenados.\n";
        return;
    }
    char codigo[10];
    cout << "\nIngrese el codigo del producto a modificar: ";
    cin.ignore();
    cin.getline(codigo, 10);

    for (size_t i = 0; i < productos.size(); i++) {
        if (strcmp(productos[i].codigo, codigo) == 0 && productos[i].activo) {
            cout << "\n Modificar Producto: \n";
            cout << "Nuevo Precio: ";
            cin >> productos[i].precio;
            cout << "Nuevo Stock: ";
            cin >> productos[i].stock;
            cout << "Nueva Categoria: ";
            cin.ignore();
            cin.getline(productos[i].categoria, 30);

            cout << "Producto modificado con exito.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}



// Funcion para eliminar un producto (borrado logico)
void eliminarProducto() {
    limpiarPantalla();
    if (productos.empty()) {
        cout << "No hay productos almacenados.\n";
        return;
    }
    char codigo[10];
    cout << "\nIngrese el codigo del producto a eliminar: ";
    cin.ignore();
    cin.getline(codigo, 10);

    for (size_t i = 0; i < productos.size(); i++) {
        if (strcmp(productos[i].codigo, codigo) == 0 && productos[i].activo) {
            productos[i].activo = false;
            cout << "Producto eliminado (borrado logico) con exito.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// Funcion para recuperar un producto borrado (o marcarlo como activo)
void recuperarProducto() {
    limpiarPantalla();
    if (productos.empty()) {
        cout << "No hay productos almacenados.\n";
        return;
    }
    char codigo[10];
    cout << "\nIngrese el codigo del producto a recuperar: ";
    cin.ignore();
    cin.getline(codigo, 10);

    for (size_t i = 0; i < productos.size(); i++) {
        if (strcmp(productos[i].codigo, codigo) == 0 && !productos[i].activo) {
            productos[i].activo = true;
            cout << "Producto recuperado con exito.\n";
            return;
        }
    }
    cout << "Producto no encontrado o ya está activo.\n";
}

// Funcion para guardar los datos en un archivo binario
void guardarEnArchivo(const string& nombreArchivo) {
    limpiarPantalla();
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return;
    }
    size_t cantidad = productos.size();
    archivo.write(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
    archivo.write(reinterpret_cast<char*>(productos.data()), cantidad * sizeof(Producto));
    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << " exitosamente.\n";
}

// Funcion para cargar los datos desde un archivo binario
void cargarDesdeArchivo(const string& nombreArchivo) {
    limpiarPantalla();
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo para lectura.\n";
        return;
    }
    size_t cantidad;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

    productos.resize(cantidad);
    archivo.read(reinterpret_cast<char*>(productos.data()), cantidad * sizeof(Producto));

    archivo.close();
    cout << "Datos cargados desde " << nombreArchivo << " exitosamente.\n";
}

// El main:
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