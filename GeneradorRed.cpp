#include "GeneradorRed.h"
#include "PlataformaTanques.h"
#include "RedPlataformasTanqueAgua.h"
#include "TanqueAgua.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

namespace UndavGeneradorRed {

	int GenerarNumeroAleatorio(int min, int max) 
	{
		random_device rd;
		mt19937 generador(rd());
		uniform_int_distribution<int> distribucion(min, max);

		return distribucion(generador);
	}

	int GenerarIndiceAleatorio(UndavRedPlataformasTanqueAgua::Red* red, int cantidadVertices)
	{
		int limiteAristasPorVertice = cantidadVertices - 1;

		int indiceNodo = GenerarNumeroAleatorio(0, (cantidadVertices - 1));
		int cantidadConexionesNodo = UndavLista::CantidadItems(
			UndavRedPlataformasTanqueAgua::ObtenerListaAdyasencia(red, indiceNodo));

		while (cantidadConexionesNodo >= limiteAristasPorVertice)
		{
			indiceNodo = GenerarNumeroAleatorio(0, (cantidadVertices - 1));
			cantidadConexionesNodo = UndavLista::CantidadItems(UndavRedPlataformasTanqueAgua::ObtenerListaAdyasencia(red, indiceNodo));
		}

		return indiceNodo;
	}

	bool ExisteLaConexion(UndavRedPlataformasTanqueAgua::Red* red, int indiceNodoOrigen, int indiceNodoDestino) 
	{
		bool laConexionExiste = false;
		if (indiceNodoOrigen == indiceNodoDestino) laConexionExiste = true;

		UndavLista::Lista* listaAdy = ObtenerListaAdyasencia(red, indiceNodoOrigen);
		UndavLista::IteradorLista::Iterador* iterador = UndavLista::IteradorLista::Comienzo(listaAdy);

		while ((!UndavLista::IteradorLista::EsFin(iterador)) and (!laConexionExiste)) 
		{
			void* Item = UndavLista::IteradorLista::ObtenerItem(iterador);
			int valorAdyacente = *static_cast<int*>(Item);
			if (valorAdyacente == indiceNodoDestino) laConexionExiste = true; 
			UndavLista::IteradorLista::Siguiente(iterador);
		}
		UndavLista::IteradorLista::Destruir(iterador);

		return laConexionExiste;
	}

	int NodoDestinoForzoso(UndavRedPlataformasTanqueAgua::Red* red, int indiceNodoOrigen, int cantidadVertices) 
	{
		int indiceNodoDestino = GenerarIndiceAleatorio(red, cantidadVertices);
		bool laConexionExiste = ExisteLaConexion(red, indiceNodoOrigen, indiceNodoDestino);

		while (laConexionExiste and indiceNodoDestino < cantidadVertices) 
		{
			indiceNodoDestino = (indiceNodoDestino + 1) % cantidadVertices;
			laConexionExiste = ExisteLaConexion(red, indiceNodoOrigen, indiceNodoDestino);
		}
		return indiceNodoDestino;
	}

	int GenerarNodoDestino(UndavRedPlataformasTanqueAgua::Red* red, int cantidadVertices, int indiceNodoOrigen) 
	{
		int indiceNodoDestino = GenerarIndiceAleatorio(red, cantidadVertices);
		bool EstaConectado = ExisteLaConexion(red, indiceNodoOrigen, indiceNodoDestino);

		if (EstaConectado) 
		{
			for (int i = 0; ((i < cantidadVertices + 10) and (EstaConectado)); i++)
			{
				indiceNodoDestino = GenerarIndiceAleatorio(red, cantidadVertices);
				EstaConectado = ExisteLaConexion(red, indiceNodoOrigen, indiceNodoDestino);
			}			
		}

		if (EstaConectado) indiceNodoDestino = NodoDestinoForzoso(red, indiceNodoOrigen, cantidadVertices);

		return indiceNodoDestino;
	}

