# include <iostream>
# include "nodoLista.h"

using namespace std;

// DefiniciÃ³n de la clase Lista Encadenada
template <typename T>
class ListaEncadenada 
{
public:
    ListaEncadenada();            // constructor
    ~ListaEncadenada();           // destructor
    bool estaVacia();
    bool insertarElementoInicio(T info);
    bool insertarElementoFinal(T info);
    int tamanio();
    int encontrarPosicionElemento(T info);
    void borrarElementoInicio();
    void borrarElementoFinal();
    bool borrarElemento(int posicion);
    void desplegar();
    T traerDatosInicio();
    T traerDatosFinal();
    T traerDato(int indice);
    bool buscarElemento(T info);

private:       
    NodoLista<T> *inicio, *final;        // ptr a objeto inicial de la lista
};

template <typename T>
ListaEncadenada<T>::ListaEncadenada()
{
    inicio = nullptr;
    final = nullptr;
}

template <typename T>
ListaEncadenada<T>::~ListaEncadenada()
{
    NodoLista<T>* auxiliar;

    while (inicio != nullptr)
    {
        auxiliar = inicio;
        inicio = inicio->siguiente;
        delete auxiliar;
    }
}

template <typename T>
bool ListaEncadenada<T>::estaVacia()
{
    return (inicio == nullptr);
}

template <typename T>
bool ListaEncadenada<T>::insertarElementoInicio(T info)
{
    NodoLista<T>* nuevo;
    bool bandera;

    nuevo = new NodoLista<T>(info);
    bandera = (nuevo != nullptr);

    if (bandera)
    {
        if (inicio == nullptr)
        {
            inicio = nuevo;
            final = nuevo;
        }
        else
        {
            nuevo -> siguiente = inicio;
            inicio = nuevo;
        }
    }

    return bandera;
}

template <typename T>
bool ListaEncadenada<T>::insertarElementoFinal(T info)
{
    NodoLista<T>* nuevo;
    bool bandera;

    nuevo = new NodoLista<T>(info);
    bandera = (nuevo != nullptr);

    if (bandera)
    {
        if (inicio == nullptr){
            inicio = nuevo;
            final = nuevo;
        }
        else{
            final -> siguiente = nuevo;
            final = nuevo;
        }
    }

    return bandera;
}

template <typename T>
void ListaEncadenada<T>::desplegar()
{
    NodoLista<T>* auxiliar = inicio;
    int indice = 0;

    if (inicio != nullptr)
        do
        {
            indice = indice + 1;
            cout << indice << ". " << auxiliar->informacion <<endl;
            auxiliar = auxiliar ->siguiente;
        }while(auxiliar != nullptr);
    else
        cout << "No hay"<<endl;
    
}

template <typename T>
int ListaEncadenada<T>::tamanio()
{
    NodoLista<T>* auxiliar = inicio;
    int indice = 0;

    if (inicio != nullptr)
        do
        {   
            indice = indice + 1;
            auxiliar = auxiliar ->siguiente;
        }while(auxiliar != nullptr);
    
    return indice;
    
}

template <typename T>
void ListaEncadenada<T>::borrarElementoFinal()
{
    NodoLista<T>* auxiliar = inicio;

    if (inicio != nullptr)
    {
        if (inicio->siguiente == nullptr)
        {  
            delete inicio;
            inicio = nullptr;
        }
        else
        {   while((auxiliar->siguiente)->siguiente != nullptr)
                auxiliar = auxiliar->siguiente;
            delete auxiliar->siguiente;
            final = auxiliar;
            auxiliar -> siguiente = nullptr;
        }
    }
}

template <typename T>    
int ListaEncadenada<T>::encontrarPosicionElemento(T info)
{
    NodoLista<T>* auxiliar = inicio;
    int indice = 1;

 
    while ( (auxiliar != nullptr) and (auxiliar->informacion != info))
    {   
        indice = indice + 1;
        auxiliar = auxiliar ->siguiente;
    };

    if (auxiliar == nullptr)
        indice = 0;

    return indice;
 
}

template <typename T>  
void ListaEncadenada<T>::borrarElementoInicio()
{
  NodoLista<T>* auxiliar;

  if (inicio != nullptr)
  {
    auxiliar = inicio -> siguiente;
    delete inicio;
    inicio = auxiliar;
  }
}

template <typename T>     
T ListaEncadenada<T>::traerDatosInicio()
{
    if(inicio != nullptr)
        return (inicio->informacion);
    else
        return (T) NULL;
}

template <typename T>
T ListaEncadenada<T>::traerDatosFinal()
{
    if(final != nullptr)
        return (final->informacion);
    else
        return (T) NULL;
}

template <typename T>
bool ListaEncadenada<T>::buscarElemento(T info)
{
    NodoLista<T>* auxiliar = inicio;
    bool bandera = false;

    while ( (auxiliar != nullptr) and (auxiliar->informacion != info))
        auxiliar = auxiliar ->siguiente;

    if (auxiliar != nullptr)
        bandera = true;

    return bandera;
}

template <typename T>
T ListaEncadenada<T>::traerDato(int indice)
{
    NodoLista<T>* auxiliar = inicio;
    int indiceAuxiliar = 1;

    while ( (auxiliar != nullptr) and (indiceAuxiliar != indice))
    {   
        indiceAuxiliar = indiceAuxiliar + 1;
        auxiliar = auxiliar ->siguiente;
    };

    if (auxiliar == nullptr)
        return (T) NULL;
    else
        return (auxiliar->informacion);
}

template <typename T>
bool ListaEncadenada<T>::borrarElemento(int posicion)
{
    NodoLista<T>* auxiliar = inicio;
    NodoLista<T>* auxiliar2;
    bool bandera = false;
    int indice = 1;

    if (inicio != nullptr)
    {
        if (posicion == 1)
        {
            borrarElementoInicio();
            bandera = true;
        }
        else
        {
            while ( (auxiliar != nullptr) and (indice < posicion-1))
            {   
                indice = indice + 1;
                auxiliar = auxiliar ->siguiente;
            };

            if (auxiliar != nullptr)
            {
                auxiliar2 = auxiliar->siguiente;
                auxiliar->siguiente = auxiliar2->siguiente;
                delete auxiliar2;
                bandera = true;
            }
        }
    }

    return bandera;
}