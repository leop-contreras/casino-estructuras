#include "Poker.h"

Poker::Poker()
{
	currentBet = MINIMUM_BET;
	lastID = 0;
	turnedCards = 0;
	round = 0;
	activePlayers = 0;
}

void Poker::generateDeck()
{
	srand(time(0));
	Card card;
	Card generatedGameDeck[52];
	int rndNumber = 0;
	int index = 0;
	for (int j = 0; j < 4; j++) {
		card.suit = static_cast<suits>(j + 1);
		for (int i = 0; i < 13; i++) {
			card.value = i;
			generatedGameDeck[index++] = card;
			/*renderCard(generatedGameDeck[index - 1]);
			cout << ",";*/
		}
	}
	//cout << endl;

	//Shuffle
	cout << "Shuffling..." << endl;
	for (int j = 0; j < SHUFFLING_TIMES; j++) {
		for (int i = 0; i < 52; i++) {
			rndNumber = (rand() % 51);
			card = generatedGameDeck[i];
			renderCard(card);
			cout << ",";
			generatedGameDeck[i] = generatedGameDeck[rndNumber];
			generatedGameDeck[rndNumber] = card;
		}
		system("cls");
	}
	//Push to game deck
	for (int i = 0; i < 52; i++) {
		gameDeck.push(generatedGameDeck[i]);
		//renderCard(gameDeck.top());
		//cout << ",";
	}
	cout << "Done!" << endl;
	system("cls");
}

void Poker::generateCommunityCards()
{
	for (int i = 0; i < 5; i++) {
		communityCards[i] = gameDeck.top();
		gameDeck.pop();
	}
}

int Poker::getActivePlayers()
{
	int nPlayers = 0;
	for (int i = 0; i < players.size(); i++) {
		if (players[i].active) {
			nPlayers++;
		}
	}
	return nPlayers;
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
	case 9: printValue = "10"; break;
	case 10: printValue = 'j'; break;
	case 11: printValue = 'q'; break;
	case 12: printValue = 'k'; break;
	case 13: printValue = 'a'; break;
	default: printValue = char(card.value + 49); break;
	}
	cout << "[" << printSuit << printValue << "]";
}

void Poker::outputPlayers()
{
	cout << "ID | Nombre | Balance" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << players[i].id << " - " << players[i].name << " - " << players[i].balance << endl;
	}
}

void Poker::playerMenu(Player* player)
{
	cout << "\n";
	cout << "Jugador: " << player->name << endl;

	cout << "Tus Cartas: ";
	renderCard(player->cards[0]); cout << " ";
	renderCard(player->cards[1]); cout << endl;
	//cout << "Valor de la baraja: " << player->valueOfHand << endl;
	cout << "Apuesta de la Mesa: " << currentBet << "\t\t\t";
	cout << "Tu balance: " << player->balance << endl << endl;
	if (!player->active) {
		cout << "~ Ya te haz retirado de la partida ~" << endl;
		Sleep(AWAIT_TIME);
		return;
	}
	if (player->balance == 0) {
		cout << "= Ya haz metido todo tu balance =" << endl;
		Sleep(AWAIT_TIME);
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
			Sleep(AWAIT_TIME);
			return;
		case 2:
			if (!betRaised) {
				cout << "* knock knock *" << endl;
				Sleep(AWAIT_TIME);
				return;
			}
			else {
				if (options[1] == "ALL-IN") {
					player->bet = player->balance;
					player->balance -= player->bet;
					communityBet += player->bet;
					currentBet = player->bet;
					cout << "!!! ALL-IN !!!" << endl;
					Sleep(AWAIT_TIME);
					return;
				}
				else {
					player->bet = currentBet;
					player->balance -= player->bet;
					communityBet += player->bet;
					cout << "$ Haz igualado la apuesta $" << endl;
					Sleep(AWAIT_TIME);
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
					Sleep(AWAIT_TIME);
					return;
				}
				else if (newBet <= currentBet) {
					cout << "! La Apuesta de la Mesa es mayor !" << endl;
					Sleep(AWAIT_TIME);
				}
				else {
					player->bet = newBet;
					player->balance -= player->bet;
					communityBet += player->bet;
					currentBet = player->bet;
					cout << "$ Haz apostado " << newBet << " $" << endl;
					Sleep(AWAIT_TIME);
					return;
				}
			} while (true);
		}
	} while (true);
}

void Poker::gameMenu(int index)
{
	system("cls");
	if (index + 1 > players.size()) {
		index = 0;
	}
	cout << "Jugadores: " << players.size() << endl;
	cout << "Siguiente jugador >> " << players[index].name << endl;
	cout << "Apuesta acumulada: " << communityBet << "\n\n";
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
}

