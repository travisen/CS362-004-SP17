#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


/* Tests playVillage
 * -checks that 2 actions are added
 * -checks that one card is drawn
 * -checks that the played card is dicarded
 *	-checks that the supply piles are unchanged
 *	-checks that other players' hands, discards, and decks are unchanged
 *
*/



int main(){
	
	//Initializations
	
	int seed = 1000;
	int i;
	int numPlayers = 2;
	int p = 0; // player number
	int handCount = 5; //number of cards in hand

	int hand[MAX_HAND];

	int handPos = 0; //position card is played from
	hand[0] = village;
	for(i = 0; i < handCount; i++){
		hand[i] = copper;
	}

	//initialize game state

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayers, k, seed, &G);

	struct gameState G2;
	memcpy(&G2, &G, sizeof(struct gameState)); // copy of game state for comparison


	G.handCount[p] = handCount;
	G.whoseTurn = p;
	memcpy(G.hand[p], hand, sizeof(int) * handCount);

	int numActions = G.numActions;



	//call function
	playVillage(&G, handPos);



	//assert results
	
	//check +2 actions
	asserttrue(G.numActions == (numActions + 2), "VILLAGE +2 actions test");
	
	//check +1 card 
	asserttrue(G.handCount[p] == handCount, "VILLAGE +1 card drawn test");
	
	//check that card was discarded
	asserttrue(G.hand[p][handPos] != village, "VILLAGE discard test");
	
	//check that supply hasn't changed
	asserttrue(0 == memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * 27), "VILLAGE supply unchanged");

	
	for(i = 0; i < numPlayers; i++){
		if(i != p){
			//check other hands aren't modified
			asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "VILLAGE other hands unchanged");

			//check other decks aren't modified
			asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "VILLAGE other decks unchanged");

			//check other discards aren't modified
			asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "VILLAGE other discards unchanged");

		}
	}

	return 0;
}

