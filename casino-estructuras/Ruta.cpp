#include "Ruta.h"

Ruta::Ruta(string nombre, int velocidad, float multiplicador, int numero1)
{
	cabecera = final = NULL;
	nombreCaballo = nombre;
	numero = numero1;
	InsertarInicio(nombre, velocidad, multiplicador, numero);
	CrearLongitud(55, numero, velocidad, multiplicador);
}

void Ruta::InsertarInicio(string nombre, int velocidad, float multiplicador, int numero)
{
	nodo = new Caballo;

	nodo->nombre = nombre;

	nodo->velocidad = velocidad;

	nodo->multiplicador = multiplicador;

	nodo->numero = numero;

	nodo->sig = cabecera;

	cabecera = nodo;

	if (final == NULL)
		final = nodo;
}

void Ruta::CrearLongitud(int longitudCarril, int numero, int velocidad, float multiplicador)
{
	for (int i = 0; i < longitudCarril - 1; i++)
	{
		nodo = new Caballo;

		nodo->nombre = "_";

		nodo->velocidad = velocidad;

		nodo->numero = numero;

		nodo->multiplicador = multiplicador;

		nodo->sig = NULL;

		final->sig = nodo;

		final = nodo;

	}
}

void Ruta::RecorrerPasto(int pasos)
{
	for (int k = 0; k < pasos; k++)
	{
		string extraida;
		int num, vel;
		float mult;
		Caballo* anterior;

		anterior = NULL;

		nodo = cabecera;

		while (nodo != final)
		{
			anterior = nodo;
			nodo = nodo->sig;
		}

		if (nodo->nombre != "_")
		{
			break;
		}

		extraida = nodo->nombre;

		num = nodo->numero;

		vel = nodo->velocidad;

		mult = nodo->multiplicador;

		anterior->sig = NULL;

		final = anterior;
		delete nodo;

		InsertarInicio(extraida, vel, mult, num);

	}
}

void Ruta::MostrarCarril()
{
	bool meta;
	nodo = cabecera;

	cout << nodo->numero << ".- ";
	cout << nodo->nombre;

	nodo = cabecera->sig;
	while (nodo != NULL)
	{
		cout << " " << nodo->nombre;
		nodo = nodo->sig;
	}
	cout << endl;
}

string Ruta::GetNombre()
{
	string nombre = cabecera->nombre;
	return nombre;
}

int Ruta::GetVelocidad()
{
	int velocidad = cabecera->velocidad;
	return velocidad;
}

float Ruta::GetMultiplicador()
{
	float multiplicador = cabecera->multiplicador;
	return multiplicador;
}

string Ruta::GetNombreCaballo()
{
	return nombreCaballo;
}

int Ruta::getNumero()
{
	return numero;
}

bool Ruta::ganador(string nombreActual)
{
	if (nombreActual == "_")
	{
		return false;
	}

	if (final != NULL && final->nombre == nombreActual)
	{
		return true;  // El caballo ha ganado
	}
	return false;  // Aún no ha llegado a la meta
}