void Poker::endOfGameMenu()
{
	system("cls");
	cout << "\n";
	for (int i = 0; i < 5; i++) {
		renderCard(communityCards[i]);
		cout << " ";
	}
	cout << "\n\n";
	cout << "Apuesta acumulada: " << communityBet << endl;
	cout << "Apuesta de la Mesa: " << currentBet << "\n\n";
	cout << "Nombre | Apuesta |  Cartas  |  Ranking" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << players[i].name << " - " << players[i].bet << " - ";
		renderCard(players[i].cards[0]); cout << ",";
		renderCard(players[i].cards[1]); cout << " - ";
		printRanking(players[i]);
		cout << endl;
	}
	int winnerIndexes[NUMBER_PLAYERS], winningScore = -1, nWinningPlayers = 0;
	for (int i = 0; i < NUMBER_PLAYERS; i++) {
		winnerIndexes[i] = 0;
	}
	for (int i = 0; i < players.size(); i++) {
		if (players[i].active && players[i].valueOfHand > winningScore) {
			for (int j = 0; j < NUMBER_PLAYERS; j++) {
				winnerIndexes[j] = 0;
			}
			nWinningPlayers = 0;
			winnerIndexes[nWinningPlayers] = i;
			nWinningPlayers++;
		}
		else if (players[i].active && players[i].valueOfHand == winningScore) {
			winnerIndexes[nWinningPlayers] = i;
			nWinningPlayers++;
		}
	}
	for (int i = 0; i < NUMBER_PLAYERS; i++) {
		if (winnerIndexes[i] == i) {
			cout << "!!! " << players[i].name << " ha ganado con ";
			printRanking(players[i]); cout << " !!!" << endl;
		}
	}
	if (nWinningPlayers > 1) {
		cout << "! Se ha distribuido la apuesta a " << nWinningPlayers << "jugadores !" << endl;
	}
	cout << communityBet/ nWinningPlayers << " otorgado";
	cout << endl;
	system("pause");
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
	newPlayer.cards[0] = gameDeck.top();
	gameDeck.pop();
	newPlayer.cards[1] = gameDeck.top();
	gameDeck.pop();
	newPlayer.id = ++lastID;
	newPlayer.valueOfHand = getValueOfHand(newPlayer);
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

int Poker::getValueOfHand(Player player)
{
	int valueOfHand = 0;
	Card fullHand[7];
	//Clubs, Diamonds, Hearts, Spades
	int nOfSuit[4] = { 0,0,0,0 };
	for (int i = 0; i < 5; i++) {
		fullHand[i] = communityCards[i];
	}
	for (int i = 0; i < 2; i++) {
		fullHand[i+5] = player.cards[i];
	}

	//Count suit
	for (int i = 0; i < 7; i++) {
		switch (fullHand[i].suit) {
		case CLUBS: nOfSuit[0]++; break; //Trebol
		case DIAMONDS: nOfSuit[1]++; break; //Diamantes
		case HEARTS: nOfSuit[2]++; break; //Corazones
		case SPADES: nOfSuit[3]++; break; //Picas
		}
	}

	//10, 9, y 6
	if (nOfSuit[0] >= 5 || nOfSuit[1] >= 5 || nOfSuit[2] >= 5 || nOfSuit[3] >= 5) {
		int indexSuit;
		int inARow = 0;
		int indexARow = -1;
		for (int i = 0; i < 4; i++) {
			if (nOfSuit[i] >= 5){
				indexSuit = i;
			}
		}
		switch (indexSuit) {
		case 0: sortFullHandBySuit(fullHand, CLUBS); break; //Trebol
		case 1: sortFullHandBySuit(fullHand, DIAMONDS); break; //Diamantes
		case 2: sortFullHandBySuit(fullHand, HEARTS); break; //Corazones
		case 3: sortFullHandBySuit(fullHand, SPADES); break; //Picas
		}

		for (int i = 0; i < 6; i++) {
			if(fullHand[i].value == fullHand[i + 1].value + 1){
				if(inARow < 1){
					indexARow = i;
				}
				inARow++;
			}
		}

		if (fullHand[0].value == 13 && inARow >= 5) {
			valueOfHand = 10000;
			return valueOfHand;
		}
		if (inARow >= 5) {
			valueOfHand = 9000;
			valueOfHand += fullHand[indexARow].value;
			return valueOfHand;
		}
		else {
			valueOfHand = 6000;
			valueOfHand += fullHand[indexARow].value;
			return valueOfHand;
		}
	}

	//Sort
	sortFullHand(fullHand);

	//SORTED HANDS RENDER - remove
	/*
	cout << "Hand sorted: ";
	for (int i = 0; i < 7; i++) {
		renderCard(fullHand[i]); cout << ",";
	}
	cout << endl;*/
	
	//8
	for (int i = 0; i < 4; i++) {
		if (fullHand[i].value == fullHand[i + 1].value &&
			fullHand[i].value == fullHand[i + 2].value &&
			fullHand[i].value == fullHand[i + 3].value) {
			valueOfHand = 8000;
			valueOfHand += fullHand[i].value;
			return valueOfHand;
		}
	}
	
	//Detect threeOAK and twoOAK
	int threeOAKValue = -1, twoOAKValue = -1;
	for (int i = 0; i < 5; i++) {
		if (fullHand[i].value == fullHand[i + 1].value && fullHand[i].value == fullHand[i + 2].value) {
			threeOAKValue = fullHand[i].value;
			break;
		}
	}
	for (int i = 0; i < 6; i++) {
		if (fullHand[i].value == fullHand[i + 1].value && threeOAKValue != fullHand[i].value) {
			twoOAKValue = fullHand[i].value;
			break;
		}
	}

	//7
	if (threeOAKValue > -1 && twoOAKValue > -1) {
		valueOfHand = 7000;
		if (threeOAKValue > twoOAKValue) {
			valueOfHand += 200;
		}
		else {
			valueOfHand += 100;
		}
		valueOfHand += threeOAKValue;
		return valueOfHand;
	}

	//5
	int inARow = 0;
	int indexARow = -1;
	for (int i = 0; i < 6; i++) {
		if (fullHand[i].value == fullHand[i + 1].value+1) {
			if (inARow < 1) {
				indexARow = i;
			}
			inARow++;
		}
	}
	if (inARow >= 5) {
		valueOfHand = 5000;
		valueOfHand += fullHand[indexARow].value;
		return valueOfHand;
	}

	//4
	if (threeOAKValue > -1) {
		valueOfHand = 4000;
		valueOfHand += threeOAKValue;
		return valueOfHand;
	}

	//3
	int secondTwoOakValue = -1;
	for (int i = 0; i < 6; i++) {
		if (fullHand[i].value == fullHand[i + 1].value && twoOAKValue != fullHand[i].value) {
			secondTwoOakValue = fullHand[i].value;
			break;
		}
	}
	if (twoOAKValue > -1 && secondTwoOakValue > -1) {
		valueOfHand = 3000;
		if (twoOAKValue > secondTwoOakValue) {
			valueOfHand += twoOAKValue * 10;
			valueOfHand += secondTwoOakValue;
		}
		else {
			valueOfHand += secondTwoOakValue * 10;
			valueOfHand += twoOAKValue;
		}
		return valueOfHand;
	}
	
	//2
	if(twoOAKValue > -1){
		valueOfHand = 2000;
		valueOfHand += twoOAKValue;
		return valueOfHand;
	}

	//1
	valueOfHand = 1000;
	if (player.cards[0].value > player.cards[1].value) {
		valueOfHand += player.cards[0].value;
	}
	else {
		valueOfHand += player.cards[1].value;
	}
	
	return valueOfHand;
}

