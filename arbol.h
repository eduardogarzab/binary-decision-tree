#include <iostream>
#include "listaEncadenada.h"
#include "nodo.h"

using namespace std;

template <class T>
class Arbol{
    public:
    Arbol();
    Arbol(Nodo<T> *raiz);
    bool agregarNodo(T info);
    bool borrarNodo(T info);
    void recorridoPostOrden(Nodo<T> *nodo);
    Nodo<T> *agregarPostOrden(ListaEncadenada<T> &listaInfo);
    void recorridoPreOrden(Nodo<T> *nodo);
    Nodo<T> *agregarPreOrden(ListaEncadenada<T> &listaInfo);
    void recorridoInOrden(Nodo<T> *nodo);
    Nodo<T> *agregarInOrden(ListaEncadenada<T> &listaInfo);
    void recorridoPorNiveles(Nodo<T> *nodo);
    bool esHoja(Nodo<T> *nodo);
    Nodo<T> *predecesor(Nodo<T> *nodo);
    Nodo<T> *sucesor(Nodo<T> *nodo);
    Nodo<T> *padre(T info);
    void visitaNodo(Nodo<T> *nodo);
    Nodo<T> *getRaiz();
    void clasificar();

    private:
    Nodo<T> *raiz;
};

template <class T>
Arbol<T>::Arbol() {
    raiz = nullptr;
}

template <class T>
Arbol<T>::Arbol(Nodo<T> *raiz) {
    this->raiz = raiz;
}

template <typename T>
bool Arbol<T>::agregarNodo(T info){
    Nodo<T>* nuevoNodo;
    bool bandera;
    Nodo<T>* auxiliar;
    Nodo<T>* hijo;
    nuevoNodo = new Nodo<T>(info);

    if(nuevoNodo == nullptr){
        bandera = false;
    }else{
        bandera = true;
    }

    if(bandera){
        if(raiz == nullptr){
            raiz = nuevoNodo;
        }else{
            auxiliar = raiz;
            while(!esHoja(auxiliar)){
                if(nuevoNodo->setInfo() < auxiliar->setInfo()){
                    hijo = auxiliar->getIzquierda();
                    if(hijo == nullptr){
                        auxiliar->setIzquierda(nuevoNodo);
                    }
                }else if(nuevoNodo->setInfo() > auxiliar->setInfo()){
                    hijo = auxiliar->getDerecha();
                    if(hijo == nullptr){
                        auxiliar->setDerecha(nuevoNodo);
                    }
                }else{
                    return false;
                }
                auxiliar = hijo;
            }
            if(auxiliar != nullptr){
                if(nuevoNodo->setInfo() < auxiliar->setInfo())
                    auxiliar->setIzquierda(nuevoNodo);
                else if(nuevoNodo->setInfo() > auxiliar->setInfo())
                    auxiliar->setDerecha(nuevoNodo);
                else
                    return false;
            }
        }
    }
    return bandera;
}

template <typename T>
bool Arbol<T>::borrarNodo(T info){
    Nodo<T>* auxiliar;
    bool bandera;
    Nodo<T>* padre;
    Nodo<T>* hijoIzquierdo;
    Nodo<T>* hijoDerecho;
    Nodo<T>* predecesor;
    T infoPredecesor;
    int cantidadHijos;
    
    auxiliar = raiz;

    if(auxiliar == nullptr){
        bandera = false;
    }else{
        while(auxiliar != nullptr && auxiliar->getInfo() != info){
            if(info < auxiliar->getInfo())
                auxiliar = auxiliar->getIzquierda();
            else 
                auxiliar = auxiliar->getDerecha();
        }
        if(auxiliar == nullptr){
            bandera = false;
        }else{
            hijoIzquierdo = auxiliar->getIzquierda();
            hijoDerecho = auxiliar->getDerecha();
            cantidadHijos = auxiliar->cantidadHijos();
            
            if(cantidadHijos == 0){
                padre = this->padre(info);
                if(padre == nullptr){
                    delete raiz;
                    raiz = nullptr;
                }
                else{
                    if(auxiliar->getInfo() < padre->getInfo())
                        padre->setIzquierda(nullptr);
                    else
                        padre->setDerecha(nullptr);
                    delete auxiliar;
                }
            }
            else if(cantidadHijos == 1){
                padre = this->padre(info);
                if(padre == nullptr){
                    delete raiz;
                    if(hijoIzquierdo == nullptr)
                        raiz = hijoDerecho;
                    else
                        raiz = hijoIzquierdo;
                }else{
                    if(info < padre->getInfo()){
                        if(hijoIzquierdo == nullptr)
                            padre->setIzquierda(hijoDerecho);
                        else
                            padre->setIzquierda(hijoIzquierdo);
                    }
                    else
                    {
                        if(hijoIzquierdo == nullptr)
                            padre->setDerecha(hijoDerecho);
                        else
                            padre->setDerecha(hijoIzquierdo);
                    }
                    delete auxiliar;
                }
            }else if(cantidadHijos == 2){
                predecesor = this->predecesor(auxiliar);
                infoPredecesor = predecesor->getInfo();
                borrarNodo(infoPredecesor);
                auxiliar->setInfo(infoPredecesor);
            }
        }
    }
    return bandera;
}

