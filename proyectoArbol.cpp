#include <iostream>
#include <fstream>
#include <string>
#include "arbol.h"

using namespace std;

//Eduardo Garza Briceño 611441

ListaEncadenada<string> obtenerlistaInfo(const string &nombreArchivo) {
    // Declaración de variables
    ListaEncadenada<string> lista;
    ifstream archivo(nombreArchivo);
    string linea;

    if (archivo.is_open()) { // Si se pudo abrir el archivo
        while (getline(archivo, linea)) { // Lee una línea
            lista.insertarElementoFinal(linea); // Inserta la línea en la lista
        }
        archivo.close();
    } else { // Si no se pudo abrir el archivo
        cout << "\nNo se pudo abrir el archivo: " << nombreArchivo << endl;
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

    if (tipoRecorrido == "preorden") { // Si el tipo de recorrido es preorden
        arbol.agregarPreOrden(listaInfo); // Agrega los elementos del archivo al árbol en preorden

        if (arbol.getRaiz()) { // Si se pudo crear el árbol correctamente
            cout << "\nRecorrido en Preorden\n" << endl;
            arbol.recorridoPreOrden(arbol.getRaiz()); // Imprime el recorrido en preorden
        }

    } else if (tipoRecorrido == "inorden") {
        cout << "\nEl programa no soporta el recorrido inorden" << endl; // Imprime un mensaje de error

    } else if (tipoRecorrido == "postorden") { // Si el tipo de recorrido es postorden
        arbol.agregarPostOrden(listaInfo); // Agrega los elementos del archivo al árbol en postorden

        if (arbol.getRaiz()) { // Si se pudo crear el árbol correctamente
            cout << "\nRecorrido en Postorden\n" << endl;
            arbol.recorridoPostOrden(arbol.getRaiz()); // Imprime el recorrido en postorden
        }

    } else {
        cout << "No se identifico el recorrido" << endl;
    }

    return arbol;
}

void clasificaInfo(Arbol<string> arbol) {
    Nodo<string> *raiz = arbol.getRaiz(); // Obtiene la raíz del árbol

    if (raiz) { // Si se pudo crear el árbol correctamente
        bool continuar = true;

        while (continuar) { // Mientras el usuario quiera clasificar
            string respuesta;

            cout << "\nQuieres clasificar (S/N)? ";
            cin >> respuesta;
            cout << endl;

            if (respuesta == "N" || respuesta == "n") { // Si el usuario no quiere clasificar
                cout << "Saliendo del programa..." << endl; // Imprime un mensaje y regresa al main para salir del programa
                continuar = false; // Cambia la variable continuar para salir del bucle
            } else if (respuesta == "S" || respuesta == "s") { // Si el usuario quiere clasificar
                arbol.clasificar(); // Llama a la función para clasificar
            }
        }
    } else {
        cout << "\nNo se pudo crear el arbol" << endl;
    }
}

int main() {
    system("cls");

    // Declaración de variables
    string nombreArchivo;
    string tipoRecorrido;

    // Ingreso de datos
    cout << "Ingresa el nombre del archivo: ";
    cin >> nombreArchivo;

    ListaEncadenada<string> listaInfo = obtenerlistaInfo(nombreArchivo); // Obtiene la lista de información del archivo

    if (!listaInfo.estaVacia()) { // Si la lista está vacía
        Arbol<string> arbol = obtenerArbol(listaInfo, tipoRecorrido); // Obtiene el arbol y el tipo de recorrido
        clasificaInfo(arbol); // Llama a la función para clasificar la información
    }

    return 0;
}