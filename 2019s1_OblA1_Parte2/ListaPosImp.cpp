#include "ListaPosImp.h"

#ifndef LISTAPOSIMP_CPP
#define LISTAPOSIMP_CPP

template <class T>
inline ostream & operator<<(ostream &out, const ListaPosImp<T> &l)
{
	l.Imprimir(out);
	return out;
}

template <class T>
ListaPos<T>* ListaPosImp<T>::CrearVacia() const
{
	return new ListaPosImp<T>();
}

template <class T>
ListaPosImp<T>::ListaPosImp()
{
	this->principio = NULL;
	this->largo = 0;
	this->fin = NULL;
}

template <class T>
ListaPosImp<T>::ListaPosImp(const ListaPos<T> &l)
{
	this->principio = NULL;
	this->fin = NULL;
	this->largo = 0;

	*this = l;
}

template <class T>
ListaPosImp<T>::ListaPosImp(const ListaPosImp<T> &l)
{
	this->principio = NULL;
	this->fin = NULL;
	this->largo = 0;

	*this = l;
}

template <class T>
ListaPos<T>& ListaPosImp<T>::operator=(const ListaPos<T> &l)
{

	if (this != &l) {
		this->Vaciar();
		for (int i = 0; i < l.CantidadElementos(); i++) {
			AgregarFin(l.ElementoPos(i));
		}
	}
	return *this;
}

template <class T>
ListaPos<T>& ListaPosImp<T>::operator=(const ListaPosImp<T> &l)
{
	if (this != &l) {
		this->Vaciar();
		for (int i = 0; i < l.CantidadElementos(); i++) {
			AgregarFin(l.ElementoPos(i));
		}
	}
	return *this;
}

template <class T>
ListaPosImp<T>::~ListaPosImp()
{
	this->Vaciar();
}

template <class T>
void ListaPosImp<T>::AgregarPpio(const T &e)
{
	if (EsVacia()) {
		this->principio = new NodoLista<T>();
		this->principio->dato = e;
		this->principio->sig = NULL;
		this->principio->ant = NULL;
		this->fin = this->principio;
	}
	else {
		NodoLista<T> * aux = new NodoLista<T>();
		aux->dato = e;
		aux->sig = this->principio;
		aux->ant = NULL;
		this->principio = aux;
	}
	this->largo = this->largo + 1;


}

template <class T>
void ListaPosImp<T>::AgregarFin(const T &e)
{
	if (EsVacia()) {
		NodoLista<T> * retorno = new NodoLista<T>();
		retorno->dato = e;
		retorno->sig = NULL;
		retorno->ant = NULL;
		this->fin = retorno;
		this->principio = this->fin;
	}
	else {
		NodoLista<T> * aux = new NodoLista<T>();
		aux->dato = e;
		aux->sig = NULL;
		aux->ant = NULL;
		this->fin->sig = aux;
		this->fin = this->fin->sig;
	}

	this->largo = this->largo + 1;
}

template <class T>
void ListaPosImp<T>::AgregarPos(const T &e, unsigned int pos)
{
	if (pos >= this->largo)
	{
		AgregarFin(e);
	}
	else {

		if (pos == 0)
		{
			this->AgregarPpio(e);
		}
		else {

			NodoLista<T> *iter = new NodoLista<T>();
			iter = this->principio;
			iter->ant = NULL;

			while (pos > 1)
			{
				iter = iter->sig;
				pos--;
			}

			NodoLista<T> *agregar = new NodoLista<T>();
			agregar->dato = e;
			agregar->ant = NULL;
			agregar->sig = iter->sig;
			iter->sig = agregar;
		}

	}
	this->largo = this->largo + 1;
}

template <class T>
void ListaPosImp<T>::BorrarPpio()
{
	if (!EsVacia()) {
		NodoLista<T> * borrar = new NodoLista<T>();
		borrar = this->principio;
		this->principio = this->principio->sig;
		if (this->principio != NULL)
		{
			this->principio->ant = NULL;
		}
		delete borrar;
		this->largo--;
	}
}

template <class T>
void ListaPosImp<T>::BorrarFin()
{

	if (!EsVacia()) {
		if (this->principio == this->fin) {
			this->Vaciar();
		}
		else {

			NodoLista<T>* iter = new NodoLista<T>();
			iter = this->principio;
			iter->ant = NULL;
			while (iter->sig->sig != NULL) {
				iter = iter->sig;
			}
			NodoLista<T> * borrar = new NodoLista<T>();
			borrar = iter->sig;
			iter->sig = NULL;
			this->fin = iter;
			delete borrar;
			this->largo--;
		}

	}
}

