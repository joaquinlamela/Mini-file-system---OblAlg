#include "FileSystem.h"

//Joaquin Lamela (233375) y Martin Gutman(186783)
#ifndef FILESYSTEM_CPP
#define FILESYTEM_CPP



FileSystem::FileSystem()
{
	this->raiz = new Directorio();
	this->maximoARecuperar = 8;
	this->archivoARecuperar = new PilaImp<Asociacion<Cadena, Archivo>>(maximoARecuperar);
}


FileSystem::FileSystem(unsigned int MAX_RECUPERAR)
{
	this->raiz = new Directorio();
	this->maximoARecuperar = MAX_RECUPERAR;
	this->archivoARecuperar = new PilaImp<Asociacion<Cadena, Archivo>>(maximoARecuperar);
}


FileSystem::~FileSystem()
{
	//	this->raiz->~Directorio();
	delete this->raiz;
	delete this->archivoARecuperar;
}

FileSystem::FileSystem(const FileSystem &f)
{
	this->raiz = new Directorio();
	this->maximoARecuperar = 0;
	this->archivoARecuperar = new PilaImp<Asociacion<Cadena, Archivo>>(maximoARecuperar);

	*this = f;
}

FileSystem &FileSystem::operator=(const FileSystem &f)
{
	if (this != &f)
	{
		this->raiz = f.raiz;
		this->maximoARecuperar = f.maximoARecuperar;
		this->archivoARecuperar = f.archivoARecuperar;
	}
	return *this;
}


TipoRetorno FileSystem::Mkdir(Cadena rutaDirectorio)
{
	if (rutaDirectorio[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaDirectorio))) {
		cout << "ERROR: No se encuentra la ruta" << endl;
		return ERROR;
	}
	if (!this->raiz->verificarCadena(this->raiz->GetNombre(), rutaDirectorio)) {
		cout << "ERROR: Ya existe un subdirectorio con el mismo nombre en esa ruta" << endl;
		return ERROR;
	}
	if (this->raiz->verificarSiExiste(rutaDirectorio)) {
		cout << "ERROR: Ya existe un subdirectorio con el mismo nombre en esa ruta" << endl;
		return ERROR;
	}

	if (rutaDirectorio == "/") {
		cout << "ERROR: No se puede volver a crear el directorio raiz" << endl;
		return ERROR;
	}

	this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaDirectorio))->AgregarDirectorio(this->raiz->nombreDirectorio(rutaDirectorio));
	return OK;
}
TipoRetorno FileSystem::Rmdir(Cadena rutaDirectorio)
{
	if (rutaDirectorio[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(rutaDirectorio)) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			if (this->raiz->GetNombre() == this->raiz->nombreDirectorio(rutaDirectorio)) {
				this->raiz->Vaciar();
			}
			else {
				this->raiz->EliminarDirectorio(rutaDirectorio);
			}
			return OK;
		}
	}
}


TipoRetorno FileSystem::CopyDir(Cadena rutaOrigen, Cadena rutaDestino)
{
	//FALTA VERIFICAR QUE NO SE ENCUENTRA EL PADRE DE LA RUTA DESTINO

	if (rutaOrigen[0] != '/' || rutaDestino[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(rutaOrigen)) {
			cout << "ERROR: No se encuentra la ruta origen" << endl;
			return ERROR;
		}
		else {
			if (this->raiz->ExisteDirectorio(rutaDestino)) { //PREGUNTAR
				cout << "ERROR: Ya existe la ruta destino" << endl;
				return ERROR;
			}
			/*if (!this->raiz->ExisteDirectorio(rutaDestino)) {
				cout << "ERROR: No se encuentra el padre de la ruta destino." << endl;
				return ERROR;
			}*/
			else {
				if (!this->raiz->existePadre(rutaDestino)) {
					cout << "ERROR: No se encuentra el padre de la ruta destino." << endl;
					return ERROR;
				}
				else {
					if (this->raiz->verificarCadena(rutaOrigen, rutaDestino)) {
						cout << "ERROR: La ruta destino no puede ser un subdirectorio de origen" << endl;
						return ERROR;
					}
					else {
						this->raiz->CopiarDirectorio(rutaOrigen, rutaDestino);
						return OK;
					}
				}
			}
		}
	}
}

