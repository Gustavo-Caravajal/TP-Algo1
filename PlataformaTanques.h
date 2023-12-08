#ifndef UNDAVPLATAFORMATANQUES_H
#define UNDAVPLATAFORMATANQUES_H

#include "DiccionarioTanqueAgua.h"
#include "TanqueAgua.h"

using UndavDiccionarioTanqueAgua::DiccionarioTanqueAgua;
using UndavTanqueAgua::TanqueAgua;

namespace UndavPlataformaTanques {
	struct PlataformaTanques;

	PlataformaTanques* CrearPlataformaVacia();
	PlataformaTanques* Crear(TanqueAgua** tanques, int cantidadTanques);

	int obtenerIdPlataforma();
	TanqueAgua* ObtenerTanque(PlataformaTanques* plataforma, int idTanque);
	bool ContieneTanque(PlataformaTanques* plataforma, int idTanque);
	int ObtenerId(PlataformaTanques* plataforma);
	DiccionarioTanqueAgua* ObtenerDiccionario(PlataformaTanques* plataforma);

	void Destruir(PlataformaTanques* plataforma);
}
#endif