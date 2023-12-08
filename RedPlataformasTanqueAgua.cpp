#include "TanqueAgua.h"
#include "Lista.h"
#include "PlataformaTanques.h"
#include "RedPlataformasTanqueAgua.h"
#include "Pila.h"
#include <iostream>

using namespace UndavPlataformaTanques;
using namespace UndavLista;
using namespace UndavTanqueAgua;
using namespace UndavRedPlataformasTanqueAgua;
using namespace UndavPila;
using namespace std;

namespace UndavRedPlataformasTanqueAgua
{
	struct ItemAdyacencia
	{
		int indiceVerticeAdyacente;
	};

	struct Vertice
	{
		UndavPlataformaTanques::PlataformaTanques* plataforma;
		UndavLista::Lista* adyacencias;
	};

	struct Red
	{
		TipoGrafo tipo;
		int cantidadVertices;
		Vertice* vertices;
	};

	Red* Crear(UndavPlataformaTanques::PlataformaTanques** nodos, int cantidadNodos)
	{
		Red* nuevaRed = NULL;
		if (cantidadNodos >= 0)
		{
			nuevaRed = new Red;
			nuevaRed->cantidadVertices = cantidadNodos;
			nuevaRed->vertices = new Vertice[cantidadNodos];
			nuevaRed->tipo = NoDirigido;
			for (int i = 0; i < cantidadNodos; i++)
			{
				nuevaRed->vertices[i].plataforma = nodos[i];
				nuevaRed->vertices[i].adyacencias = UndavLista::CrearListaVacia();
			}
		}
		return nuevaRed;
	}

	int EncontrarVertice(Red* red, UndavPlataformaTanques::PlataformaTanques* nodoPlataforma)
	{
		int i = 0;
		while ((red->vertices[i].plataforma != nodoPlataforma) and (i < red->cantidadVertices)) i++;
		return i == red->cantidadVertices ? -1 : i;
	}

	UndavPlataformaTanques::PlataformaTanques* SeleccionarPlataforma(Red* red, int indice)
	{
		return red->vertices[indice].plataforma;
	}

	int ObtenerCantidadVertices(Red* red)
	{
		return red->cantidadVertices;
	}

	UndavLista::Lista* ObtenerListaAdyasencia(Red* red, int indice)
	{
		return red->vertices[indice].adyacencias;
	}

	void AgregarConexion(Red* red, int iNodoOrigen, int iNodoDestino)
	{
		int* copiaINodoDestino = new int(iNodoDestino);
		UndavLista::AgregarAlComienzo(red->vertices[iNodoOrigen].adyacencias, copiaINodoDestino);

		int* copiaINodoOrigen = new int(iNodoOrigen);
		UndavLista::AgregarAlComienzo(red->vertices[iNodoDestino].adyacencias, copiaINodoOrigen);
	}

	namespace UndavRecorridoProfundidad
	{
		struct RecorridoProfundidad
		{
			bool* fueVisitado;
		};

		void InicializarVisitados(bool* visitados, int cantidad)
		{
			for (int i = 0; i < cantidad; ++i)  visitados[i] = false;
		}

		RecorridoProfundidad* Crear(Red* red)
		{
			RecorridoProfundidad* dfs = new RecorridoProfundidad;
			int cantidadVertices = ObtenerCantidadVertices(red);
			dfs->fueVisitado = new bool[cantidadVertices];
			InicializarVisitados(dfs->fueVisitado, cantidadVertices);
			return dfs;
		}

		UndavTanqueAgua::TanqueAgua* ObtenerTanqueDFS(Red* red, int idTanque)
		{
			int verticeAVisitar = 0;
			RecorridoProfundidad* recorrido = Crear(red);
			UndavPila::Pila* pila = UndavPila::CrearPila();
			UndavPila::Apilar(pila, verticeAVisitar);
			recorrido->fueVisitado[verticeAVisitar] = true;
			UndavTanqueAgua::TanqueAgua* tanque = NULL;

			while ((!UndavPila::EstaVacia(pila)) and (tanque == NULL))
			{
				verticeAVisitar = UndavPila::Desapilar(pila);
				tanque = UndavDiccionarioTanqueAgua::Obtener(ObtenerDiccionario(red->vertices[verticeAVisitar].plataforma), idTanque);
				if (tanque == NULL)
				{
					UndavLista::IteradorLista::Iterador* iterador = UndavLista::IteradorLista::Comienzo(red->vertices[verticeAVisitar].adyacencias);

					while (!UndavLista::IteradorLista::EsFin(iterador))
					{
						int itemIterador = *(int*)UndavLista::IteradorLista::ObtenerItem(iterador);

						if (!recorrido->fueVisitado[itemIterador])
						{
							UndavPila::Apilar(pila, itemIterador);
							recorrido->fueVisitado[itemIterador] = true;
						}
						UndavLista::IteradorLista::Siguiente(iterador);
					}
					UndavLista::IteradorLista::Destruir(iterador);
				}
			}

			UndavPila::DestruirPila(pila);

			if (tanque == NULL)
			{
				int cantidadVertices = ObtenerCantidadVertices(red);
				for (int i = 0; ((i < cantidadVertices) and (tanque == NULL)); i++)
				{
					if (!recorrido->fueVisitado[i])
					{
						tanque = UndavDiccionarioTanqueAgua::Obtener(ObtenerDiccionario(red->vertices[i].plataforma), idTanque);
					}
				}
			}

			return tanque;
		}

		bool EsAlcanzable(RecorridoProfundidad* recorrido, int destino)
		{
			return recorrido->fueVisitado[destino];
		}

		void DestruirRecorrido(RecorridoProfundidad* recorrido)
		{
			delete[] recorrido->fueVisitado;
			delete recorrido;
		}
	}

	void Destruir(Red* red)
	{
		for (int i = 0; i < red->cantidadVertices; ++i)
		{
			UndavPlataformaTanques::Destruir(red->vertices[i].plataforma);
			UndavLista::Destruir(red->vertices[i].adyacencias);
		}
		delete[] red->vertices;
		delete red;
	}
}