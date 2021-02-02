#ifndef DIRECTORIO_H
#define DIRECTORIO_H

#include "Cadena.h"
#include "ListaOrdImp.h"
#include "Asociacion.h"
#include "Referencia.h"
#include "Archivo.h"

//Joaquin Lamela (233375) y Martin Gutman(186783)
class Directorio;

inline ostream &operator<<(ostream& out, const Directorio &d) {
	assert(false);
	return out;
	/*d.Imprimir(out);
	return out;*/
}

class Directorio {

public:
	void Imprimir(ostream& o) const;
	//Constructor por defecto
	Directorio();

	//Constructor
	Directorio(Cadena nombreDirectorio);

	//Destructor
	virtual ~Directorio();

	//Constructor copia
	Directorio(const Directorio &d);

	//Operador de asignación
	Directorio &operator=(const Directorio &d);

	//Operador de menor
	bool operator<(const Directorio &d) const;

	//Operador de igualdad
	bool operator==(const Directorio &d) const;

	//PRE: El archivo no existe
	//POS: Agrega el archivo
	void AgregarArchivo(Cadena nombreArchivo);

	//PRE: El archivo no existe
	//POS: Agrega el archivo
	void AgregarArchivo(Archivo &archivo);

	//PRE: El archivo existe
	//POS: Elimina el archivo
	void EliminarArchivo(Cadena nombreArchivo);

	//PRE:
	//POS: Elimina todos los archivos
	void EliminarArchivos();

	//PRE:
	//POS: Retorna true si existe archivo con ese nombre
	bool ExisteArchivo(Cadena nombreArchivo) const;

	//PRE:
	//POS: True si existe al menos un archivo.
	bool ContieneArchivos() const;

	//PRE: Existe archivo
	//POS: Retorna Archivo
	Archivo *BuscarArchivo(Cadena nombreArchivo);

	Archivo & BuscarArchivoParaCambiarAttrib(Cadena nombreArchivo) const;

	//PRE:
	//POS: Retorna el nombre del directorio
	Cadena GetNombre() const;

	//PRE:
	//POS: Cambia el nombre del directorio
	void SetNombre(Cadena nombre);

	//PRE:
	//POS: Lista todos los archivos en orden alfabetico con prefijo ruta teniendo en cuenta el parametro que indica la visibilidad.
	void ListarArchivos(Cadena ruta, Cadena parametro);


	//Operador <= 

	bool operator<=(const Directorio &a) const;



	//Aqui vamos a poner los metodos de directorios para no utilizar dicha clase asi la complejidad se disminuye

	//PRE:  
	//POS: Agregar el directorio
	void AgregarDirectorio(Cadena nombre);

	void AgregarDirectorioAux(Cadena ruta);

	//PRE: 
	//POS: Elimina el directorio.
	void EliminarDirectorio(Cadena ruta);

	//PRE: 
	//POS: Retorna true si existe directorio correspondiente a ruta.
	bool ExisteDirectorio(Cadena ruta);

	//PRE: Existe ruta
	//POS: Retorna Directorio correspondiente a la ruta.
	Directorio &BuscarDirectorio(Cadena ruta);

	void DirAux(Cadena ruta, Cadena parametro, Cadena impresion);


	//PRE: Existe ruta
	//POS: Imprime la jerarquia de directorios a partir de ruta teniendo en cuenta el parametro que indica la visibilidad.
	void Dir(Cadena ruta, Cadena parametro);

	//PRE: 
	//POS: Elimina todos los directorios (y sus archivos) excepto el raiz "/".
	void Vaciar();

	//PRE: 
	//POS: Copia el directorio de origen a destino
	void CopiarDirectorio(Cadena rutaOrigen, Cadena rutaDestino);

	void AgregarDirectorioDirecto(Cadena ruta, Directorio directorio);


	//Metodos agregados por nosotros: 

	Directorio crearDirectorio(Cadena ruta);

	Directorio* buscarRuta(Cadena ruta);

	int cantidadElementosCadena(Cadena ruta);

	bool verificarCadena(Cadena c1, Cadena c2);

	Cadena nombreArchivo(Cadena ruta);
	Cadena nombreDirectorio(Cadena ruta);

	Cadena rutaDirectorio(Cadena ruta);

	bool verificarSiExiste(Cadena ruta);

	bool existePadre(Cadena ruta);

	Cadena DirectorioDeUnArchivo(Cadena ruta);


	void ListarDirectorio(Cadena ruta, Cadena parametro);

private:
	Cadena nombre;
	ListaOrd<Archivo> * listaArchivos;
	ListaOrd<Directorio> * listaDirectorio;

};

#endif 