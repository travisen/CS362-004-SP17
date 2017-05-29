#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


/* Tests shuffle
 * -checks that the number of cards in the deck is the same after the shuffle
 * -checks that the number of each type of card is the same after the shuffle
 * -checks that the original deck and the new deck are different
 * -checks that supply counts are unchanged
 * -checks that other players' hands, decks and discards are unchanged
*/


int main(){

	//initializations

	int seed = 1000;
	int i;
	int numPlayers = 2;
	int p = 0; //player number

	int deckCount = 20;
	int deck[deckCount];

	//initialize a deck with two of each of the first ten cards
	//(estate, duchy, province, ... gardens)
	for(i = 0; i < deckCount; i++){
		deck[i] = i/2 + 1;
	}

	//initialize the gamestate

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	struct gameState G, G2;
	initializeGame(numPlayers, k, seed, &G);

	memcpy(G.deck[p], deck, sizeof(int) * deckCount);
	G.deckCount[p] = deckCount;

	memcpy(&G2, &G, sizeof(struct gameState));


	//call the function
	shuffle(p, &G);



	//assert the results

	int cardCount[10] = {0};// array of the card counts

	for(i = 0; i < G.deckCount[p]; i++){
		if(G.deck[p][i] >= 1 && G.deck[p][i] <= 10){
			cardCount[G.deck[p][i] - 1]++; //count each card
		}
	}

	int cardCountFail = 0;
	for(i = 0; i < 10; i++){
		if(cardCount[i] != 2){
			cardCountFail = 1;
		}
	}


	//check that the number of cards in the deck is unchanged
	asserttrue(G.deckCount[p] == deckCount, "SHUFFLE number of cards in deck unchanged");

	//check that the number of each type of card is correct
	asserttrue(cardCountFail == 0, "SHUFFLE number of each type of card unchanged");

	//check that cards are in a different order
	asserttrue(memcmp(G.deck[p], G2.deck[p], sizeof(int) * deckCount), "SHUFFLE cards in different order");

	//check that supply hasn't changed
	asserttrue(0 == memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * 27), "SHUFFLE supply unchanged");
	
	
	
	for(i = 0; i < numPlayers; i++){
		if(i != p){
			//check other hands aren't modified
			asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "SHUFFLE other hands unchanged");

			//check other decks aren't modified
			asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "SHUFFLE other decks unchanged");

			//check other discards aren't modified
			asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "SHUFFLE other discards unchanged");

		}
	}

	return 0;
}
