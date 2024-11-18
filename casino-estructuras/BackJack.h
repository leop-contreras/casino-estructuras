#pragma once
#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

struct Carta {
	string nombre;
	int valor;
};



class BackJack
{
public:
	BackJack();
	int generarIndiceAleatorio(bool usados[]);
	void inicializarBaraja();
	void barajear();
	int Puntaje(stack <Carta> pila);
	int Jugar(int apuesta);

private:
	
	stack <Carta> JUGADOR;
	stack <Carta> CASA;
	stack <Carta> BARAJA;
	Carta BarajaSM[52];
	bool usados[52] = { false };
	
	
};

