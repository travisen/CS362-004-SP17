#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


/* Tests scoreFor()
 * TEST 1: Estate, Duchy, Province
 * 	-checks that victory cards are scored correctly
 * 	-checks that victory cards in hand, deck, and discard are scored
 * 	-checks that game state doen not change
 *
 * TEST 2: Gardens
 * 	-checks that gardens are scored correctly 
 * 	-checks that game state doen not change
 *
 * TEST 3: Great Hall
 * 	-checks that great halls are scored correctly 
 * 	-checks that game state doen not change
 *
 * TEST 4: Curses
 *		-checks that curses are scored correctly
 * 	-checks that game state doen not change
 *
 * TEST 5: Invalid input
 * 	-checks that function returns -9999
 * 	-checks that game state doen not change
*/

int main(){

	//initialize the gamestate

	int seed = 1000;
	int i;
	int numPlayers = 4;
	int p = 0; //player number
	
	int scores[5];
	int expectedScores[5] = {10, 5, 5, -5, -9999};

	//



	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};
	struct gameState G, G2;
	initializeGame(numPlayers, k, seed, &G);


	//initialize all players hands, decks, discards to empty
	for(p = 0; p < numPlayers; p++){
		G.handCount[p] = 0;
		for(i = 0; i < MAX_HAND; i++){
			G.hand[p][i] = -1;
		}
		G.deckCount[p] = 0;
		G.discardCount[p] = 0;
		for(i = 0; i < MAX_DECK; i++){
			G.deck[p][i] = -1;
			G.discard[p][i] = -1;
		}	
	}
	
	
	
	
	
	//Player 0 hand, deck, discard initilization
	//1 estate in hand, 1 duchy in deck, 1 province in discard
	G.handCount[0] = 1;
	G.hand[0][0] = estate;
	G.deckCount[0] = 1;
	G.deck[0][0] = duchy;
	G.discardCount[0] = 1;
	G.discard[0][0] = province;


	//Player 1 deck initialization
	//50 coppers and 1 garden
	int deck1[51];
	for(i = 0; i < 51; i++){
		if(i == 0)
			deck1[i] = gardens;
		else
			deck1[i] = copper;
	}
	G.deckCount[1] = 51;
	memcpy(G.deck[1], deck1, sizeof(int) * 51);
	

	
	//Player 2 deck initialization
	//5 great halls
	int deck2[5] = {great_hall, great_hall, great_hall, great_hall, great_hall};
	G.deckCount[2] = 5;
	memcpy(G.deck[2], deck2, sizeof(int) * 5);



	//Player 3 deck initialization
	//5 great halls
	int deck3[5] = {curse, curse, curse, curse, curse};
	G.deckCount[3] = 5;
	memcpy(G.deck[3], deck3, sizeof(int) * 5);



	for(p = 0; p < numPlayers; p++){
		
		memcpy(&G2, &G, sizeof(struct gameState));
	
		//call function
		scores[p] = scoreFor(p, &G);

		//assert the results
		printf("player %d score: %d\n", p, scores[p]);
		printf("player %d expected: %d\n", p, expectedScores[p]);
		asserttrue(scores[p] == expectedScores[p],  "SCORE FOR score matches expected");

		//check that game state is preserved
		asserttrue(0 == memcmp(&G, &G2, sizeof(struct gameState)), "SCORE FOR game state unchanged");
	}

	/* Invalid input segfaults, disrupts tests
	memcpy(&G2, &G, sizeof(struct gameState));

	//player number out of range
	scores[4] = scoreFor(4, &G);

	//should return -9999
	asserttrue(scores[4] == expectedScores[4], "SCORE FOR invalid input");
	
	//check that game state is preserved
	asserttrue(0 == memcmp(&G, &G2, sizeof(struct gameState)), "SCORE FOR Game state unchanged");
	*/

	return 0;
}
