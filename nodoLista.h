// Para que reconozca que la clase amiga usa template
template <typename T> class ListaEncadenada;

// Definicion de la clase NodoLista

template <typename T>
class NodoLista
{ 
    friend class ListaEncadenada<T>; // clase amiga para poder acceder directo a los atributos

public:
    NodoLista(T e);            // constructor

private:
    T informacion;        // datos almacenados en este NodoLista
    NodoLista<T>* siguiente;        // ptr a otro objeto del mismo tipo
};

template <class T>
NodoLista<T>::NodoLista(T e) 
{ 
    informacion=e; 
    siguiente = nullptr;
}