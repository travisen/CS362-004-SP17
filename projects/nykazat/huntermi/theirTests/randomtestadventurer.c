#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>

/* Random Tester for adventurer
 * When there are >= 2 available treasures:
 * 	-checks that exactly 2 cards are drawn
 * 	-checks that 2 treasure cards are drawn
 * When there are < 2 available treasures 
 * 	-checks that exactly 0/1 cards are drawn
 *		-checks that 0/1 treasure cards are drawn
 * Always:
 * -checks that adventurer card is discarded
 *	-checks that the supply piles are unchanged
 *	-checks that other players' hands, discards, and decks are unchanged
 *
 *
 * Counts tests and failures for summary at the end
 * Full output for tests can be viewed by setting VERBOSE to 1
 * NUM_TESTS controls the number of tests
 */


int main(){

	int VERBOSE = 0; /* set to 1 to output the result of each test
							* set to 0 to get a summary at the end
						   */

	//declarations
	int test;
	int NUM_TESTS = 1000;
	int seed = 1000;

	int numFails[9] = {0};
	int normalTests = 0;
	int playerChecks = 0;

	//SelectStream(1);
	//PutSeed(seed);
	srand(time(NULL));//random number generator

	int i;

	int numPlayers = 4;
	int p = 0;
	int handPos = 0; //position of card before it is played

	int numTreasures;
	int newNumTreasures;
	int availableTreasures;

	int hand[MAX_HAND];
	int handCount;
	int deck[MAX_DECK];
	int deckCount;
	int discard[MAX_DECK];
	int discardCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
						smithy, village, baron, great_hall};

	struct gameState G, G2;

	//LOOP!!!!

	for(test = 0; test < NUM_TESTS; test++){

		//initialize the game state
		numPlayers = 2 + rand() % 3; //number between 2 and 4
		p = rand() % numPlayers;

		initializeGame(numPlayers, k, seed, &G);

		handCount = (rand() % 50) + 1; //between 1 and 50 cards in the hand
		deckCount = rand() % 51; // between 0 and 50 cards in the deck
		discardCount = rand() % 51; // between 0 and 50 cards in the discard

		for(i = 0; i < handCount; i++){
			hand[i] = rand() % (treasure_map + 1);
			if(hand[i] == adventurer)
				hand[i] = curse; //no extra adventurers
		}
		for(i = 0; i < deckCount; i++){
			deck[i] = rand() % (treasure_map + 1);
			if(deck[i] == adventurer)
				deck[i] = curse; //no extra adventurers
		}
		for(i = 0; i < discardCount; i++){
			discard[i] = rand() % (treasure_map + 1);
			if(discard[i] == adventurer)
				discard[i] = curse; // no extra adventurers
		}

		handPos = rand() % handCount;
		hand[handPos] = adventurer;

		G.numPlayers = numPlayers;
		G.whoseTurn = p;

		memcpy(G.hand[p], hand, sizeof(int) * handCount);
		memcpy(G.deck[p], deck, sizeof(int) * deckCount);
		memcpy(G.discard[p], discard, sizeof(int) * discardCount);
		G.handCount[p] = handCount;
		G.deckCount[p] = deckCount;
		G.discardCount[p] = discardCount;



		memcpy(&G2, &G, sizeof(struct gameState));

		numTreasures = 0;
		for(i = 0; i < handCount; i++){
			if(hand[i] >= copper && hand[i] <= gold)
				numTreasures++;
		}

		availableTreasures = 0;
		for(i = 0; i < deckCount; i++){
			if(deck[i] >= copper && deck[i] <= gold)
				availableTreasures++;		
		}
		for(i = 0; i < discardCount; i++){
			if(discard[i] >= copper && discard[i] <= gold)
				availableTreasures++;
		}

		//Initializations



		//Call function
		playAdventurer(&G, handPos);

		//assert results

		
		newNumTreasures = 0;
		for(i = 0; i < G.handCount[p]; i++){
			if(G.hand[p][i] >= copper && G.hand[p][i] <= gold)
				newNumTreasures++;
		}

		
		if(availableTreasures >= 2){
			normalTests++;
			if(newNumTreasures != numTreasures + 2)
				numFails[0]++;
			if(G.handCount[p] != handCount + 1)
				numFails[1]++;
		}
		else{
			if(newNumTreasures != numTreasures + availableTreasures)
				numFails[2]++;
			if(G.handCount[p] != handCount + availableTreasures - 1)
				numFails[3]++;
		}

		if(G.hand[p][handPos] == adventurer)
			numFails[4]++;

		if(0 != memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * 27))
			numFails[5]++;

		for(i = 0; i < numPlayers; i++){
			if(i != p){
				playerChecks++;
				if(0 != memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND))
					numFails[6]++;
				if(0 != memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK))
					numFails[7]++;
				if(0 != memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK))
					numFails[8]++;
			}
		}




		if(VERBOSE){

			if(availableTreasures >= 2){
				//check that two treasures have been drawn
				asserttrue(newNumTreasures == (numTreasures + 2), "ADVENTURER +2 treasures");
				//check that exactly two cards have been drawn
				asserttrue(G.handCount[p] == (handCount + 1), "ADVENTURER +2 cards drawn");
			}	
			else{
				//check that all available treasures were drawn
				asserttrue(newNumTreasures == (numTreasures + availableTreasures), "ADVENTURER +0/1 treasures");
				//check that cards drawn is equal to number of avilable treasures
				asserttrue(G.handCount[p] == (handCount + (availableTreasures - 1)), "ADVENTURER +2 cards drawn");
			}

			//check that played card is discarded
			asserttrue(G.hand[p][handPos] != adventurer, "ADVENTURER discard test");

			//chack that supply is unchanged
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
		}//end verbose assertions



	}
	//END LOOP

	//Print summary of failures

	printf("ADVENTURER +2 treasures            FAILS: %d/%d\n", numFails[0], normalTests);
	printf("ADVENTURER +2 cards drawn          FAILS: %d/%d\n", numFails[1], normalTests);
	printf("ADVENTURER +0/1 treasures          FAILS: %d/%d\n", numFails[2], NUM_TESTS - normalTests);
	printf("ADVENTURER +0/1 cards drawn        FAILS: %d/%d\n", numFails[3], NUM_TESTS - normalTests);
	printf("ADVENTURER discard                 FAILS: %d/%d\n", numFails[4], NUM_TESTS);
	printf("ADVENTURER supply unchanged        FAILS: %d/%d\n", numFails[5], NUM_TESTS);
	printf("ADVENTURER other hands unchanged   FAILS: %d/%d\n", numFails[6], playerChecks);
	printf("ADVENTURER other decks unchanged   FAILS: %d/%d\n", numFails[7], playerChecks);
	printf("ADVENTURER other dicards unchanged FAILS: %d/%d\n", numFails[8], playerChecks);

	return 0;
}

