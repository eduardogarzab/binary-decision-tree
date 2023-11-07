#include <iostream>
#include <fstream>
#include <string>
#include "arbol.h"

using namespace std;

/*
Un árbol de decisión binario es una estructura jerárquica de datos utilizada en el campo del aprendizaje automático y la inteligencia artificial. Es una forma de representar decisiones y sus posibles consecuencias en una serie de bifurcaciones.
En un árbol de decisión binario, cada nodo tiene, como máximo, dos hijos: uno para representar la decisión afirmativa (o "verdadera") y otro para la decisión negativa (o "falsa"). Esto significa que en cada nivel del árbol, se toma una decisión basada en un atributo y, en función del resultado, se avanza hacia uno de los dos hijos.
Cada nodo interno del árbol representa una condición sobre un atributo, mientras que las hojas del árbol representan resultados finales o clasificaciones. Por ejemplo, si estamos clasificando animales, un nodo interno podría representar la condición "¿tiene plumas?" y las hojas podrían representar clasificaciones como "pájaro" o "mamífero".
Un árbol de decisión es construido a través de un proceso llamado aprendizaje del árbol de decisión, donde el modelo examina los datos de entrenamiento y elige los atributos y las condiciones que mejor separan las clases de interés.
Los árboles de decisión binarios son muy utilizados en el aprendizaje automático y tienen muchas aplicaciones, incluyendo clasificación, regresión y tareas de toma de decisiones en general. Además, son relativamente fáciles de interpretar, lo que los convierte en una herramienta valiosa para comprender cómo se toman decisiones en un modelo pues a medida que se recorren las ramas, se toman decisiones sucesivas hasta llegar a una hoja del árbol, que representa una predicción o una clasificación.
Por ejemplo, supongamos que tenemos la siguiente tabla de datos sobre frutas
Fruta
Color
Tamaño
Clase
1
Rojo
Grande
Manzana
2
Rojo
Pequeño
Cereza
3
Amarillo
Grande
Pera
4
Amarillo
Pequeño
Limón

En base a ella se puede generar el siguiente árbol binario de decisión en dónde los hijos izquierdos corresponden a una respuesta positiva y los derechos a una respuesta negativa

Se te pide que escribas un programa en C++ que utilizando la clase Árbol que se desarrolló en el curso pueda ir recorriendo el árbol, pidiendo los valores definidos en cada nodo hasta que llegue a una clasificación o a decir que no tiene respuesta.
Los datos para poblar el árbol se leerán de un archivo de texto que tendrá la información del recorrido de acuerdo a lo indicado en su primera línea. Por ejemplo, para el árbol anterior si el recorrido fuera preorden, el contenido del archivo sería (se agregan los nodos nulos para identificar cuando se llegó a un nodo hoja):
Preorden
Color rojo
Tamanio grande
Fruta Manzana
Nulo
Nulo
Fruta Cereza
Nulo
Nulo
Color amarillo
Tamanio Grande
Fruta Pera
Nulo
Nulo
Fruta Limon
Nulo
Nulo
Sin respuesta
Nulo
Nulo
*/

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

Nodo<string> *obtenerArbol(ListaEncadenada<string> listaInfo, string &tipoRecorrido) {
    tipoRecorrido = listaInfo.traerDatosInicio();
    listaInfo.borrarElementoInicio(); // Obtiene el tipo de recorrido y lo saca

    Nodo<string> *raiz = nullptr; // Inicializa la raíz como nullptr
    Arbol<string> arbol; // Creamos un objeto Arbol

    if (tipoRecorrido == "Preorden") {
        raiz = arbol.agregarPreOrden(listaInfo);
        cout << "\nRecorrido en Preorden\n" << endl;
        arbol.recorridoPreOrden(raiz);
    } else if (tipoRecorrido == "Inorden") {
        raiz = arbol.agregarInOrden(listaInfo);
        if(raiz == nullptr) {
            cout << "El arbol no esta balanceado" << endl;
        } else {
            cout << "\nRecorrido en Inorden\n" << endl;
            arbol.recorridoInOrden(raiz);
        }
    } else if (tipoRecorrido == "Postorden") {
        raiz = arbol.agregarPostOrden(listaInfo);
        cout << "\nRecorrido en Postorden\n" << endl;
        arbol.recorridoPostOrden(raiz);
    }

    return raiz;
}

void clasificaInfo(Nodo<string> *raiz) {
    if (raiz) {
        Arbol<string> arbol(raiz); // Creamos el objeto Arbol con la raíz

        bool continuar = true;

        while (continuar) {
            cout << "\nClasificar una entrada (S/N): ";
            char respuesta;
            cin >> respuesta;

            if (respuesta == 'N' || respuesta == 'n') {
                cout << "Saliendo..." << endl;
                continuar = false; // Cambia la variable continuar para salir del bucle
            } else if (respuesta == 'S' || respuesta == 's') {
                arbol.clasificar();
            }
        }
    } else {
        cout << "No se pudo crear el arbol" << endl;
    }
}

int main() {
    system("cls");

    string nombreArchivo = "infoArbol.txt";
    string tipoRecorrido;
    cout << "Ingresa el nombre del archivo: ";
    cin >> nombreArchivo;

    ListaEncadenada<string> listaInfo = obtenerlistaInfo(nombreArchivo);
    Nodo<string> *raiz = obtenerArbol(listaInfo, tipoRecorrido);

    clasificaInfo(raiz);

    return 0;
}