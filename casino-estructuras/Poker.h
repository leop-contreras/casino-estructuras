#pragma once
#include "Casino.h"
#define MINIMUM_BET 100
#define AWAIT_TIME 500
#define SHUFFLING_TIMES 7
#define POKER_MAX_NUMBER_PLAYERS 5

using namespace std;

extern enum suits { NONE = -1, CLUBS = 1, DIAMONDS, HEARTS, SPADES };

struct Card {
	enum suits suit;
	int value;
};

struct Player {
	string id;
	string name;
	int balance;
	int bet = 0;
	Card cards[2];
	int valueOfHand = 0;
	bool active = false;
};

class Poker
{
public:
	Poker();
	void generateDeck(); //Genera la baraja del juego
	void generateCommunityCards(); //Genera las cartas del centro de la mesa
	int getActivePlayers(); //Obtiene los jugadores que aun pueden actuar
	void renderCard(Card); //Imprime la carta en el formato [S1]
	void renderBigCard(Card); //Imprime la carta con ascii art
	void renderBigCards(stack<Card>); //Imprime varias cartas con ascii art una alado de otra
	void outputPlayers(); //Muestra los jugadores dentro de Poker
	void playerMenu(Player*); //Seccion del menu de jugador
	void gameMenu(int); //Seccion del menu general
	void endOfGameMenu(); //Funcion para final de juego
	int playerJoin(Jugador*); //Vincula a Jugador con Player
	void playerAssignCards(Player*); //Asigna las 2 cartas del jugador
	void playersLeave(vector<Jugador>*); //Vacia todos los Players y vacia balances en Jugador
	void nextRound(); //Siguiente ronda
	int getValueOfHand(Player); //Obtener el valor de la baraja (las 7 cartas) conforme a las reglas de Poker
	void printRanking(Player); //Obtiene el ranking (nombre de la mano)
	void sortFullHand(Card[7]); //Acomoda la baraja de 7 cartas por valor
	void sortFullHandBySuit(Card [7], enum suits); //Acomoda la baraja de 7 cartas por palo
	void play(vector<Jugador>*); //Metodo para jugar
private:
	vector<Player> players; //Players (registro especifico de jugador para Poker)
	int round; //Numero de round
	int turnedCards; //Numero de cartas del centro volteadas
	bool playerBetRaisedPassed; //Si el jugador que elevo la apuesta ya paso
	bool gameBetRaised; //Si la apuesta se ha subido
	string betRaisedID; //ID del jugador que subio la apuesta
	int activePlayers; //Numero de jugadores que aun pueden actuar
	Card communityCards[5]; //Cartas del centro de la mesa
	int communityBet, currentBet; //Apuesta acumulada y apuesta actual
	stack<Card> gameDeck; //Baraja del juego (las 52 cartas)
};