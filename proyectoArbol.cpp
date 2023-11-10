#include <iostream>
#include <fstream>
#include <string>
#include "arbol.h"

using namespace std;

ListaEncadenada<string> obtenerlistaInfo(const string &nombreArchivo) {
    ListaEncadenada<string> lista;
    ifstream archivo(nombreArchivo);
    string linea;

    if (archivo.is_open()) { // Si se pudo abrir el archivo
        while (getline(archivo, linea)) { // Lee una línea
            lista.insertarElementoFinal(linea); // Inserta la línea en la lista
        }
        archivo.close();
    } else { // Si no se pudo abrir el archivo
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
    return lista;
}

Arbol<string> obtenerArbol(ListaEncadenada<string> listaInfo, string &tipoRecorrido) {
    tipoRecorrido = listaInfo.traerDatosInicio();
    listaInfo.borrarElementoInicio(); // Obtiene el tipo de recorrido y lo saca

    //Convertir el tipo de recorrido a minusculas
    for (int i = 0; i < tipoRecorrido.length(); i++) {
        tipoRecorrido[i] = tolower(tipoRecorrido[i]);
    }

    Arbol<string> arbol;

    if (tipoRecorrido == "preorden") {
        arbol.agregarPreOrden(listaInfo);

        if (arbol.getRaiz()) {
            cout << "\nRecorrido en Preorden\n" << endl;
            arbol.recorridoPreOrden(arbol.getRaiz());
        }

    } else if (tipoRecorrido == "inorden") {

    } else if (tipoRecorrido == "postorden") {
        arbol.agregarPostOrden(listaInfo);

        if (arbol.getRaiz()) {
            cout << "\nRecorrido en Postorden\n" << endl;
            arbol.recorridoPostOrden(arbol.getRaiz());
        }

    } else {
        cout << "No se identifico el recorrido" << endl;
    }

    return arbol;
}

void clasificaInfo(Arbol<string> arbol) {
    Nodo<string> *raiz = arbol.getRaiz();

    if (raiz) {
        bool continuar = true;

        while (continuar) {
            cout << "\nQuieres clasificar (S/N)? ";
            char respuesta;
            cin >> respuesta;
            cout << endl;

            if (respuesta == 'N' || respuesta == 'n') {
                cout << "Saliendo del programa..." << endl;
                continuar = false; // Cambia la variable continuar para salir del bucle
            } else if (respuesta == 'S' || respuesta == 's') {
                arbol.clasificar();
            }
        }
    } else {
        cout << "\nNo se pudo crear el arbol correctamente" << endl;
    }
}

int main() {
    system("cls");

    string nombreArchivo;
    string tipoRecorrido;
    cout << "Ingresa el nombre del archivo: ";
    cin >> nombreArchivo;

    ListaEncadenada<string> listaInfo = obtenerlistaInfo(nombreArchivo);
    Arbol<string> arbol = obtenerArbol(listaInfo, tipoRecorrido);

    clasificaInfo(arbol);

    return 0;
}