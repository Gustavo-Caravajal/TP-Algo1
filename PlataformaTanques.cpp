#include "PlataformaTanques.h"
#include "DiccionarioTanqueAgua.h"
#include "TanqueAgua.h"
#include <iostream>

/*using namespace UndavTanqueAgua;
using namespace UndavDiccionarioTanqueAgua;
using namespace UndavPlataformaTanques;
*/
using namespace std;

namespace UndavPlataformaTanques
{

	struct PlataformaTanques
	{
		int id = 0;
		UndavDiccionarioTanqueAgua::DiccionarioTanqueAgua* items;
	};

	int idPlataforma = 0;
	int obtenerIdPlataforma() { return idPlataforma++; }

	PlataformaTanques* CrearPlataformaVacia()
	{
		PlataformaTanques* nuevaPlataforma = new PlataformaTanques;
		nuevaPlataforma->id = obtenerIdPlataforma();
		nuevaPlataforma->items = UndavDiccionarioTanqueAgua::Crear();
		return nuevaPlataforma;
	}

	PlataformaTanques* Crear(UndavTanqueAgua::TanqueAgua** tanques, int cantidadTanques)
	{
		PlataformaTanques* nuevaPlataforma = CrearPlataformaVacia();
		TanqueAgua* tanqueActual;

		for (int i = 0; i < cantidadTanques; ++i) 
		{
			tanqueActual = tanques[i];
			int idTanque = UndavTanqueAgua::ObtenerId(tanqueActual);
			UndavDiccionarioTanqueAgua::Agregar(nuevaPlataforma->items, idTanque,
				tanqueActual);
		}
		return nuevaPlataforma;
	}

	UndavDiccionarioTanqueAgua::DiccionarioTanqueAgua* ObtenerDiccionario(PlataformaTanques* plataforma)
	{
		return plataforma->items;
	}

	bool ContieneTanque(PlataformaTanques* plataforma, int idTanque)
	{
		return UndavDiccionarioTanqueAgua::Existe(plataforma->items, idTanque);
	}

	int ObtenerId(PlataformaTanques* plataforma)
	{
		return plataforma->id;
	}

	void Destruir(PlataformaTanques* plataforma)
	{
		UndavDiccionarioTanqueAgua::Destruir(plataforma->items);
		delete plataforma;
	}
}