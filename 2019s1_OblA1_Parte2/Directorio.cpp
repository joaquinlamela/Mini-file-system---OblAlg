#include "Directorio.h"
//Joaquin Lamela (233375) y Martin Gutman(186783)
#ifndef DIRECTORIO_CPP
#define DIRECTORIO_CPP

void Directorio::Imprimir(ostream & o) const
{
	o << *this->listaDirectorio;
}

Directorio::Directorio()
{
	this->nombre = Cadena();
	this->listaArchivos = new ListaOrdImp<Archivo>();
	this->listaDirectorio = new ListaOrdImp<Directorio>();
}

Directorio::Directorio(Cadena nombreDirectorio)
{
	this->nombre = Cadena(nombreDirectorio);
	this->listaArchivos = new ListaOrdImp<Archivo>();
	this->listaDirectorio = new ListaOrdImp<Directorio>();
}

Directorio::~Directorio()
{
	
	delete this->listaArchivos;
	delete this->listaDirectorio;
	
		
		/*
	if (this->listaArchivos != NULL && this->listaDirectorio != NULL) {
		delete this->listaArchivos; 
		delete this->listaDirectorio;
	}*/
}

Directorio::Directorio(const Directorio &d)
{
	this->nombre = d.GetNombre();
	this->listaArchivos = d.listaArchivos->Clon();
	this->listaDirectorio = d.listaDirectorio->Clon();

	//*this = d; 
}

bool Directorio::operator<(const Directorio &d) const
{
	return this->nombre < d.GetNombre();
}

bool Directorio::operator<=(const Directorio & a) const
{
	return this->nombre <= a.GetNombre();
}

bool Directorio::operator==(const Directorio &d) const
{
	return this->nombre == d.GetNombre();
}

Directorio &Directorio::operator=(const Directorio&d)
{
	if (this != &d)
	{
		this->nombre = Cadena(d.GetNombre());
		this->listaArchivos = d.listaArchivos->Clon();
		this->listaDirectorio = d.listaDirectorio->Clon();
	}
	return *this;
}

void Directorio::AgregarArchivo(Cadena nombreArchivo)
{
	Archivo a1 = Archivo(nombreArchivo);
	this->listaArchivos->AgregarOrd(a1);
}

void Directorio::AgregarArchivo(Archivo &archivo)
{
	this->listaArchivos->AgregarOrd(archivo);
}

void Directorio::EliminarArchivo(Cadena nombreArchivo)
{
	Archivo *a1 = new Archivo(nombreArchivo);
	this->listaArchivos->Borrar(*a1);
	delete a1; 
}

void Directorio::EliminarArchivos()
{
	this->listaArchivos->Vaciar();
}

bool Directorio::ExisteArchivo(Cadena nombreArchivo) const
{
	Archivo  a1 = Archivo(nombreArchivo);
	return this->listaArchivos->Existe(a1);
}

bool Directorio::ContieneArchivos() const
{
	return !this->listaArchivos->EsVacia();
}

// DESCOMENTAR FUNCION EN .cpp y .h LUEGO DE IMPLEMENTAR
Archivo *Directorio::BuscarArchivo(Cadena nombreArchivo) 
{
	Archivo * aRetornar = new Archivo(nombreArchivo);
	return &this->listaArchivos->RecuperarInseguro(*aRetornar);
	delete aRetornar; 
}


Archivo &Directorio::BuscarArchivoParaCambiarAttrib(Cadena nombreArchivo) const
{
	Archivo aRetornar = Archivo(nombreArchivo); 
	return this->listaArchivos->RecuperarInseguro(aRetornar); 
}



Cadena Directorio::GetNombre() const
{
	return this->nombre;
}

void Directorio::SetNombre(Cadena nombre)
{
	this->nombre = nombre;
}

