#ifndef UNDAVTANQUEAGUA_H
#define UNDAVTANQUEAGUA_H

namespace UndavTanqueAgua {
	struct TanqueAgua;
	// Postcondicion: Devuelve una instancia valida de TanqueAgua si la capacidad es
	// mayor que cero. caso contrario devuelve false
	TanqueAgua* Crear(int capacidad, int caudal, int id);
	void Cargar(TanqueAgua* tanqueAgua, int caudal);
	void Vaciar(TanqueAgua* tanqueAgua, int caudal);
	int ObtenerCaudal(const TanqueAgua* tanqueAgua);
	int ObtenerCapacidad(const TanqueAgua* tanqueAgua);
	int asignarIdTanque();
	int ObtenerId(TanqueAgua* tanqueAgua);
	bool EstaVacio(const TanqueAgua* tanqueAgua);
	bool EstaLleno(const TanqueAgua* tanqueAgua);
	void Destruir(TanqueAgua* tanqueAgua);
}
#endif 