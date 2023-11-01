#include <iostream>

using namespace std;

template <class T>
class Nodo{
    public:
    Nodo(T info);
    void setInfo(T info);
    void setIzquierda(Nodo<T> *izq);
    void setDerecha(Nodo<T> *der);
    T getInfo();
    Nodo<T> *getIzquierda();
    Nodo<T> *getDerecha();
    int cantidadHijos();

    private:
    T informacion;
    Nodo<T> *izquierda;
    Nodo<T> *derecha;
};

template <class T>
Nodo<T>::Nodo(T info){
    informacion = info;
    izquierda = nullptr;
    derecha = nullptr;
}

template <class T>
void Nodo<T>::setInfo(T info){
    informacion = info;
}

template <class T>
void Nodo<T>::setIzquierda(Nodo<T> *izq){
    izquierda = izq;
}

template <class T>
void Nodo<T>::setDerecha(Nodo<T> *der){
    derecha = der;
}

template <class T>
T Nodo<T>::getInfo(){
    return informacion;
}

template <class T>
Nodo<T> *Nodo<T>::getIzquierda(){
    return izquierda;
}

template <class T>
Nodo<T> *Nodo<T>::getDerecha(){
    return derecha;
}

template <class T>
int Nodo<T>::cantidadHijos(){
    int cant = 0;
    if (izquierda != nullptr)
        cant++;
    if (derecha != nullptr)
        cant++;
    return cant;
}
    