template <class T>
void ListaPosImp<T>::BorrarPos(unsigned int pos)
{
	if (pos < this->largo) {

		if (pos == 0) {
			this->BorrarPpio();
		}
		else {

			NodoLista<T> *iter = new NodoLista<T>();
			iter = this->principio;
			iter->ant = NULL;

			while (pos != 1)
			{
				iter = iter->sig;
				pos--;
			}

			NodoLista<T> *aBorrar = new NodoLista<T>();
			aBorrar = iter->sig;
			iter->sig = aBorrar->sig;
			delete aBorrar;
		}
		this->largo--;
	}
}

template <class T>
void ListaPosImp<T>::Borrar(const T &e)
{
	if (!EsVacia()) {
		if (this->principio->dato == e) {
			this->BorrarPpio();
		}
		else {

			NodoLista<T> * iter = new NodoLista<T>();
			iter = this->principio;
			iter->ant = NULL;
			while (iter->sig != NULL && iter->sig->dato != e) {
				iter = iter->sig;
			}
			if (iter->sig != NULL)
			{
				NodoLista<T> * aBorrar = new NodoLista<T>();
				aBorrar = iter->sig;
				iter->sig = aBorrar->sig;
				delete aBorrar;
			}
		}
		this->largo--;
	}
}

template <class T>
T& ListaPosImp<T>::ElementoPpio() const
{
	return this->principio->dato;
}

template <class T>
T& ListaPosImp<T>::ElementoFin() const
{
	return this->fin->dato;
}

template <class T>
T& ListaPosImp<T>::ElementoPos(unsigned int pos) const
{
	NodoLista<T> *iter = new NodoLista<T>();
	iter = this->principio;
	iter->ant = NULL;


	while (pos > 0)
	{
		iter = iter->sig;
		pos--;
	}

	return iter->dato;
}

template <class T>
unsigned int ListaPosImp<T>::Posicion(const T &e) const
{
	NodoLista<T> * iter = new NodoLista<T>();
	iter = this->principio;
	iter->ant = NULL;
	int contador = 0;
	while (iter != NULL && iter->dato != e) {
		iter = iter->sig;
		contador++;
	}
	return contador;
}

template <class T>
bool ListaPosImp<T>::Existe(const T &e) const
{
	NodoLista<T> * iter = new NodoLista<T>();
	iter = this->principio;
	iter->ant = NULL;
	bool existe = false;
	while (iter != NULL && iter->dato != e) {
		iter = iter->sig;
	}
	if (iter != NULL)
	{
		existe = true;
	}
	return existe;
}

template <class T>
void ListaPosImp<T>::Vaciar()
{
	NodoLista<T> *aux = this->principio;
	while (aux != NULL) {
		NodoLista<T> *borrar = aux;
		aux = aux->sig;
		delete borrar;
	}

	this->fin = NULL;
	this->principio = NULL;
	this->largo = 0;
}

template <class T>
unsigned int ListaPosImp<T>::CantidadElementos() const
{
	if (this != NULL) {
		return this->largo;
	}
	else {
		return 0; 
	}
}

template <class T>
bool ListaPosImp<T>::EsVacia() const
{
	return this->largo == 0;
}

template <class T>
bool ListaPosImp<T>::EsLlena() const
{
	return false;
}

template <class T>
ListaPos<T>* ListaPosImp<T>::Clon() const
{

	ListaPos<T>* clon = new ListaPosImp<T>();

	for (int i = 0; i < this->CantidadElementos(); i++)
	{
		clon->AgregarFin(ElementoPos(i));
	}
	return clon;
}

template <class T>
Iterador<T> ListaPosImp<T>::GetIterador() const
{
	return IteradorListaPosImp<T>(*this);
}

template <class T>
void ListaPosImp<T>::Imprimir(ostream& o) const
{

	//Ya no pasa las pruebas de TAD debido a que lo modifique para archivos
	
	
	for (int i = 0; i < this->CantidadElementos(); i++)
	{
		o << i << ElementoPos(i) << endl;
	}
	
	
	//Esto es si fuera para el TAD
	/*for (int i = 0; i < this->CantidadElementos(); i++) {
		if (i != this->CantidadElementos() - 1)
		{
			o << ElementoPos(i) << " ";
		}
		else {
			o << ElementoPos(i) << "";
		}
	}*/

}

#endif