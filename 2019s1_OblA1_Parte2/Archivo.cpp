#include "Archivo.h"


#ifndef ARCHIVO_CPP
#define ARCHIVO_CPP

//Joaquin Lamela (233375) y Martin Gutman(186783)

Archivo::Archivo(Cadena nombre)
{
	this->nombre = Cadena(nombre);
	this->oculto = false;
	this->matrizTexto = new ListaPosImp<Cadena>();
}

Archivo::Archivo()
{
	this->nombre = Cadena();
	this->oculto = false;
	this->matrizTexto = new ListaPosImp<Cadena>();
}

Archivo::~Archivo()
{
	delete this->matrizTexto;
	
//	this->matrizTexto->Vaciar(); 
//	delete this->matrizTexto;
}

Archivo::Archivo(const Archivo &a)
{
	this->nombre = Cadena(a.nombre);
	this->oculto = a.oculto;
	this->matrizTexto = a.matrizTexto->Clon();
	//*this = a;
}

void Archivo::copia(const Archivo & a)
{
	this->nombre = Cadena();
	this->oculto = false;
	this->matrizTexto = NULL;
	
	*this = a;
}

Archivo &Archivo::operator=(const Archivo &a)
{
	if (this != &a)
	{
		this->nombre = Cadena(a.GetNombre());
		this->oculto = a.oculto;
		this->matrizTexto = a.matrizTexto->Clon();
	}
	return *this;
}

bool Archivo::operator==(const Archivo &a) const
{
	return this->nombre == a.GetNombre();
}

bool Archivo::operator<(const Archivo & a) const
{
	return this->nombre < a.GetNombre();
}

bool Archivo::operator<=(const Archivo & a) const
{
	return this->nombre <= a.GetNombre();
}

void Archivo::setMatriztexto(ListaPos<Cadena>* matriz)
{
	this->matrizTexto = matriz;
}



void Archivo::ModificarVisibilidad(Cadena nuevaVisibilidad)
{
	Cadena oculto = Cadena("+H", true);
	Cadena visible = Cadena("-H", false);

	if (nuevaVisibilidad == oculto) {
		this->oculto = true;
	}
	if (nuevaVisibilidad == visible) {
		this->oculto = false;
	}
}

void Archivo::setVisibilidad(bool visibilidad) {
	this->oculto = visibilidad; 
}

void Archivo::agregarLineasVacias() {
	
	Cadena c = " "; 
	this->matrizTexto->AgregarFin(c);
}


void Archivo::InsertarTexto(unsigned int nroLinea, unsigned int posLinea, Cadena texto)
{
	posLinea--;
	int contador = 0;
	contador = this->matrizTexto->CantidadElementos();
	while (contador < nroLinea) {
		agregarLineasVacias();
		contador++;
	}

	if (posLinea > this->matrizTexto->ElementoPos(nroLinea - 1).Length()) {
		for (int i = this->matrizTexto->ElementoPos(nroLinea - 1).Length(); i < posLinea; i++)
		{
			Cadena * c = new Cadena(" "); 
			this->matrizTexto->ElementoPos(nroLinea - 1) = this->matrizTexto->ElementoPos(nroLinea - 1) + *c;
			delete c; 
		}
		this->matrizTexto->ElementoPos(nroLinea - 1) = this->matrizTexto->ElementoPos(nroLinea - 1) + texto; 
	}
	else {
			
	Cadena linea = this->matrizTexto->ElementoPos(nroLinea-1); 
	Cadena izq = ""; 
	Cadena der = ""; 
	
	for (int i = 0; i < linea.Length(); i++)
	{
		char c = linea[i];
		char * pc = new char[2];
		pc[0] = c;
		pc[1] = '\0';
		Cadena caden = Cadena(pc);
		if (i < posLinea) {
			izq = Cadena(izq + caden);
		}
		else {
			der = Cadena(der + caden);
		}
	}
	this->matrizTexto->ElementoPos(nroLinea-1) = izq + texto + der;

	}

}


bool Archivo::TieneLineas() const
{
	return this->matrizTexto->CantidadElementos() != 0;
}

bool Archivo::EliminarTexto(unsigned int nroLinea, unsigned int posLinea, unsigned int k)
{
	
	int contador = 0;
	contador = this->matrizTexto->CantidadElementos();
	while (contador < nroLinea) {
		return false; 
	}
	Cadena linea = this->matrizTexto->ElementoPos(nroLinea - 1);
	Cadena izq = "";
	Cadena der = "";

	for (int i = 0; i < linea.Length(); i++)
	{
		char c = linea[i];
		char * pc = new char[2];
		pc[0] = c;
		pc[1] = '\0';
		Cadena caden = Cadena(pc);
		if (i < posLinea) {
			izq = Cadena(izq + caden);
		}
		if (i >= posLinea + k) {
			der = Cadena(der + caden);
		}
	}

	this->matrizTexto->ElementoPos(nroLinea - 1) = izq + der;
	if (this->matrizTexto->ElementoPos(nroLinea-1).Length()==0)
	{
		this->matrizTexto->BorrarPos(nroLinea-1);
	}
	return true;
}

void Archivo::MostrarContenido() const
{
	for (int i = 0; i < this->matrizTexto->CantidadElementos(); i++)
	{
		if (this->matrizTexto->ElementoPos(i) != "") {
			cout << i+1 << ":" <<" " << this->matrizTexto->ElementoPos(i) << endl;
		}
		else {
			cout << i+1 << endl;
		}
	}
}

bool Archivo::EstaOculto() const
{
	return this->oculto;
}

Cadena Archivo::GetNombre() const
{
	return this->nombre;
}

ListaPos<Cadena>* Archivo::GetMatrizTexto()
{
	return this->matrizTexto;
}

bool Archivo::GetVisibilidad()
{
	return this->oculto;
}

#endif