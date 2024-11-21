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
	void entradaJugador(); //Agrega nuevos jugadores al vector
	int salidaJugador(); //Saca jugadores del vector
	int modificarBalance(Jugador, int); //Modifica el balance de jugadores manualmente
	int indiceJugador(Jugador); //Obtiene el indice de un jugador en el vector
	void seleccionJugadores(int nJugadores = -1); //Menu de seleccion de jugadores para los juegos
	void vaciarJugadoresActivos(); //Vacia jugadoresActivos y pasa el balance a jugadores
	void mostrarJugadores(); //Muestra los jugadores del casino
	string generarID(); //Genera un ID aleatorio de 16 caracteres
	vector<Jugador>jugadoresActivos; //Jugadores del juego actual
private:
	vector<Jugador> jugadores; //Jugadores en el casino
};