TipoRetorno FileSystem::Dir(Cadena rutaDirectorio, Cadena parametro) const
{
	if (rutaDirectorio[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(rutaDirectorio)) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			if (parametro != "" && parametro != "-H") {
				cout << "ERROR: Parametro desconocido" << endl;
				return ERROR;
			}
			else {
				this->raiz->Dir(rutaDirectorio, parametro);
				return OK;
			}
		}
	}
}

TipoRetorno FileSystem::CreateFile(Cadena rutaArchivo)
{
	if (rutaArchivo[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaArchivo))) {
			cout << "ERROR: No se encuentra la ruta " << endl;
			return ERROR;
		}
		else {
			Directorio *d1 = new Directorio(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo)));

			if (d1->ExisteArchivo(this->raiz->nombreArchivo(rutaArchivo))) { // AQUI ES SI EXISTE UN ARCHIVO CON EL MISMO NOMBRE EN ESA RUTA
				cout << "ERROR: Ya existe un archivo con el mismo nombre en esa ruta" << endl;
				return ERROR;
			}
			else {
				Archivo* a = new Archivo(this->raiz->nombreArchivo(rutaArchivo));
				if (this->raiz->cantidadElementosCadena(rutaArchivo) == 1) {
					this->raiz->AgregarArchivo(*a);
				}
				else {
					this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->AgregarArchivo(*a);
				}
				// this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo));
				return OK;
			}
		}
	}
}


TipoRetorno FileSystem::Delete(Cadena rutaArchivo)
{

	if (rutaArchivo[0] != '/') {
		cout << "ERROR: La ruta no comienza con / " << endl;
		return ERROR;
	}
	else {

		if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaArchivo))) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			Directorio* d1 = new Directorio(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo)));
			if (!d1->ExisteArchivo(d1->nombreArchivo(rutaArchivo))) {
				cout << "ERROR: No existe un archivo con ese nombre en esa ruta" << endl;
				return ERROR;
			}
			else {
				Archivo *a = new Archivo(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->BuscarArchivo(this->raiz->nombreArchivo(rutaArchivo)));
				Asociacion<Cadena, Archivo>* agregarUndelete = new Asociacion<Cadena, Archivo>(rutaArchivo, *a);
				this->archivoARecuperar->Push(*agregarUndelete);
				this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->EliminarArchivo(this->raiz->nombreArchivo(rutaArchivo));
				return OK;
			}
		}
	}

}

TipoRetorno FileSystem::Attrib(Cadena rutaArchivo, Cadena parametro)
{
	if (rutaArchivo[0] != '/') {
		cout << "ERROR: La ruta no comienza con / " << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaArchivo))) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			Directorio* d1 = new Directorio(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo)));
			if (!d1->ExisteArchivo(d1->nombreArchivo(rutaArchivo))) {
				cout << "ERROR: No existe un archivo con ese nombre en esa ruta" << endl;
				return ERROR;
			}
			else {
				if (parametro != "+H" && parametro != "-H") {
					cout << "ERROR: Parametro desconocido" << endl;
					return ERROR;
				}
				else {
					if (parametro == "+H") {
						this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->BuscarArchivoParaCambiarAttrib(this->raiz->nombreArchivo(rutaArchivo)).setVisibilidad(true);
					}
					else {
						this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->BuscarArchivoParaCambiarAttrib(this->raiz->nombreArchivo(rutaArchivo)).setVisibilidad(false);
					}
					return OK;
				}
			}
		}
	}

}

TipoRetorno FileSystem::InsertText(Cadena rutaArchivo, unsigned int nroLinea, unsigned int posLinea, Cadena texto)
{

	//LLAMAR CON POSLINEA - 1 

	if (rutaArchivo[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaArchivo))) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			Directorio* d1 = new Directorio(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo)));
			if (!d1->ExisteArchivo(d1->nombreArchivo(rutaArchivo))) {
				cout << "ERROR: No existe un archivo con ese nombre en esa ruta" << endl;
				return ERROR;
			}
			else {
				if (nroLinea == 0) {
					cout << "ERROR: La linea cero no es valida" << endl;
					return ERROR;
				}
				else {
					if (posLinea == 0) {
						cout << "ERROR: La posicion cero no es valida" << endl;
						return ERROR;
					}
					else {
						Archivo * a = this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->BuscarArchivo(d1->nombreArchivo(rutaArchivo));
						a->InsertarTexto(nroLinea, posLinea, texto);
						return OK;
					}
				}
			}
		}
	}
}

