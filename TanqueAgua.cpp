#include "TanqueAgua.h"
#include <iostream>

using namespace std;

namespace UndavTanqueAgua
{
	struct TanqueAgua 
	{
		int id;
		int capacidad;
		int caudal;
	};

	TanqueAgua* Crear(int capacidad, int caudal, int id)
	{
		TanqueAgua* nuevoTanque = new TanqueAgua;
		if (capacidad > 0) {
			//nuevoTanque->id = asignarIdTanque();
			nuevoTanque->id = id;
			nuevoTanque->capacidad = capacidad;
			nuevoTanque->caudal = caudal < 0 ? 0: caudal > capacidad ? capacidad: caudal;
		}
		return nuevoTanque;
	}

	void Cargar(TanqueAgua* tanqueAgua, int caudal) 
	{
		int capacidadRestante = tanqueAgua->capacidad - tanqueAgua->caudal;
		if (capacidadRestante > caudal)
		{
			tanqueAgua->caudal += caudal;
		}
	}

	void Vaciar(TanqueAgua* tanqueAgua,	int caudal) 
	{
		if (tanqueAgua->caudal >= caudal)
		{
			tanqueAgua->caudal -= caudal;
		}
		else
			tanqueAgua->caudal = 0;
	}

	int ObtenerId(TanqueAgua* tanqueAgua)
	{
		return tanqueAgua->id;
	}

	int ObtenerCaudal(const TanqueAgua* tanqueAgua)
	{
		return tanqueAgua->caudal;
	}

	int ObtenerCapacidad(const TanqueAgua* tanqueAgua) 
	{
		return tanqueAgua->capacidad;
	}

	bool EstaVacio(const TanqueAgua* tanqueAgua) 
	{
		return tanqueAgua->caudal == 0;
	}

	bool EstaLleno(const TanqueAgua* tanqueAgua) 
	{
		return tanqueAgua->caudal == tanqueAgua->capacidad;
	}

	void Destruir(TanqueAgua* tanqueAgua) 
	{
		delete tanqueAgua;
	}
}
