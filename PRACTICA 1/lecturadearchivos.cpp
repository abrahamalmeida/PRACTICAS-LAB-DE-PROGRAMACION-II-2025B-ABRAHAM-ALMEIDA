#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h>

using namespace std;

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

string Minusculas(const string& texto) {
    string TextoAMinusculas = texto;
    transform(TextoAMinusculas.begin(), TextoAMinusculas.end(), TextoAMinusculas.begin(), ::tolower);
    return TextoAMinusculas;
}

void resaltarCoincidencias(string linea, const string& palabraBuscada) {
    string lineaMinuscula = Minusculas(linea);
    string palabraMinuscula = Minusculas(palabraBuscada);
    size_t posicion = lineaMinuscula.find(palabraMinuscula);

    while (posicion != string::npos) {
        cout << linea.substr(0, posicion);
        cambiarColor(10);
        cout << linea.substr(posicion, palabraBuscada.length());
        cambiarColor(7);

        linea = linea.substr(posicion + palabraBuscada.length());
        lineaMinuscula = lineaMinuscula.substr(posicion + palabraBuscada.length());
        posicion = lineaMinuscula.find(palabraMinuscula);
    }
    cout << linea;
}

int main() {
    string archivoTexto = "texto.txt";
    ifstream archivo(archivoTexto);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    } 

    string linea;
    string palabraBuscada;
    char repetir;

    do {
        cout << "Por favor, ingrese la palabra o caracter que desea buscar: ";
        getline(cin, palabraBuscada);

        if (palabraBuscada.empty()) {
            cout << "Error, no se permiten entradas vacias.." << endl;
            continue;
        }

        int coincidenciasTotal = 0;
        archivo.clear();
        archivo.seekg(0);

        while (getline(archivo, linea)) {
            string lineaMinuscula = Minusculas(linea);
            string palabraMinuscula = Minusculas(palabraBuscada);
            size_t posicion = lineaMinuscula.find(palabraMinuscula);

            if (posicion != string::npos) {
                resaltarCoincidencias(linea, palabraBuscada);
                size_t contador = 0;
                while (posicion != string::npos) {
                    contador++;
                    posicion = lineaMinuscula.find(palabraMinuscula, posicion + 1);
                }
                coincidenciasTotal += contador; 
                cout << endl;
            } else { 
                cout << linea << endl; 
            }
        } 

        cout << "Total de coincidencias para \"" << palabraBuscada << "\": " << coincidenciasTotal << endl;

        // Preguntar si desea realizar otra búsqueda
        cout << "¿Desea buscar otra palabra o caracter? (S/N): ";
        cin >> repetir;
        cin.ignore(); // Limpiar el buffer de entrada
    } while (repetir == 'S' || repetir == 's');

    archivo.close();

    return 0;
}