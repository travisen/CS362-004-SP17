#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


/* Tests playAdventurer
 * -checks that 2 cards are drawn
 * -checks that 2 treasure cards are drawn
 * -checks that adventurer card is discarded
 *	-checks that the supply piles are unchanged
 *	-checks that other players' hands, discards, and decks are unchanged
 *
*/



int main(){
	
	//Initializations
	int seed = 1000;
	int i;
	int numPlayers = 2;
	int p = 0; //player number
	int handCount = 5; // number of cards

	int hand[MAX_HAND]; //hand that will be tested

	int handPos = 0; //position of card before it is played
	hand[handPos] = adventurer;
	for(i = 1; i < handCount; i++){
		hand[i] = estate;
	}
	int numTreasures = 0;


	//initialize game state
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	
	struct gameState G;
	initializeGame(numPlayers, k, seed, &G);

	G.handCount[p] = handCount;
	G.whoseTurn = p;
	memcpy(G.hand[p], hand, sizeof(int) * handCount);
	
	struct gameState G2;
	memcpy(&G2, &G, sizeof(struct gameState)); // copy of game state for comparison

	
	//call function
	playAdventurer(&G, handPos);


	//find number of treasures in the hand afterwards
	int newNumTreasures = 0;
	for(i = 0; i < G.handCount[p]; i++){
		if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold){
			newNumTreasures++;
		}
	}


	//assert results
	
	//check that two cards have been drawn
	asserttrue(G.handCount[p] == (handCount + 1), "ADVENTURER +2 cards drawn test");
	
	//check that two treasure cards have been drawn
	asserttrue(newNumTreasures == (numTreasures + 2), "ADVENTURER +2 treasure test");
	
	//check that played card is discarded
	asserttrue(G.hand[p][handPos] != adventurer, "ADVENTURER discard test");
	
	//check that supply hasn't changed
	asserttrue(0 == memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * 27), "ADVENTURER supply unchanged");

	for(i = 0; i < numPlayers; i++){
		if(i != p){
			//check other hands aren't modified
			asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "ADVENTURER other hands unchanged");

			//check other decks aren't modified
			asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "ADVENTURER other decks unchanged");

			//check other discards aren't modified
			asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "ADVENTURER other discards unchanged");

		}
	}
	
	return 0;
}