void Directorio::ListarArchivos(Cadena ruta, Cadena parametro)
{

	Directorio * d1 = new Directorio(*this->buscarRuta(ruta));

	for (int i = 0; i < d1->listaArchivos->CantidadElementos(); i++) {
		if (parametro == "") {
			if (!this->listaArchivos->ElementoPos(i).EstaOculto()) {
				if (ruta == "/")
				{
					cout << ruta  << this->listaArchivos->ElementoPos(i).GetNombre() << endl;
				}
				else {
					cout << ruta << "/" << this->listaArchivos->ElementoPos(i).GetNombre() << endl;
				}
			}
		}
		else {
			if (parametro == "-H") {
				if (this->listaArchivos->ElementoPos(i).EstaOculto()) {
					if (ruta == "/")
					{
						cout << ruta << this->listaArchivos->ElementoPos(i).GetNombre() <<  " (H)" << endl;
					}
					else {
						cout << ruta << "/" << this->listaArchivos->ElementoPos(i).GetNombre() << " (H)" << endl;
					}
				}
				else {
					if (ruta == "/")
					{
						cout << ruta  << this->listaArchivos->ElementoPos(i).GetNombre() << endl;
					}
					else {
						cout << ruta << "/" << this->listaArchivos->ElementoPos(i).GetNombre() << endl;
					}
				}

			}
		}
	}
	delete d1; 
}


void Directorio::AgregarDirectorio(Cadena nombre)
{
	Directorio * agregar = new Directorio(nombre);
	this->listaDirectorio->AgregarOrd(*agregar);
	delete agregar; 
}

void Directorio::AgregarDirectorioAux(Cadena ruta)
{
	ListaPos<Cadena> *lista = ruta.split("/");
	 Directorio *actual = this;
	while (!lista->EsVacia() && lista->ElementoPpio() == actual->GetNombre())
	{
		lista->BorrarPpio();
		if (!lista->EsVacia())
		{
			if (actual->ExisteDirectorio(lista->ElementoPpio())) {
				actual = &actual->listaDirectorio->RecuperarInseguro(lista->ElementoPpio());
			}
			else {
				Directorio *agregar = new Directorio(lista->ElementoPpio());
				actual->listaDirectorio->AgregarOrd(*agregar);
				actual = &actual->listaDirectorio->RecuperarInseguro(lista->ElementoPpio());
				delete agregar; 
			}
		}
	}
}


void Directorio::EliminarDirectorio(Cadena ruta)
{
	Directorio *aBorrar = new Directorio(nombreDirectorio(ruta));
	Directorio d1 = *this->buscarRuta(rutaDirectorio(ruta));
	d1.listaDirectorio->Borrar(*aBorrar);
	*this->buscarRuta(rutaDirectorio(ruta)) = d1;
	delete aBorrar;

}

bool Directorio::ExisteDirectorio(Cadena ruta)
{
	ListaPos<Cadena> *lista = ruta.split("/");
	Directorio *d = this;
	if (ruta.Length() == 1||lista->CantidadElementos()==0) {
		return true; 
	}
	else {
		while (!lista->EsVacia())
		{
			if (d->listaDirectorio->Existe(lista->ElementoPpio()))
			{
				d = &d->listaDirectorio->RecuperarInseguro(lista->ElementoPpio());
				lista->BorrarPpio();
				if (lista->EsVacia())
					return true;
			}
			else return false;
		}
	}


}

Directorio & Directorio::BuscarDirectorio(Cadena ruta) 
{
	return this->listaDirectorio->RecuperarInseguro(*this->buscarRuta(ruta));
}


void Directorio::ListarDirectorio(Cadena ruta, Cadena parametro)
{
	Directorio * d1 = new Directorio(*this->buscarRuta(ruta));

	cout << ruta << endl;

	for (int i = 0; i < d1->listaDirectorio->CantidadElementos(); i++) {
		Directorio * d1 = &this->listaDirectorio->ElementoPos(i);
	}

	delete d1; 
}

