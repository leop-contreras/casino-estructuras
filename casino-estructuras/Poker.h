#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <windows.h>
#define MINIMUM_BET 100

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
	bool active = false;
};

class Poker
{
public:
	Poker();
	void generateCommunityCards();
	void renderCard(Card);
	void outputPlayers();
	void playerMenu(Player*);
	int playerJoin();
	int playerLeave();
	void nextRound();
	vector<Player> players;
private:
	int turnedCards, round;
	int lastID;
	Card communityCards[5];
	int communityBet, currentBet;
	
};

