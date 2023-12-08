#ifndef UNDAVPILA_H
#define UNDAVPILA_H

namespace UndavPila {
	struct Pila;
	struct NodoPila;

	Pila* CrearPila();
	NodoPila* CrearNodo(int item, NodoPila* siguiente);
	void Apilar(Pila* pila, int item); // PUSH
	int Desapilar(Pila* pila);         // POP (POPEYE)
	bool EstaVacia(const Pila* pila);
	void DestruirPila(Pila* pila);
}

#endif