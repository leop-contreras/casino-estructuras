#pragma once
#include <list>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <windows.h>
#include <vector>
#include <stack>
#include <thread>
#include <chrono> 

using namespace std;

struct Jugador {
	string id;
	string name;
	int balance;
};

class Casino
{
public:
	Casino();
	void entradaJugador();
	void salidaJugador();
	int modificarBalance(Jugador, int);
	int indiceJugador(Jugador);
	string generarID();
private:
	list<Jugador> jugadores;
};