void Directorio::DirAux(Cadena ruta, Cadena parametro, Cadena impresion) {
	//Cadena aux = this->GetNombre();
	Cadena impresionAux = impresion;
	for (int i = 0; i < this->listaDirectorio->CantidadElementos(); i++) {
		Directorio  directorioPosicionado = *new Directorio(this->listaDirectorio->ElementoPos(i)); //constructor copia agregado de forma preventiva.
		if (impresion == "/")
		{
			impresion = impresion + directorioPosicionado.GetNombre();
		}
		else {
			impresion = impresion + "/" + directorioPosicionado.GetNombre();
		}
			cout << impresion << endl;
		directorioPosicionado.ListarArchivos(impresion , parametro);
		if (!directorioPosicionado.listaDirectorio->EsVacia())
		{
			directorioPosicionado.DirAux(ruta + "/" + directorioPosicionado.GetNombre(), parametro, impresion);
		}
		impresion = impresionAux;
	}
}

void Directorio::Dir(Cadena ruta, Cadena parametro)
{
	Directorio* d1 = new Directorio(*this->buscarRuta(ruta));
	cout << ruta << endl;
	d1->ListarArchivos(ruta, parametro);
	if (d1->listaArchivos->EsVacia() && d1->listaDirectorio->EsVacia())
	{
		cout << "No contiene archivos ni directorios " << endl;
	}
	else {
		d1->DirAux(ruta, parametro, ruta);
	}
	delete d1; 
}

void Directorio::Vaciar()
{
	this->listaArchivos->Vaciar();
	this->listaDirectorio->Vaciar();
}

void Directorio::CopiarDirectorio(Cadena rutaOrigen, Cadena rutaDestino)
{
	bool esSubruta = this->verificarCadena(rutaOrigen, rutaDestino);

	if (!esSubruta)
	{
		Directorio dCopia = Directorio();

		dCopia.nombre = this->buscarRuta(rutaOrigen)->nombre;
		dCopia.listaArchivos = this->buscarRuta(rutaOrigen)->listaArchivos->Clon();
		dCopia.listaDirectorio = this->buscarRuta(rutaOrigen)->listaDirectorio->Clon();

		this->crearDirectorio(rutaDestino);
		while (!dCopia.listaDirectorio->EsVacia())
		{
			this->buscarRuta(rutaDestino)->listaDirectorio->AgregarOrd(dCopia.listaDirectorio->Minimo());
			dCopia.listaDirectorio->BorrarMinimo();
		}
		while (!dCopia.listaArchivos->EsVacia())
		{
			this->buscarRuta(rutaDestino)->listaArchivos->AgregarOrd(dCopia.listaArchivos->Minimo());
			dCopia.listaArchivos->BorrarMinimo();
		}
	}
}

void Directorio::AgregarDirectorioDirecto(Cadena ruta, Directorio directorio) {
	ListaPos<Cadena> *lista = ruta.split("/");
	Directorio *actual = this;
	while (!lista->EsVacia() && lista->ElementoPpio() == actual->GetNombre())
	{
		lista->BorrarPpio();

		if (!lista->EsVacia())
		{
			actual = &actual->listaDirectorio->RecuperarInseguro(lista->ElementoPpio());
		}
	}
	actual->listaDirectorio->AgregarOrd(directorio);
}

//FUNCIONES AGREGADAS: 

Directorio Directorio::crearDirectorio(Cadena ruta)
{
	ListaPos<Cadena> *lista = ruta.split("/");
	lista->AgregarPpio(""); //Se agregar un espacio vacio debido a que el nombre de FileSystem es siempre una barra.

	Directorio *actual = this;
	while (!lista->EsVacia() && lista->ElementoPpio() == actual->GetNombre())
	{
		lista->BorrarPpio();
		if (!lista->EsVacia())
		{
			if (actual->ExisteDirectorio(lista->ElementoPpio())) {
				actual = &actual->listaDirectorio->RecuperarInseguro(lista->ElementoPpio());
			}
			else {
				Directorio *agregar = new Directorio(lista->ElementoPpio());
				actual->listaDirectorio->AgregarOrd(*agregar);
				actual = &actual->listaDirectorio->RecuperarInseguro(lista->ElementoPpio());
				delete agregar; 
			}
		}
	}

	return *actual;
}

