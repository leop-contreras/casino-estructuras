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

void main() {
	setlocale(LC_ALL, "");

	Poker game;
	game.generateCommunityCards();
}
