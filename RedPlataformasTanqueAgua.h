#ifndef UNDAVREDPLATAFORMASTANQUEAGUA_H
#define UNDAVREDPLATAFORMASTANQUEAGUA_H

#include "Lista.h"
#include "PlataformaTanques.h"
#include "TanqueAgua.h"
#include <iostream>


using UndavLista::IteradorLista::Iterador;
using UndavPlataformaTanques::PlataformaTanques;
using UndavTanqueAgua::TanqueAgua;

namespace UndavRedPlataformasTanqueAgua {
	enum TipoGrafo { NoDirigido };
	struct ItemAdyacencia;
	struct Vertice;
	struct Red;

	// Precondicion: Los ids de los nodos van de [0:@cantidadNodos -1]
	// Postcondicion: Devuelve una instancia valida de Red que representa
	//  un grafo no dirigido desconectado donde los vertices son los @nodos

	Red* Crear(PlataformaTanques** nodos, int cantidadNodos);
	void AgregarConexion(Red* red, int iNodoOrigen, int iNodoDestino);
	int EncontrarVertice(Red* red, PlataformaTanques* nodoPlataforma);
	int ObtenerCantidadVertices(Red* red);
	PlataformaTanques* SeleccionarPlataforma(Red* red, int indice);
	UndavLista::Lista* ObtenerListaAdyasencia(Red* red, int indice); //nuevo

	namespace UndavRecorridoProfundidad {
		struct RecorridoProfundidad;

		typedef void (*TipoVisitar)(int vertice);
		void InicializarVisitados(bool* visitados, int cantidad);
		RecorridoProfundidad* Crear(Red* Red, int comienzo, int idTanque);


		TanqueAgua* ObtenerTanqueDFS(Red* red, int idTanque);


		bool EsAlcanzable(RecorridoProfundidad* recorrido, int destino);
		void DestruirRecorrido(RecorridoProfundidad* recorrido);
	}

	TanqueAgua* ObtenerTanqueAgua(Red* red, int idTanqueAgua);

	void Destruir(Red* red);
} 

#endif