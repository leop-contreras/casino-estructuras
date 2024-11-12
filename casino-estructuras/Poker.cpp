#include "Poker.h"

Poker::Poker()
{
	currentBet = MINIMUM_BET;
	lastID = 0;
}

void Poker::generateCommunityCards()
{
	srand(time(0)); // Seed the random number generator with the current time
	for (int i = 0; i < 5; i++) {
		Card newCard;
		newCard.suit = static_cast<suits>(rand() % 4 + 1);
		newCard.value = rand() % 13 + 1;
		communityCards[i] = newCard;
		renderCard(communityCards[i]);
		cout << ",";
	}
}

void Poker::renderCard(Card card)
{
	char printSuit = ' ', printValue = ' ';
	switch (card.suit) {
	case CLUBS: printSuit = 'T'; break; //Trebol
	case DIAMONDS: printSuit = 'D'; break; //Diamantes
	case HEARTS: printSuit = 'C'; break; //Corazones
	case SPADES: printSuit = 'P'; break; //Picas
	}
	switch (card.value) {
	case 11: printValue = 'j'; break;
	case 12: printValue = 'q'; break;
	case 13: printValue = 'k'; break;
	default: printValue = char(card.value + 48); break;
	}
	cout << printSuit << printValue;
}

void Poker::outputPlayers()
{
	cout << "ID | Nombre | Monto" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << players[i].id << " - " << players[i].name << " - " << players[i].balance << endl;
	}
}

void Poker::playerMenu(Player player)
{
	if (!player.active) { return; }
	string options[3] = {"RETIRARSE/FOLD", "PASAR/CHECK", "APOSTAR/BET"};
	int opc;
	bool betRaised = false;

	if (player.bet < currentBet) {
		options[1] = "IGUALAR/CALL";
		options[2] = "SUBIR/RAISE";
		betRaised = true;
		if (currentBet > player.balance) {
			options[1] = "ALL-IN";
			options[2] = "ALL-IN";
		}
	}

	do{
		for (int i = 0; i < 3; i++) {
			cout << (i + 1) << "." << options[i] << "  ";
		}
		cout << ":";
		cin >> opc;
		cin.ignore();
		switch (opc) {
		case 1:
			cout << "~ Haz abandonado esta partida ~" << endl;
			player.active = false;
			return;
		case 2:
			if (!betRaised) {
				cout << "* knock knock *" << endl;
				return;
			}
			else {
				if (options[1] == "ALL-IN") {
					cout << "ALL-IN !!" << endl;
					return;
				}
				else {
					cout << "$ Haz igualado la apuesta $" << endl;
					return;
				}
			}
			return;
		case 3:
			int newBet;
			do {
				cout << "CARTAS: ";
				renderCard(player.cards[0]); renderCard(player.cards[1]); cout << endl;
				cout << "Apuesta de la Mesa: " << currentBet << endl;
				cout << "Tu balance: " << player.balance << endl;
				cout << "-----------------------" << endl;
				cout << "Tu nueva apuesta -> ";
				cin >> newBet;
				if (newBet > player.balance) {
					cout << "! No cuentas con el balance suficiente !" << endl;
				}
				else if (newBet == player.balance) {
					cout << "ALL-IN" << endl;
					return;
				}
				else if (newBet < currentBet) {
					cout << "! La Apuesta de la Mesa es mayor !" << endl;
				}
				else {
					cout << "$ Haz apostado " << newBet << " $" << endl;
					return;
				}
			} while (true);
		}
	} while (true);
}

int Poker::playerJoin()
{
	Player newPlayer;
	cout << "Ingresa el nombre del jugador: ";
	getline(cin, newPlayer.name);
	cout << "Ingresa el monto con el que ingresa: ";
	cin >> newPlayer.balance;
	cin.ignore();
	newPlayer.id = ++lastID;
	players.push_back(newPlayer);
	return 0;
}

int Poker::playerLeave()
{
	int deleteID;
	cout << "ID del Jugador: ";
	cin >> deleteID;
	for (int i = 0; i < players.size(); i++) {
		if (players[i].id == deleteID) {
			cout << "Removed " << players[i].name << " succesfully." << endl;
			players.erase(players.begin() + i);
			return 0;
		}
	}
	return 1;
}

void main() {
	setlocale(LC_ALL, "");

	Poker game;
	game.playerJoin();
	game.outputPlayers();
	game.players[0].active = true;
	game.playerMenu(game.players[0]);
	//game.generateCommunityCards();
}
