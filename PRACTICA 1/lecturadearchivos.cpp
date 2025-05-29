#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h>

using namespace std;


void cambiarColor (int color) {
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}

string Minusculas (const string& texto) {
    string TextoAMinusculas = texto;
    transforma(TextoAMinusculas.begin() , TextoAMinusculas.end(), TextoAMinusculas.begin, ::tolower);
    return TextoAMinusculas;
}

void resaltarCoincidencias(string linea, const linea& palabraBuscada) {
    string lineaMinuscula = Minusculas(linea);
    string palabraMinuscula = Minusculas(palabraBuscada);
    size_t posicion = lineaMinuscula.find(palabraMinuscula);



while (posicion != string ::npos) {

cout << linea.substr(0, posicion);
cambiarColor(10);
cout << linea.substr(posicion, palabraBuscada.leght());
    cambiarColor(7);

linea= linea.substr(posicion+palabraBuscada.leght());
lineaMinuscula= lineaMinuscula.substr(posicion + palabraBuscada.leght());
posicion= lineaMinuscula.find(palabraMinuscula);

}

}

int main() {

string archivoTexto = "texto.txt"
ifstream archivo (archivoTexto)

string linea;
string palabraBuscada;
char repetir;

















    return 0;
}