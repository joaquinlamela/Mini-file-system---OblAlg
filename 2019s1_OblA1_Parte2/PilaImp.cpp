#include "PilaImp.h"

#ifndef PILAIMP_CPP
#define PILAIMP_CPP

template <class T>
inline ostream &operator<<(ostream& out, const PilaImp<T> &c) {
	c.Imprimir(out);
	return out;
}

template<class T>
PilaImp<T>::PilaImp(int llena)
{
	this->llena= llena;
	this->principio = new ListaPosImp<T>();
}

template<class T>
PilaImp<T>::PilaImp(const Pila<T>& p)
{
	this->llena = 0; 
	this->largo = 0; 
	this->principio = new ListaPosImp<T>(); 

	*this = p; 
}

template<class T>
PilaImp<T>::PilaImp(const PilaImp<T>& p)
{

	this->llena = 0;
	this->largo = 0;
	this->principio = new ListaPosImp<T>();

	*this = p;
}



template<class T>
PilaImp<T>::~PilaImp() {
	this->llena = 0;
	this->principio->Vaciar();
}

template<class T>
void PilaImp<T>::Push(const T& e) {
	if (this->EsLlena())
	{
		this->principio->BorrarFin();
		this->principio->AgregarPpio(e);
	}
	else {
		this->principio->AgregarPpio(e);
		this->largo++;
	}
}

template<class T>
T& PilaImp<T>::Top() const {
	return this->principio->ElementoPpio();
}

template<class T>
T PilaImp<T>::Pop() {
	T dato = this->Top();
	this->principio-> BorrarPpio(); 
	this->largo--;
	return dato;
}

template<class T>
void PilaImp<T>::Vaciar() {
	this->largo = 0;
	this->principio->Vaciar();
}

template<class T>
unsigned int PilaImp<T>::CantidadElementos() const {
	return this->largo;
}

template<class T>
bool PilaImp<T>::EsVacia() const {
	return this->largo==0;
}

template <class T>
bool PilaImp<T>::EsLlena() const{
	return this->largo==this->llena;
}

template<class T>
Pila<T>* PilaImp<T>::CrearVacia(int llena)
{
	this->llena = llena;
	this->largo = 0;
	this->principio = new ListaPosImp<T>();
	return this; 
}

#endif