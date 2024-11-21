#pragma once
#include <iostream>
#include "Ruta.h"

using namespace std;

// #define TAM 10

struct Caballo
{
	string nombre;
	int velocidad;
	int numero;
	float multiplicador;
	Caballo* sig;
};

class Ruta
{
public:
	Ruta(string, int, float, int);
	void InsertarInicio(string, int, float, int);
	void CrearLongitud(int, int, int, float);
	void RecorrerPasto(int);
	void MostrarCarril();
	string GetNombre();
	int GetVelocidad();
	float GetMultiplicador();
	string GetNombreCaballo();
	int getNumero();
	bool ganador(string);
private:
	Caballo* cabecera, * final, * nodo;
	string nombreCaballo;
	int numero;
};

