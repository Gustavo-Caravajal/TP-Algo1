#include "GeneradorRed.h"
#include "RedPlataformasTanqueAgua.h"
#include "TanqueAgua.h"
#include <iostream>

using namespace std;
using UndavRedPlataformasTanqueAgua::Red;
using UndavTanqueAgua::TanqueAgua;

void Mostrar(TanqueAgua* tanque);

int main()
{
	Red* redDispersa = UndavGeneradorRed::GenerarRed(200, 10, 15);
	TanqueAgua * tanque1 = UndavRedPlataformasTanqueAgua::UndavRecorridoProfundidad::ObtenerTanqueDFS(redDispersa, 1500);
	Mostrar(tanque1);
	Red* redDensa = UndavGeneradorRed::GenerarRed(15, 100, 40);
	TanqueAgua* tanque2 = UndavRedPlataformasTanqueAgua::UndavRecorridoProfundidad::ObtenerTanqueDFS(redDensa, 103);
	Mostrar(tanque2);

	return 0;
}

void Mostrar(TanqueAgua* tanque)
{
	if (tanque == NULL)
	{
		cout << "No se encontro el tanque" << endl;
	}
	else
	{
		cout << "Capacidad: " << ObtenerCapacidad(tanque) << " Caudal:" << ObtenerCaudal(tanque) << endl;
	}
}