Directorio* Directorio::buscarRuta(Cadena ruta)
{
	Directorio *d = this;
	ListaPos<Cadena> *lista = ruta.split("/");
	lista->AgregarPpio("");
	if (lista->CantidadElementos() != 0)
	{
		if (Cadena(lista->ElementoPpio()) == d->GetNombre())
		{
			lista->BorrarPpio();
			int i = 0;
			while (!lista->EsVacia())
			{
				if (d->listaDirectorio->ElementoPos(i).GetNombre() == lista->ElementoPpio())
				{

					d = &d->listaDirectorio->ElementoPos(i);
					lista->BorrarPpio();
					i = 0;
				}
				else {
					i++;
				}
			}
		}
	}
	return d;
}


Cadena Directorio::nombreArchivo(Cadena ruta)
{
	ListaPos<Cadena> *listaConRuta = ruta.split("/");

	while (listaConRuta->CantidadElementos() != 1) {
		listaConRuta->BorrarPpio();
	}
	return listaConRuta->ElementoPpio();
}

Cadena Directorio::nombreDirectorio(Cadena ruta)
{
	ListaPos<Cadena> *listaConRuta = ruta.split("/");

	while (listaConRuta->CantidadElementos() != 1) {
		listaConRuta->BorrarPpio();
	}
	return listaConRuta->ElementoPpio();
}

Cadena Directorio::rutaDirectorio(Cadena ruta)
{
	ListaPos<Cadena> *listaConRuta = ruta.split("/");
	Cadena c = "";

	listaConRuta->BorrarFin();

	if (listaConRuta->CantidadElementos()==0)
	{
		c = "/";
	}
	else {
		int final = listaConRuta->CantidadElementos();
		for (int i = 0; i < final; i++)
		{
			c = c + "/";
			c = c + listaConRuta->ElementoPpio();
			listaConRuta->BorrarPpio();
		}
	}
	return c;
}

bool Directorio::verificarSiExiste(Cadena ruta) {
	ListaPos<Cadena> *listaConRuta = ruta.split("/");
	if (listaConRuta->CantidadElementos() == 1) {
		Directorio *d1 = new Directorio(listaConRuta->ElementoPpio());
		return this->listaDirectorio->Existe(*d1); 
		delete d1; 
	}
}



bool Directorio::existePadre(Cadena ruta) {

	ListaPos<Cadena> *listaConRuta = ruta.split("/");

	listaConRuta->BorrarFin();
	Cadena c = "";

	if (listaConRuta->CantidadElementos() == 0)
	{
		c = "/";
	}
	else {
		int final = listaConRuta->CantidadElementos();
		for (int i = 0; i < final; i++)
		{
			c = c + "/";
			c = c + listaConRuta->ElementoPpio();
			listaConRuta->BorrarPpio();
		}
	}
	return this->ExisteDirectorio(c);
}

Cadena Directorio::DirectorioDeUnArchivo(Cadena ruta)
{
	ListaPos<Cadena> *listaConRuta = ruta.split("/");

	while (listaConRuta->CantidadElementos() != 2) {
		listaConRuta->BorrarPpio();
	}
	return listaConRuta->ElementoPpio();
}



int Directorio::cantidadElementosCadena(Cadena ruta) {
	ListaPos<Cadena> *listaConRuta = ruta.split("/");
	return listaConRuta->CantidadElementos(); 
}


bool Directorio::verificarCadena(Cadena c1, Cadena c2)
{
	ListaPos<Cadena> *l1 = c1.split("/");
	ListaPos<Cadena> *l2 = c2.split("/");

	bool sonIguales = true;
	if (!l2->CantidadElementos() == 0)
	{
		while (!l1->EsVacia() && !l2->EsVacia())
		{
			if (l1->ElementoPpio() == l2->ElementoPpio())
			{
				l1->BorrarPpio();
				l2->BorrarPpio();
			}
			else {
				sonIguales = false;
				l1->BorrarPpio();
				l2->BorrarPpio();
			}
		}
	}
	return sonIguales;
}
#endif