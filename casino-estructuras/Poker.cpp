#include "Poker.h"

Poker::Poker()
{
}

void Poker::generateCommunityCards()
{
	srand(time(0)); // Seed the random number generator with the current time
	for (int i = 0; i < 5; i++) {
		Card newCard;
		newCard.suit = static_cast<suits>(rand() % 4 + 1);
		newCard.value = rand() % 13 + 1;
		communityCards[i] = newCard;
		cout << communityCards[i].suit << communityCards[i].value << ",";
	}
}

void Poker::renderCard(Card card)
{
	char printSuit, printValue; 
	switch (card.suit) {
	case CLUBS: printSuit = 'T'; break; //Trebol
	case DIAMONDS: printSuit = 'D'; break; //Diamantes
	case HEARTS: printSuit = 'C'; break; //Corazones
	case SPADES: printSuit = 'P'; break; //Picas
	}
}

void main() {
	Poker game;
	game.generateCommunityCards();
}