TipoRetorno FileSystem::DeleteText(Cadena rutaArchivo, unsigned int nroLinea, unsigned int posLinea, unsigned int k)
{

	if (rutaArchivo[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaArchivo))) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			Directorio* d1 = new Directorio(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo)));

			if (!d1->ExisteArchivo(d1->nombreArchivo(rutaArchivo))) {
				cout << "ERROR: No existe un archivo con ese nombre en esa ruta" << endl;
				return ERROR;
			}
			else {
				if (nroLinea == 0) {
					cout << "ERROR: La linea cero no es valida" << endl;
					return ERROR;
				}
				else {
					if (posLinea == 0) {
						cout << "ERROR: La posicion cero no es valida" << endl;
						return ERROR;
					}
					else {
						Archivo * a = this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->BuscarArchivo(d1->nombreArchivo(rutaArchivo));
						if (a->EliminarTexto(nroLinea, posLinea - 1, k)) {
							return OK;
						}
						else {
							cout << "ERROR: La linea no existe" << endl;
							return ERROR;
						}
					}
				}
			}
		}
	}
}

TipoRetorno FileSystem::Type(Cadena rutaArchivo) const
{
	if (rutaArchivo[0] != '/') {
		cout << "ERROR: La ruta no comienza con /" << endl;
		return ERROR;
	}
	else {
		if (!this->raiz->ExisteDirectorio(this->raiz->rutaDirectorio(rutaArchivo))) {
			cout << "ERROR: No se encuentra la ruta" << endl;
			return ERROR;
		}
		else {
			Directorio* d1 = new Directorio(*this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo)));
			if (!d1->ExisteArchivo(d1->nombreArchivo(rutaArchivo))) {
				cout << "ERROR: No existe un archivo con ese nombre en esa ruta" << endl;
				return ERROR;
			}
			else {
				Archivo * a = this->raiz->buscarRuta(this->raiz->rutaDirectorio(rutaArchivo))->BuscarArchivo(d1->nombreArchivo(rutaArchivo));
				if (d1->BuscarArchivo(d1->nombreArchivo(rutaArchivo))->EstaOculto()) {
					cout << rutaArchivo << endl;
					cout << endl;
					cout << "El archivo esta oculto" << endl;
				}
				else {
					if (a->TieneLineas()) {
						cout << rutaArchivo << endl;
						cout << endl;
						a->MostrarContenido();
					}
					else {
						cout << rutaArchivo << endl;
						cout << endl;
						cout << "El archivo no posee contenido" << endl;
					}

				}
			}
		}
	}
}
TipoRetorno FileSystem::Undelete()
{
	if (this->archivoARecuperar->EsVacia()) {
		cout << "ERROR: No hay archivos para recuperar" << endl;
		return ERROR;
	}
	else {
		Asociacion<Cadena, Archivo> a = this->archivoARecuperar->Pop();
		Cadena ruta = a.GetDominio();
		Archivo recuperado = a.GetRango();
		//this->raiz->buscarRuta(this->raiz->rutaDirectorio(ruta)).AgregarArchivo(a.GetRangoInseguro()); 
		this->CreateFile(ruta);
		for (int i = 0; i < recuperado.GetMatrizTexto()->CantidadElementos(); i++)
		{
			this->InsertText(ruta, i + 1, 1, recuperado.GetMatrizTexto()->ElementoPos(i));
		}
		this->raiz->buscarRuta(this->raiz->rutaDirectorio(ruta))->BuscarArchivoParaCambiarAttrib(this->raiz->nombreArchivo(ruta)).setVisibilidad(recuperado.GetVisibilidad());

		//this->raiz->buscarRuta(this->raiz->rutaDirectorio(ruta)).AgregarArchivo(recuperado); 
		return OK;
	}
}



#endif