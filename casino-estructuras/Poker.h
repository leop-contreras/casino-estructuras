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
#define AWAIT_TIME 200
#define SHUFFLING_TIMES 6

using namespace std;

enum suits {CLUBS=1, DIAMONDS, HEARTS, SPADES};

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
	void renderCard(Card);
	void outputPlayers();
	void playerMenu(Player*);
	int playerJoin();
	int playerLeave();
	void nextRound();
	int getValueOfHand(Player);
	void sortFullHand(Card[7]);
	void sortFullHandBySuit(Card [7], enum suits);
	vector<Player> players;
private:
	int activePlayers;
	int turnedCards, round;
	int lastID;
	Card communityCards[5];
	int communityBet, currentBet;
	stack<Card> gameDeck;
	
};

