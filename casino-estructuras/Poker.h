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
	void generateDeck();
	void generateCommunityCards();
	int getActivePlayers();
	void renderCard(Card);
	void renderBigCard(Card);
	void renderBigCards(stack<Card>);
	void outputPlayers();
	void playerMenu(Player*);
	void gameMenu(int);
	void endOfGameMenu();
	int playerJoin(Jugador*);
	void playerAssignCards(Player*);
	void playersLeave(vector<Jugador>*);
	void nextRound();
	int getValueOfHand(Player);
	void printRanking(Player);
	void sortFullHand(Card[7]);
	void sortFullHandBySuit(Card [7], enum suits);
	void play(vector<Jugador>*);
private:
	vector<Player> players;
	int round;
	int turnedCards;
	bool playerBetRaisedPassed;
	bool gameBetRaised;
	string betRaisedID;
	int activePlayers;
	int lastID;
	Card communityCards[5];
	int communityBet, currentBet;
	stack<Card> gameDeck;
};