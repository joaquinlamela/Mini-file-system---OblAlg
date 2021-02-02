#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "Cadena.h"
#include "ListaPosImp.h"
#include "Referencia.h"

//Joaquin Lamela (233375) y Martin Gutman(186783)
class Archivo;

inline ostream &operator<<(ostream& out, const Archivo &a) {
	assert(false); // No implementada
	return out;
}

class Archivo {

public:

	//Constructor por defecto
	Archivo();

	//Constructor
	Archivo(Cadena nombre);

	//Destructor
	virtual ~Archivo();

	//Constructor copia
	Archivo(const Archivo &a);

	void copia(const Archivo &a);

	//Operador de asignaci�n
	Archivo &operator=(const Archivo &a);

	//Operador igualdad
	bool operator==(const Archivo &a) const;

	//Operador < 
	bool operator<(const Archivo &a) const;

	//Operador <= 

	bool operator<=(const Archivo &a) const;

	void setMatriztexto(ListaPos<Cadena>* matriz);

	//PRE:
	//POS: Si los parametros son validos se agrega texto al archivo 
	void InsertarTexto(unsigned int nroLinea, unsigned int posLinea, Cadena texto);

	//PRE:
	//POS: Si los parametros son validos se elimina texto del archivo. Devuelve true cuando lo hizo efectivamente y false si tira error.
	bool EliminarTexto(unsigned int nroLinea, unsigned int posLinea, unsigned int k);

	//PRE:
	//POS: Se lista su contenido 
	void MostrarContenido() const;

	//PRE:
	//POS: Retorna true si esta oculto
	bool EstaOculto() const;

	//PRE:
	//POS: Retorna nombre
	Cadena GetNombre() const;

	ListaPos<Cadena>* GetMatrizTexto();

	bool GetVisibilidad();

	//PRE: Recibe nombre de archivo existente y nueva visibilidad
	//POS: Modifica visibilidad del archivo correspondiente al recibido
	void ModificarVisibilidad(Cadena nuevaVisibilidad);

	void setVisibilidad(bool visibilidad);

	//PRE:
	//POS: Retorna si el archivo tiene lineas
	bool TieneLineas() const;


	//Metodo agregado por nosotros: 

	//Pre:
	//Pos: Crea lineas vacias
	void agregarLineasVacias();




private:
	Cadena nombre;
	bool oculto;
	ListaPos <Cadena> * matrizTexto;

};

#endif 