template <typename T>
void Arbol<T>::recorridoPostOrden(Nodo<T> *nodo) {
    if(nodo == nullptr) {
        return;
    }
    
    recorridoPostOrden(nodo->getIzquierda());  // Recorre el subárbol izquierdo
    recorridoPostOrden(nodo->getDerecha());    // Recorre el subárbol derecho
    visitaNodo(nodo);  // Imprime el nodo actual
}

template <class T>
Nodo<T> *Arbol<T>::agregarPostOrden(ListaEncadenada<T> &listaInfo) {
    //Agregar la informacion siguiendo el recorrido postorden
    //Como la raiz es el ultimo elemento, se debe sacar primero

    if (listaInfo.estaVacia()) {
        return nullptr;
    }

    T info = listaInfo.traerDatosFinal();
    listaInfo.borrarElementoFinal();

    if (info == "Nulo") {
        return nullptr; // Nodo nulo
    }

    Nodo<T> *nuevoNodo = new Nodo<T>(info);

    nuevoNodo->setDerecha(agregarPostOrden(listaInfo)); // Recursión para el hijo derecho
    nuevoNodo->setIzquierda(agregarPostOrden(listaInfo)); // Recursión para el hijo izquierdo
}

template<typename T>
void Arbol<T>::recorridoPreOrden(Nodo<T> *nodo) {
    if(nodo == nullptr) {
        return;
    }
    
    visitaNodo(nodo);  // Imprime el nodo actual
    recorridoPreOrden(nodo->getIzquierda());  // Recorre el subárbol izquierdo
    recorridoPreOrden(nodo->getDerecha());    // Recorre el subárbol derecho
}

template <class T>
Nodo<T> *Arbol<T>::agregarPreOrden(ListaEncadenada<T> &listaInfo) {
    if (listaInfo.estaVacia()) {
        return nullptr;
    }

    T info = listaInfo.traerDatosInicio();
    listaInfo.borrarElementoInicio();

    if (info == "Nulo") {
        return nullptr; // Nodo nulo
    }

    Nodo<T> *nuevoNodo = new Nodo<T>(info);

    nuevoNodo->setIzquierda(agregarPreOrden(listaInfo)); // Recursión para el hijo izquierdo
    nuevoNodo->setDerecha(agregarPreOrden(listaInfo)); // Recursión para el hijo derecho

    return nuevoNodo;
}

template<typename T>
void Arbol<T>::recorridoInOrden(Nodo<T> *nodo) {
    if(nodo == nullptr) {
        return;
    }
    
    recorridoInOrden(nodo->getIzquierda());  // Recorre el subárbol izquierdo
    visitaNodo(nodo);  // Imprime el nodo actual
    recorridoInOrden(nodo->getDerecha());    // Recorre el subárbol derecho
}

template <class T>
Nodo<T> *Arbol<T>::agregarInOrden(ListaEncadenada<T> &listaInfo) {
    //Agregar la informacion siguiendo el recorrido inorden
    //Como la raiz es el elemento del medio, se debe sacar primero y se debe obtener el tamaño de la lista y verificar que sea impar
    //Siempre se debera tomar el arbol como si estuviese correctamente balanceado

    if (listaInfo.estaVacia()) {
        return nullptr;
    }

    int tamano = listaInfo.tamanio();
    if (tamano % 2 == 0) {
        cout << "El arbol no esta balanceado" << endl;
        return nullptr; // El árbol no está balanceado
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
Nodo<T> *Arbol<T>::getRaiz(){
    return raiz;
}

template <class T>
void Arbol<T>::clasificar(){
    Nodo<T> *nodo = raiz;
    bool clasificado = false;

    while (nodo && !clasificado) {
        cout << nodo->getInfo() << "? (S/N): ";
        char respuesta;
        cin >> respuesta;

        if (respuesta == 'N' || respuesta == 'n') {
            nodo = nodo->getDerecha();
        } else if (respuesta == 'S' || respuesta == 's') {
            nodo = nodo->getIzquierda();
        } else {
            cout << "Respuesta no válida. Introduce S para Sí o N para No." << endl;
        }

        if (esHoja(nodo)) {
            cout << "Clasificacion: " << nodo->getInfo() << endl;
            clasificado = true;
        }
    }
}