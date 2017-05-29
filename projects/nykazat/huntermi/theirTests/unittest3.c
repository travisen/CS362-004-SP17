#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* Tests buyCard
 * TEST 1: not enough money for the buy
 * 	-checks that buy does not happen (returns -1)
 * 	-checks that game state is unchanged
 *
 * TEST 2: enough money, but card not in supply
 * 	-checks that buy does not happen (returns -1)
 * 	-checks that game state is unchanged
 *
 * TEST 3: enogh money card in supply
 *		-checks that buy does happen (returns 0)
 *		-checks that card is added to discard
 *		-checks that money is decreased
 *		-checks that number of buys is decreased
 *		-checks that the supply pile is decreased
 *		-checks that the other supply piles are unchanged
 *		-checks that other players' hands, discards, and decks are unchanged
 *
*/




int main(){

	//initialize the gamestate

	int seed = 1000;
	int i;
	int r;
	int numPlayers = 2;
	int p = 0; //player number
	int supplyPos; //card being bought
	

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	struct gameState G, G2;
	initializeGame(numPlayers, k, seed, &G);


	// ---------------- TEST 1: not enough money -------------------
	// buy should not happen
	
	G.coins = 0;
	G.numBuys = 1;
	supplyPos = 6; //gold (cost 6)
	memcpy(&G2, &G, sizeof(struct gameState));
	
	r = buyCard(supplyPos, &G);

	//assert the results
	asserttrue(r == -1,  "BUY CARD TEST 1 returns -1");
	asserttrue(0 == memcmp(&G, &G2, sizeof(struct gameState)), "BUY CARD TEST 1 game state unchanged");




	// ---------------- TEST 2: no cards in supply -------------------
	// buy should not happen

	G.coins = 6;
	G.numBuys = 1;
	supplyPos = 6; //gold (cost 6)
	G.supplyCount[6] = 0;
	memcpy(&G2, &G, sizeof(struct gameState));

	r = buyCard(supplyPos, &G);

	//assert the results

	asserttrue(r == -1,  "BUY CARD TEST 2 returns -1");
	asserttrue(0 == memcmp(&G, &G2, sizeof(struct gameState)), "BUY CARD TEST 2 game state unchanged");




	// ---------------- TEST 3: enough money, card in supply -------------------
	// buy should excute


	G.coins = 6;
	G.numBuys = 1;
	supplyPos = 6; //gold (cost 6)
	G.supplyCount[6] = 1; //1 gold in supply
	memcpy(&G2, &G, sizeof(struct gameState));

	r = buyCard(supplyPos, &G);


	//assert results
	
	//check that card is in discard
	asserttrue(G.discard[p][G.discardCount[p]-1] == gold, "BUY CARD card in discard");

	//check that money has decreased
	asserttrue(G.coins == 0, "BUY CARD money drecreased");

	//check that number of buys has decreased
	asserttrue(G.numBuys == 0, "BUY CARD number of buys decreased");

	
	//check that gold supply has been decreased (1 -> 0)
	asserttrue(G.supplyCount[6] == 0, "BUY CARD bought card supply -1");
	
	//check supply pile counts before gold (<6)
	asserttrue(0 == memcmp(&G.supplyCount[0], &G2.supplyCount[0], sizeof(int) * 6), "BUY CARD supply unchanged part 1");
	
	//check supply pile counts after gold (>6)
	asserttrue(0 == memcmp(&G.supplyCount[7], &G2.supplyCount[7], sizeof(int) * 20), "BUY CARD supply unchanged part 2");
	
	
	for(i = 0; i < numPlayers; i++){
		if(i != p){
			//check other hands aren't modified
			asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "BUY CARD TEST 3 other hands unchanged");

			//check other decks aren't modified
			asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "BUY CARD TEST 3 other decks unchanged");

			//check other discards aren't modified
			asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "BUY CARD TEST 3 other discards unchanged");

		}
	}

	return 0;
}
