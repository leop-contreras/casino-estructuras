#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <windows.h>
#include <stack>
#define MINIMUM_BET 100
#define AWAIT_TIME 2500
#define SHUFFLING_TIMES 7
#define NUMBER_PLAYERS 2

using namespace std;

enum suits { NONE = -1, CLUBS = 1, DIAMONDS, HEARTS, SPADES };

struct Card {
	enum suits suit;
	int value;
};

struct Player {
	int id;
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
	int playerJoin();
	int playerLeave();
	void nextRound();
	int getValueOfHand(Player);
	void printRanking(Player);
	void sortFullHand(Card[7]);
	void sortFullHandBySuit(Card [7], enum suits);
	vector<Player> players;
	int round;
	int turnedCards;
	bool playerBetRaisedPassed;
	bool gameBetRaised;
private:
	int betRaisedID;
	int activePlayers;
	int lastID;
	Card communityCards[5];
	int communityBet, currentBet;
	stack<Card> gameDeck;
};


string clubs[5] = {
	"|     __     |",
	"|   _(  )_   |",
	"|  (_    _)  |",
	"|    (__)    |",
	"|    /__\\    |",
};

string diamonds[5] = {
	"|     /\\     |",
	"|    /  \\    |",
	"|   (    )   |",
	"|    \\  /    |",
	"|     \\/     |",
};

string hearts[5] = {
	"|   /\\  /\\   |",
	"|  /  \\/  \\  |",
	"|  \\      /  |",
	"|   \\    /   |",
	"|    \\  /    |",
};

string spades[5] = {
	"|     /\\     |",
	"|    /  \\    |",
	"|   (    )   |",
	"|    _  _    |",
	"|    /__\\    |",
};

