#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


/* Tests playTreasure_map
 * if the hand has only treasure map
 *    -checks that card is not played
 *		-checks that game state does not change
 * if the hand has two treasure maps
 *		-checks that the card is played
 *		-checks that four gold are added to the top of the deck
 *		-checks that the rest of the deck remains unchanged
 *		-checks that gold supply is decreased
 *		-checks that the other supply piles are unchanged
 *		-checks that other players' hands, discards, and decks are unchanged
 *
*/



int main(){
	
	//Initializations
	int seed = 1000;
	int i;
	int r; //holds return value
	int numPlayers = 2;
	int p = 0; //player number
	int handCount = 5; //number of cards
	
	int hand1[MAX_HAND] = {treasure_map, copper, copper, estate, estate};
	int hand2[MAX_HAND] = {treasure_map, treasure_map, copper, copper, estate};
	int fourGold[4] = {gold, gold, gold, gold};
	int handPos = 0; //position of card before it is played


	//initialize game state

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayers, k, seed, &G);

	struct gameState G2;
	memcpy(&G2, &G, sizeof(struct gameState)); // copy of game state for comparison

	G.handCount[p] = handCount;
	G.whoseTurn = p;
	memcpy(G.hand[p], hand1, sizeof(int) * handCount);


	/* -------- TEST 1: only one treasure map in hand --------
	   ------------- should not play card --------------------*/
	r = playTreasure_map(&G, handPos);


	//assert the results

	//check that function returns -1
	asserttrue(r == -1, "TREASURE MAP can't be played test");

	//check that gamestate has not changed
	asserttrue(0 == memcmp(&G, &G2, sizeof(struct gameState)), "TREASURE MAP gamestate unchanged test");


	//reinitialize for next test
	initializeGame(numPlayers, k, seed, &G);
	memcpy(G.hand[p], hand2, sizeof(int) * handCount);
	memcpy(&G, &G2, sizeof(struct gameState));

	int deckCount = G.deckCount[p]; //number of cards in deck before treasure map played 

	//-------------- TEST 2: two treasure maps in hand ----------------
	//----- should trash the cards and add four gold to the deck ------
	r = playTreasure_map(&G, handPos);


	//assert results

	//check that function returned correctly
	asserttrue(r == 1, "TREASURE MAP played test");
	
	//last four cards in deck should be four golds
	asserttrue(0 == memcmp(&G.deck[p][deckCount], fourGold, sizeof(int) * 4), "TREASURE MAP 4 gold added test");
	
	//all of the other cards in the deck should be unchanged
	asserttrue(0 == memcmp(&G.deck[p], G2.deck[p], sizeof(int) * deckCount), "TREASURE MAP rest of deck unchanged test");
	
	//check that gold supply has been decreased
	asserttrue(G.supplyCount[6] == (G2.supplyCount[6] - 4), "TREASURE MAP gold supply -4 test");
	
	//check supply pile counts before gold (<6)
	asserttrue(0 == memcmp(&G.supplyCount[0], &G2.supplyCount[0], sizeof(int) * 6), "TREASURE MAP supply unchanged test part 1");
	
	//check supply pile counts after gold (>6)
	asserttrue(0 == memcmp(&G.supplyCount[7], &G2.supplyCount[7], sizeof(int) * 20), "TREASURE MAP supply unchanged test part 2");
	

	for(i = 0; i < numPlayers; i++){
		if(i != p){
			//check other hands aren't modified
			asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "TREASURE MAP other hands unchanged");

			//check other decks aren't modified
			asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "TREASURE MAP other decks unchanged");

			//check other discards aren't modified
			asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "TREASURE MAP other discards unchanged");

		}
	}

	return 0;
}



