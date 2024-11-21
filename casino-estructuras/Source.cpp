#include "Casino.h"
#include "BackJack.h"
#include "Poker.h"
#include "RaceMenu.h"

//CARRERA

void main() {
	setlocale(LC_ALL, "");
	Casino casino;
	Poker poker;
	RaceMenu carrera;
	BackJack blackJack;

	int opc, apuesta;
	do {
		system("cls");
		cout << "\t\t$$$$ CASINO ELM $$$$" << "\n\n";
		casino.mostrarJugadores();
		cout << "\n";
		cout << "1.Entrada jugador  2.Salida jugador  3.Carrera  4.Poker  5.Blackjack  6.Salir: ";
		cin >> opc;
		cin.ignore();
		switch (opc) {
		case 1:
			casino.entradaJugador();
			break;
		case 2:
			casino.salidaJugador();
			break;
		case 3: //Carrera
			casino.seleccionJugadores(1);
			if (casino.jugadoresActivos.size() < 1) break;
			system("cls");
			cout << "Cuanto quieres apostar?  ";
			cin >> apuesta;
			cin.ignore();
			casino.jugadoresActivos[0].balance -= apuesta;
			casino.jugadoresActivos[0].balance += carrera.Apostar(1000);;
			cout << endl;
			casino.vaciarJugadoresActivos();
			break;
		case 4: //Poker
			casino.seleccionJugadores(POKER_MAX_NUMBER_PLAYERS);
			if(casino.jugadoresActivos.size() < 1) break;
			system("cls");
			poker = Poker();
			poker.play(&casino.jugadoresActivos);
			casino.vaciarJugadoresActivos();
			break;
		case 5: //Blackjack
			casino.seleccionJugadores(1);
			if (casino.jugadoresActivos.size() < 1) break;
			system("cls");
			cout << "Cuanto quieres apostar?  ";
			cin >> apuesta;
			cin.ignore();
			casino.jugadoresActivos[0].balance -= apuesta;
			casino.jugadoresActivos[0].balance += blackJack.Jugar(500);
			cout << endl;
			casino.vaciarJugadoresActivos();
			system("pause");
			break;
		}
	} while (opc != 6);

}