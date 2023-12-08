#ifndef UNDAVGENERADORRED_H
#define UNDAVGENERADORRED_H

#include "RedPlataformasTanqueAgua.h"

using UndavRedPlataformasTanqueAgua::Red;
using UndavTanqueAgua::TanqueAgua;

namespace UndavGeneradorRed {
	int GenerarNumeroAleatorio(int min, int max);
	int GenerarIndiceAleatorio(UndavRedPlataformasTanqueAgua::Red* red, int cantidadVertices);
	bool ExisteLaConexion(UndavRedPlataformasTanqueAgua::Red* red, int indiceNodoOrigen, int indiceNodoDestino);
	int GenerarNodoDestino(UndavRedPlataformasTanqueAgua::Red* red, int cantidadVertices, int indiceNodoOrigen);
	void ConectarVertices(Red* red, int cantidadConexiones);
	TanqueAgua** CrearTanques(int cantidad);

	void Mezclar(TanqueAgua** items, int cantidadTanques);
	void Swap(int* a, int* b);
	void Intercambiar(int& a, int& b);

	int* CrearVectorRandom(int cantidadRandom);
	// Precondicion: ninguna
	// Postcondicion: Genera una red donde:
	//  1 - La cardinalidad del conjunto de vertices es igual @cantidadPlataformas
	//  2 - Las plataformas tienen una cantidad de tanques igual a
	//  @cantidadTanquesPorPlataforma, esos tanques estan distribuidos de mnaera
	//  random en las plataformas 3 - Se agregan conexiones igual a
	//  @cantidadConexiones de manera random
	Red* GenerarRed(int cantidadPlataformas, int cantidadTanquesPorPlataforma, int cantidadConexiones);
} // namespace UndavGeneradorRed

#endif