#pragma once
#include <vector>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#define MINIMUM_BET 100

using namespace std;

enum suits {CLUBS=1, DIAMONDS, HEARTS, SPADES};

struct Card {
	enum suits suit;
	int value;
};

struct Player {
	int bet;
	Card cards[2];
};

class Poker
{
public:
	Poker();
	void generateCommunityCards();
	void renderCard(Card);
private:
	Card communityCards[5];
	int communityBet;
	vector<Player> players;
};

