
namespace UndavLista {
	struct Lista;
	struct Nodo;

	Lista* CrearListaVacia();
	Lista* CrearLista(void* items[], int cantidadItems);

	Nodo* CrearNodo(void* item, Nodo* siguiente);
	Nodo* CrearUltimoNodo(void* item);
	void DestruirNodo(Nodo* nodo);

	void AgregarAlComienzo(Lista* lista, void* item);
	void AgregarAlFinal(Lista* lista, void* item);

	void QuitarPrimero(Lista* lista);
	void QuitarUltimo(Lista* lista);

	void Vaciar(Lista* lista);

	bool Existe(Lista* lista, void* item);
	bool EstaVacia(const Lista* lista);
	int CantidadItems(const Lista* lista);

	namespace IteradorLista {
		struct Iterador;
		// Precondicion: @lista es una instancia valida
		// Postcondicion: Crea un iterador que apunta al comienzo de la lista
		Iterador* Comienzo(Lista* lista);

		// Precondicion: @iterador es una instancia valida
		// Postcondicion: Devuleve true si iterador esta apuntando al final de la lista
		bool EsFin(const Iterador* iterador);
		void Siguiente(Iterador* iterador);
		void* ObtenerItem(Iterador* iterador);
		void Reemplazar(IteradorLista::Iterador* iterador, void* item);
		void Destruir(Iterador* iterador);
	} // namespace IteradorLista

	void Quitar(Lista* lista, IteradorLista::Iterador* iterador);
	void Destruir(Lista* lista);
}

