#include "Poker.h"

Poker::Poker()
{
	currentBet = MINIMUM_BET;
	lastID = 0;
	turnedCards = 0;
	round = 0;
}

void Poker::generateCommunityCards()
{
	srand(time(0)); // Seed the random number generator with the current time
	for (int i = 0; i < 5; i++) {
		Card newCard;
		newCard.suit = static_cast<suits>(rand() % 4 + 1);
		newCard.value = rand() % 13 + 1;
		communityCards[i] = newCard;
		//renderCard(communityCards[i]);
		//cout << ",";
	}
}

void Poker::renderCard(Card card)
{
	char printSuit = ' ';
	string printValue = "";
	switch (card.suit) {
	case CLUBS: printSuit = 'T'; break; //Trebol
	case DIAMONDS: printSuit = 'D'; break; //Diamantes
	case HEARTS: printSuit = 'C'; break; //Corazones
	case SPADES: printSuit = 'P'; break; //Picas
	}
	switch (card.value) {
	case 10: printValue = "10"; break;
	case 11: printValue = 'j'; break;
	case 12: printValue = 'q'; break;
	case 13: printValue = 'k'; break;
	default: printValue = char(card.value + 48); break;
	}
	cout << "[" << printSuit << printValue << "]";
}

void Poker::outputPlayers()
{
	cout << "ID | Nombre | Monto" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << players[i].id << " - " << players[i].name << " - " << players[i].balance << endl;
	}
}

void Poker::playerMenu(Player* player)
{
	system("cls");
	cout << "\n\n";
	cout << "Acumulado: " << communityBet << "\n\n";
	cout << "\t";
	for (int i = 0; i < turnedCards; i++) {
		renderCard(communityCards[i]);
		cout << " ";
	}
	for (int i = 0; i < (5 - turnedCards); i++) {
		cout << "[  ]";
		cout << " ";
	}
	cout << endl << "\n\n";

	cout << "Tus Cartas: ";
	renderCard(player->cards[0]); cout << " ";
	renderCard(player->cards[1]); cout << endl;
	cout << "Apuesta de la Mesa: " << currentBet << "\t\t\t";
	cout << "Tu balance: " << player->balance << endl << endl;
	if (!player->active) {
		cout << "~ Ya te haz retirado de la partida ~" << endl;
		Sleep(3000);
		return;
	}
	if (player->balance == 0) {
		cout << "= Ya haz metido todo tu balance =" << endl;
		Sleep(3000);
		return;
	}
	string options[3] = {"RETIRARSE/FOLD", "PASAR/CHECK", "APOSTAR/BET"};
	int opc;
	bool betRaised = false;

	if (player->bet < currentBet) {
		options[1] = "IGUALAR/CALL";
		options[2] = "SUBIR/RAISE";
		betRaised = true;
		if (currentBet > player->balance) {
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
			player->active = false;
			Sleep(2000);
			return;
		case 2:
			if (!betRaised) {
				cout << "* knock knock *" << endl;
				Sleep(2000);
				return;
			}
			else {
				if (options[1] == "ALL-IN") {
					player->bet = player->balance;
					player->balance -= player->bet;
					communityBet += player->bet;
					currentBet = player->bet;
					cout << "!!! ALL-IN !!!" << endl;
					Sleep(2000);
					return;
				}
				else {
					player->bet = currentBet;
					player->balance -= player->bet;
					communityBet += player->bet;
					cout << "$ Haz igualado la apuesta $" << endl;
					Sleep(2000);
					return;
				}
			}
		case 3:
			int newBet;
			do {
				cout << "-----------------------" << endl;
				cout << "Tu nueva apuesta -> ";
				cin >> newBet;
				if (newBet > player->balance) {
					cout << "! No cuentas con el balance suficiente !" << endl;
				}
				else if (newBet == player->balance) {
					player->bet = player->balance;
					player->balance -= player->bet;
					communityBet += player->bet;
					currentBet = player->bet;
					cout << "!!! ALL-IN !!!" << endl;
					Sleep(2000);
					return;
				}
				else if (newBet <= currentBet) {
					cout << "! La Apuesta de la Mesa es mayor !" << endl;
					Sleep(2000);
				}
				else {
					player->bet = newBet;
					player->balance -= player->bet;
					communityBet += player->bet;
					currentBet = player->bet;
					cout << "$ Haz apostado " << newBet << " $" << endl;
					Sleep(2000);
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
	do {
		cout << "Ingresa el balance con el que ingresa (+ de " << MINIMUM_BET * 10 << "): ";
		cin >> newPlayer.balance;
		cin.ignore();
		if (newPlayer.balance >= MINIMUM_BET * 10) {
			break;
		}
	} while (true);
	Card newCard;
	newCard.suit = static_cast<suits>(rand() % 4 + 1);
	newCard.value = rand() % 13 + 1;
	newPlayer.cards[0] = newCard;
	newCard.suit = static_cast<suits>(rand() % 4 + 1);
	newCard.value = rand() % 13 + 1;
	newPlayer.cards[1] = newCard;
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

void Poker::nextRound()
{
	round++;
	switch (round) {
	case 1:
		turnedCards += 3;
		break;
	case 2:
		turnedCards ++;
		break;
	case 3:
		turnedCards ++;
		break;
	}
}

void main() {
	setlocale(LC_ALL, "");

	Poker game;
	game.generateCommunityCards();
	game.playerJoin();
	game.outputPlayers();
	game.players[0].active = true;
	game.playerMenu(&game.players[0]);
	game.nextRound();
	game.playerMenu(&game.players[0]);
}