	void ConectarVertices(UndavRedPlataformasTanqueAgua::Red* red,int cantidadConexiones) 
	{
		int cantidadVertices = UndavRedPlataformasTanqueAgua::ObtenerCantidadVertices(red);
		int limiteAristas = (cantidadVertices * (cantidadVertices - 1)) / 2;
		limiteAristas = limiteAristas < cantidadConexiones ? limiteAristas : cantidadConexiones;

		for (int i = 0; i < limiteAristas; i++)
		{
			int indiceNodoOrigen = GenerarIndiceAleatorio(red, cantidadVertices);
			int indiceNodoDestino =	GenerarNodoDestino(red, cantidadVertices, indiceNodoOrigen);
			UndavRedPlataformasTanqueAgua::AgregarConexion(red, indiceNodoOrigen,indiceNodoDestino);
		}
	}

	UndavTanqueAgua::TanqueAgua** CrearTanques(int cantidad) 
	{
		const int multiplicador = 10;
		const int caudal = 0;

		UndavTanqueAgua::TanqueAgua** tanques = new UndavTanqueAgua::TanqueAgua * [cantidad];

		for (int i = 0; i < cantidad; ++i) 
		{
			int capacidad = multiplicador * GenerarNumeroAleatorio(4, 15);
			tanques[i] = UndavTanqueAgua::Crear(capacidad, caudal, i);
		}
		return tanques;
	}

	void Mezclar(UndavTanqueAgua::TanqueAgua** items, int cantidadTanques) 
	{
		int* vectorDeIndicesRandom = CrearVectorRandom(cantidadTanques);

		for (int i = 0; i < cantidadTanques; ++i) 
		{
			int indiceAleatorio = vectorDeIndicesRandom[i];
			UndavTanqueAgua::TanqueAgua* tanqueAux = items[i];
			items[i] = items[indiceAleatorio];
			items[indiceAleatorio] = tanqueAux;
		}
		delete[] vectorDeIndicesRandom;
	}

	int* CrearVectorRandom(int cantidadRandom)
	{		
		int* vectorDeNumerosRandom = new int[cantidadRandom];

		for (int i = 0; i < cantidadRandom; ++i)
		{
			vectorDeNumerosRandom[i] = i;
		}

		for (int i = cantidadRandom - 1; i > 0; --i)
		{
			int j = GenerarNumeroAleatorio(0, i);

			int temp = vectorDeNumerosRandom[i];
			vectorDeNumerosRandom[i] = vectorDeNumerosRandom[j];
			vectorDeNumerosRandom[j] = temp;
		}
		return vectorDeNumerosRandom;
	}

	UndavRedPlataformasTanqueAgua::Red* GenerarRed(int cantidadPlataformas, int cantidadTanquesPorPlataforma, int cantidadConexiones) 
	{
		int cantidadTanques = cantidadPlataformas * cantidadTanquesPorPlataforma;
		UndavTanqueAgua::TanqueAgua** tanques = CrearTanques(cantidadTanques);

		Mezclar(tanques, cantidadTanques);

		UndavPlataformaTanques::PlataformaTanques** plataformas = new UndavPlataformaTanques::PlataformaTanques * [cantidadPlataformas];
		int indicePrimerTanque = 0;
		UndavTanqueAgua::TanqueAgua** tanquesSeleccionados = new UndavTanqueAgua::TanqueAgua * [cantidadTanquesPorPlataforma];
		 
		for (int i = 0; i < cantidadPlataformas; i++) 
		{
			int indiceUltimoTanque = indicePrimerTanque + cantidadTanquesPorPlataforma;
			int j = indicePrimerTanque, z = 0;

			while (j < indiceUltimoTanque) 
			{
				tanquesSeleccionados[z] = tanques[j];
				j++, z++;
			}

			plataformas[i] = UndavPlataformaTanques::Crear(tanquesSeleccionados, cantidadTanquesPorPlataforma);
			indicePrimerTanque = indiceUltimoTanque;
		}

		Red* nuevaRed = UndavRedPlataformasTanqueAgua::Crear(plataformas, cantidadPlataformas);

		ConectarVertices(nuevaRed, cantidadConexiones);

		return nuevaRed;
	};
}