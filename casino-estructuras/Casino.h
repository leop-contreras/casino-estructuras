#pragma once
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
	string nombre;
	int balance;
};

class Casino
{
public:
	Casino();
	void entradaJugador();
	int salidaJugador();
	int modificarBalance(Jugador, int);
	int indiceJugador(Jugador);
	void seleccionJugadores(vector<Jugador>*, int nJugadores = -1);
	void mostrarJugadores();
	string generarID();
private:
	vector<Jugador> jugadores;
};