void Poker::printRanking(Player player)
{
	int handValue = player.valueOfHand;
	if (handValue < 2000) { cout << "Carta Alta / High Card"; }
	else if (handValue < 3000) { cout << "Par / Pair"; }
	else if (handValue < 4000) { cout << "Doble Par / Double Pair"; }
	else if (handValue < 5000) { cout << "Tercia / Three of a Kind"; }
	else if (handValue < 6000) { cout << "Escalera / Straight"; }
	else if (handValue < 7000) { cout << "Color / Flush"; }
	else if (handValue < 8000) { cout << "Full / Full House"; }
	else if (handValue < 9000) { cout << "Poker / Poker"; }
	else if (handValue < 10000) { cout << "Escalera de Color / Straight Flush"; }
	else if (handValue >= 10000) { cout << "Escalera Real / Royal Flush"; }
	else { cout << "????"; }
}

void Poker::sortFullHand(Card fullHand[7])
{
	Card foo;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if (fullHand[j].value < fullHand[j + 1].value) {
				foo = fullHand[j];
				fullHand[j] = fullHand[j + 1];
				fullHand[j + 1] = foo;
			}
		}
	}
}

void Poker::sortFullHandBySuit(Card fullHand[7], suits suit)
{
	Card foo;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if ((fullHand[j].value < fullHand[j + 1].value) || fullHand[j].suit != suit) {
				foo = fullHand[j];
				fullHand[j] = fullHand[j + 1];
				fullHand[j + 1] = foo;
			}
		}
	}
}

void main() {
	setlocale(LC_ALL, "");

	Poker game;
	bool debug = false;
	if (debug) {
		game.turnedCards = 5;
		game.generateDeck();
		game.generateCommunityCards();
		game.playerJoin();
		game.outputPlayers();
		game.players[0].active = true;
		game.playerMenu(&game.players[0]);
		game.nextRound();
		game.playerMenu(&game.players[0]);
		return;
	}

	game.generateDeck();
	game.generateCommunityCards();
	for (int i = 0; i < NUMBER_PLAYERS; i++) {
		game.playerJoin();
		game.players[i].active = true;
	}
	game.outputPlayers();
	system("pause");
	do {
		for (int i = 0; i < game.players.size(); i++) {
			game.gameMenu(i);
			game.playerMenu(&game.players[i]);
		}
		game.nextRound();
		if (game.round > 3 || game.getActivePlayers() <= 1) {
			break;
		}
	} while (true);
	game.endOfGameMenu();
}
