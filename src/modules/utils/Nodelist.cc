/*
 * Nodelist.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: root
 */

#include "Nodelist.h"

// Constructor por defecto
template<typename T>

Nodelist<T>::Nodelist() {
    // TODO Auto-generated constructor stub
    data=NULL;
    next=NULL;
         }
// Constructor por parámetro
template<typename T>
Nodelist<T>::Nodelist(T data_)
{
    data = data_;
    next = NULL;
}

// Eliminar todos los Nodos
template<typename T>
void Nodelist<T>::delete_all()
{
    if (next)
        next->delete_all();
    delete this;
}

// Imprimir un Nodo
template<typename T>
void Nodelist<T>::print()
{
    //cout << "Node-> " << "Dato: " << dato << " Direcion: " << this << " Siguiente: " << next << endl;
    cout << data << "-> ";
}

template<typename T>
Nodelist<T>::~Nodelist() {}


