#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

/*  Tests playSmithy()
 *  -checks that card is discarded
 *  -checks that three cards are drawn
 *	 -checks that deck has three fewer cards
 *	 -checks that the supply piles are unchanged
 *	 -checks that other players' hands, discards, and decks are unchanged
 *
*/

int main(){
	//initializations
	
	int seed = 1000;
	int i;
	int numPlayers = 2;
	int p = 0; //player number
	int handCount = 5; //number of cards
	
	int hand[MAX_HAND];

	int handPos = 0; //position of card before it is played
	hand[0] = smithy;
	for(i = 1; i < handCount; i++){
		hand[i] = copper;
	}


	//initialize the game state
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	struct gameState G;
	struct gameState G2;
	initializeGame(numPlayers, k, seed, &G);

	G.handCount[p] = handCount;
	G.whoseTurn = p;
	memcpy(G.hand[p], hand, sizeof(int) * handCount);
	
	memcpy(&G2, &G, sizeof(struct gameState)); // copy of game state for comparison


	//call function
	playSmithy(&G, handPos);



	//assert results
	//check card has been discarded
	asserttrue(G.hand[p][handPos] != smithy, "SMITHY discard test");
	
	//check that 3 cards have been drawn
	asserttrue(G.handCount[p] == handCount + 2, "SMITHY +3 cards drawn test");
	
	//check that deck has three fewer cards
	asserttrue(G.deckCount[p] == G2.deckCount[p] - 3, "SMITHY deck -3 cards test");
	
	//check that supply hasn't changed
	asserttrue(0 == memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * 27), "SMITHY supply unchanged");
	
	
	
	for(i = 0; i < numPlayers; i++){
		if(i != p){
			//check other hands aren't modified
			asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "SMITHY other hands unchanged");

			//check other decks aren't modified
			asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "SMITHY other decks unchanged");

			//check other discards aren't modified
			asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "SMITHY other discards unchanged");

		}
	}

	return 0;
}

