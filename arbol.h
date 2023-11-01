#include <iostream>
#include "fila.h"
#include "nodo.h"

using namespace std;

template <class T>
class Arbol{
    public:
    Arbol();
    bool agregarNodo(T info);
    bool borrarNodo(T info);
    void recorridoPostOrden(Nodo<T> *nodo);
    void recorridoPreOrden(Nodo<T> *nodo);
    bool agregarPreOrden(Fila<string> filaInfo);
    void recorridoInOrden(Nodo<T> *nodo);
    void recorridoPorNiveles(Nodo<T> *nodo);
    bool esHoja(Nodo<T> *nodo);
    Nodo<T> *predecesor(Nodo<T> *nodo);
    Nodo<T> *sucesor(Nodo<T> *nodo);
    Nodo<T> *padre(T info);
    void visitaNodo(Nodo<T> *nodo);
    Nodo<T> *getRaiz();

    private:
    Nodo<T> *raiz;
};

template <class T>
Arbol<T>::Arbol() {
    raiz = nullptr;
}

template <class T>
bool Arbol<T>::agregarNodo(T info) {
    Nodo<T> *nuevo = new Nodo<T>(info);
    if (nuevo == nullptr) {
        return false;
    }

    if (raiz == nullptr) {
        raiz = nuevo;
        return true;
    }

    Nodo<T> *auxiliar = raiz;
    while (auxiliar != nullptr) {
        if (info < auxiliar->getInfo()) {
            if (auxiliar->getIzquierda() == nullptr) {
                auxiliar->setIzquierda(nuevo);
                return true;
            } else {
                auxiliar = auxiliar->getIzquierda();
            }
        } else {
            if (auxiliar->getDerecha() == nullptr) {
                auxiliar->setDerecha(nuevo);
                return true;
            } else {
                auxiliar = auxiliar->getDerecha();
            }
        }
    }
    return false;
}

template <class T>
bool Arbol<T>::borrarNodo(T info) {
    Nodo<T>* auxiliar = raiz;
    Nodo<T>* nodoPadre = nullptr;
    Nodo<T>* nodoPredecesor = nullptr;
    T infoPredecesor;
    
    if (auxiliar == nullptr) {
        return false; // El árbol está vacío, no se puede borrar
    }
    
    // Buscar el nodo a borrar y su padre
    while (auxiliar != nullptr && auxiliar->getInfo() != info) {
        nodoPadre = auxiliar;
        if (info < auxiliar->getInfo()) {
            auxiliar = auxiliar->getIzquierda();
        } else {
            auxiliar = auxiliar->getDerecha();
        }
    }

    if (auxiliar == nullptr) {
        return false; // No se encontró el nodo a borrar
    }

    int cantidadHijos = auxiliar->cantidadHijos();

    if (cantidadHijos == 0) {
        if (nodoPadre == nullptr) {
            delete raiz;
            raiz = nullptr;
        } else if (auxiliar == nodoPadre->getIzquierda()) {
            delete auxiliar;
            nodoPadre->setIzquierda(nullptr);
        } else {
            delete auxiliar;
            nodoPadre->setDerecha(nullptr);
        }
    } else if (cantidadHijos == 1) {
        Nodo<T>* hijo = (auxiliar->getIzquierda() != nullptr) ? auxiliar->getIzquierda() : auxiliar->getDerecha();
        if (nodoPadre == nullptr) {
            delete raiz;
            raiz = hijo;
        } else if (auxiliar == nodoPadre->getIzquierda()) {
            delete auxiliar;
            nodoPadre->setIzquierda(hijo);
        } else {
            delete auxiliar;
            nodoPadre->setDerecha(hijo);
        }
    } else {
        nodoPredecesor = predecesor(auxiliar);
        infoPredecesor = nodoPredecesor->getInfo();
        borrarNodo(infoPredecesor);
        auxiliar->setInfo(infoPredecesor);
    }

    return true; // Borrado exitoso
}

template <typename T>
void Arbol<T>::recorridoPostOrden(Nodo<T> *nodo) {
    if(nodo == nullptr) {
        return;
    }
    if (nodo->getIzquierda() != nullptr){
        recorridoPostOrden(nodo->getIzquierda());
    }
    if (nodo->getDerecha() != nullptr) {
        recorridoPostOrden(nodo->getDerecha());
    }
    visitaNodo(nodo);
}

template<typename T>
void Arbol<T>::recorridoPreOrden(Nodo<T> *nodo) {
    if(nodo == nullptr) {
        return;
    }
    visitaNodo(nodo);
    if (nodo->getIzquierda() != nullptr){
        recorridoPreOrden(nodo->getIzquierda());
    }
    if (nodo->getDerecha() != nullptr) {
        recorridoPreOrden(nodo->getDerecha());
    }
}

template<typename T>
bool Arbol<T>::agregarPreOrden(Fila<string> filaInfo) {
    return true;
}

template<typename T>
void Arbol<T>::recorridoInOrden(Nodo<T> *nodo) {
    if(nodo == nullptr) {
        return;
    }
    if (nodo->getIzquierda() != nullptr){
        recorridoInOrden(nodo->getIzquierda());
    }
    visitaNodo(nodo);
    if (nodo->getDerecha() != nullptr) {
        recorridoInOrden(nodo->getDerecha());
    }
}

template<typename T>
void Arbol<T>::recorridoPorNiveles(Nodo<T> *nodo){
    cout << "Recorrido por niveles" << endl;
}

template <typename T>
bool Arbol<T>::esHoja(Nodo<T> *nodo) 
{
	bool bandera = false;
	Nodo<T> *hijoIzquierdo;
	Nodo<T>* hijoDerecho;

	if (nodo == nullptr) 
	{
		bandera = true;
	}
	else 
	{
		hijoIzquierdo = nodo->getIzquierda();
		hijoDerecho = nodo->getDerecha();
		if (hijoIzquierdo == nullptr && hijoDerecho == nullptr) 
		{
			bandera = true;
		}

	}
	return bandera;
}

template <class T>
Nodo<T> *Arbol<T>::predecesor(Nodo<T> *nodo){
    Nodo<T> *aux = nodo;
    if(aux != nullptr){
        aux = nodo->getIzquierda();
        if(aux != nullptr){
            while(aux->getDerecha() != nullptr){
                aux = aux->getDerecha();
            }
        }
    }
    return aux;
}

template <class T>
Nodo<T> *Arbol<T>::sucesor(Nodo<T> *nodo){
    Nodo<T> *aux = nodo;
    if(aux != nullptr){
        aux = nodo->getDerecha();
        if(aux != nullptr){
            while(aux->getIzquierda() != nullptr){
                aux = aux->getIzquierda();
            }
        }
    }
    return aux;
}

template <typename T>
Nodo<T> *Arbol<T>::padre(T info){
    Nodo<T>* aux;
    Nodo<T>* padre;
    aux = raiz;
    padre = nullptr;

    if (aux != nullptr){

        while (aux->getInfo() != info && aux != nullptr){
            padre = aux;
        
            if (info < aux->getInfo())
                aux = aux->getIzquierda();
            else
                aux = aux->getDerecha();
        }

        if (aux == nullptr)
            padre = nullptr;

        return padre;
    }
}

template <class T>
void Arbol<T>::visitaNodo(Nodo<T> *nodo){
    if(nodo != nullptr)
        cout << nodo->getInfo() << endl;
}

template <class T>
Nodo<T> *Arbol<T>::getRaiz() {
    return raiz;
}