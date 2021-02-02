#ifndef PRUEBASPROPIAS_H
#define PRUEBASPROPIAS_H

#include "Prueba.h"
#include "ConductorPrueba.h"
#include "InterfazDelSistemaImp.h"
#include "ListaPosImp.h"
#include "Asociacion.h"
#include "Archivo.h"

class PruebasPropias : public Prueba
{

public:
	PruebasPropias(ConductorPrueba* conductor);
	virtual ~PruebasPropias();


protected:
	virtual const char* getNombre() const;

private:

	void FormarRedBasica(InterfazDelSistema* interfaz);
	void correrPruebaConcreta();
	void FormarRedPrueba(Archivo* a);
	void FormarRedPrueba2(Directorio* d);
};

#endif