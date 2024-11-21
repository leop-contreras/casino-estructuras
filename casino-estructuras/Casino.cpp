#include "Casino.h"


Casino::Casino()
{

}

void Casino::entradaJugador()
{
	system("cls");
	Jugador nuevoJugador;
	cout << "Ingresa el nombre del jugador: ";
	getline(cin, nuevoJugador.nombre);
;	cout << "Ingresa su balance inicial: ";
	cin >> nuevoJugador.balance;
	cin.ignore();
	nuevoJugador.id = generarID();
	jugadores.push_back(nuevoJugador);
}

int Casino::salidaJugador()
{
	int opc;
	system("cls");
	cout << "\t\t  % JUGADORES %" << endl;
	cout << "##" << "\t=       ID        =  Nombre  =  Balance" << endl;
	for (int i = 0; i < jugadores.size(); i++) {
		cout << i + 1 << "\t " << jugadores[i].id << " - " << jugadores[i].nombre << " - " << jugadores[i].balance << endl;
	}
	cout << "\n\n";

	cout << "- Selecciona un jugador -" << endl;
	cout << "#: ";
	cin >> opc;
	cin.ignore();

	if (opc > jugadores.size() || opc < 0) {
		cout << "Elige un jugador valido" << endl;
		system("pause");
		return -1;
	}
	else {
		jugadores.erase(jugadores.begin() + opc -1);
		return 0;
	}
}

int Casino::modificarBalance(Jugador jugador, int valor)
{
	int indice = indiceJugador(jugador);
	if (indice <= -1) {
		cout << "Jugador no encontrado";
		return -1;
	}
	else {
		jugadores[indice].balance += valor;
		return 0;
	}
}

int Casino::indiceJugador(Jugador jugador)
{
	for (int i = 0; i < jugadores.size(); i++) {
		if (jugadores[i].id == jugador.id) {
			return i;
		}
	}
	return -1;
}

void Casino::seleccionJugadores(int nJugadores)
{
	int opc, contador = 0;

	do {
		system("cls");
		cout << "\t\t  % JUGADORES %" << endl;
		cout << "##" << "\t=       ID        =  Nombre  =  Balance" << endl;
		for (int i = 0; i < jugadores.size(); i++) {
			cout << i + 1 << "\t " << jugadores[i].id << " - " << jugadores[i].nombre << " - " << jugadores[i].balance << endl;
		}
		cout << "\n\n";

		cout << "Seleccionados: " << endl;
		for (int i = 0; i < jugadoresActivos.size(); i++) {
			cout << jugadoresActivos[i].nombre;
			if (i < (jugadoresActivos.size()-1)) cout << ", ";
		}
		cout << "\n\n";

		cout << "+ Selecciona un jugador +" << endl;
		if (nJugadores == 1) {
			cout << "!Este juego solo permite un jugador!" << endl;
		}
		else {
			if (nJugadores > 1) {
				cout << "Jugadores máximos restantes: " << (nJugadores-contador) << endl;
			}
			cout << "-1 para terminar seleccion" << endl;
		}
		cout << "#: ";
		cin >> opc;
		cin.ignore();

		if (opc == -1) {
			contador = 999;
		}
		else{
			if (opc > jugadores.size()) {
				cout << "No hay tantos jugadores" << endl;
				system("pause");
			}
			else {
				jugadoresActivos.push_back(jugadores[(opc - 1)]);
				contador++;
			}
		}
	} while (contador < nJugadores || nJugadores == -1);
}

void Casino::vaciarJugadoresActivos()
{
	for (int i = 0; i < jugadoresActivos.size(); i++) {
		if (jugadoresActivos[i].id == jugadores[i].id) {
			jugadores[i].balance = jugadoresActivos[i].balance;
		}
	}
	jugadoresActivos.clear();
	jugadoresActivos.shrink_to_fit();
}

void Casino::mostrarJugadores()
{
	cout << "\t\t % JUGADORES %" << endl;
	cout << "=       ID        =  Nombre  =  Balance" << endl;
	for (int i = 0; i < jugadores.size(); i++) {
		cout << " " << jugadores[i].id << " - " << jugadores[i].nombre << " - " << jugadores[i].balance << endl;
	}
}

string Casino::generarID()
{
	srand(time(0));
	char chId[16];
	for (int i = 0; i < 16; i++) {
		if ((rand() % 2) == 0) {
			chId[i] = (rand() % 26) + 97;
		}
		else {
			chId[i] = (rand() % 26) + 65;
		}
	}

	string strId(chId, 16);

	return strId;
}
