#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>

/* Random Tester for treasure map
 * When there is only one treasure map in the hand:
 * 	-checks that card is not played
 * 	-checks that gamestate is unchanged
 * When there are two or more treasure maps in the hand:
 * 	-checks that exactly 2 treasure map cards are trashed
 * 	-checks that 4 gold are added to the top of the deck
 * 	-checks that the gold supply is decreased by 4
 *		-checks that the other supply piles are unchanged
 *		-checks that other players' hands, discards, and decks are unchanged
 *
 *
*/


int main(){

	//declarations

	int test;
	int NUM_TESTS = 1000;
	int seed = 1000;
	int notPlayedTests = 0;
	int playedTests = 0;


	int numFails[9] = {0};
	int playerChecks = 0;

	//SelectStream(1);
	//PutSeed(seed);
	srand(time(NULL));//random number generator

	int i, j, r;

	int numPlayers = 4;
	int p = 0;
	int handPos = 0; //position of card before it is played

	int numTreasureMaps; //number of treasure maps in the hand
	int newNumTreasureMaps;
	int fourgold[4] = {gold, gold, gold, gold};
	int goldSupply;

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

		//Initializations
		numPlayers = 2 + rand() % 3; //number between 2 and 4
		p = rand() % numPlayers;

		initializeGame(numPlayers, k, seed, &G);

		handCount = (rand() % 50) + 1; //between 1 and 50 cards in the hand
		deckCount = rand() % 51; // between 0 and 50 cards in the deck
		discardCount = rand() % 51; // between 0 and 50 cards in the discard


		for(i = 0; i < handCount; i++){
			hand[i] = rand() % (treasure_map + 1);
			if(hand[i] == treasure_map)
				hand[i] = curse; //no extra treasure maps
		}
		for(i = 0; i < deckCount; i++){
			deck[i] = rand() % (treasure_map + 1);
			if(deck[i] == treasure_map)
				deck[i] = curse; //no extra treasure maps
		}
		for(i = 0; i < discardCount; i++){
			discard[i] = rand() % (treasure_map + 1);
			if(discard[i] == treasure_map)
				discard[i] = curse; // no extra treasure maps
		}

		numTreasureMaps = (rand() % 3) + 1; // between 1 and 3
		if(handCount < numTreasureMaps)
			numTreasureMaps = handCount; // prevent numTreasureMaps > handCount
		
		i = 1;
		while(i < numTreasureMaps){
			//add treasure maps to hand
			//equal to numTreasureMaps (1, 2, or 3)
			j = rand() % handCount;
			if(hand[j] != treasure_map){
				hand[j] = treasure_map;
				i++;
			}
		}

		goldSupply = rand() % 8; //gold supply between 0 and 7
		G.supplyCount[gold] = goldSupply;

		handPos = rand() % handCount;
		hand[handPos] = treasure_map;

		G.numPlayers = numPlayers;
		G.whoseTurn = p;

		memcpy(G.hand[p], hand, sizeof(int) * handCount);
		memcpy(G.deck[p], deck, sizeof(int) * deckCount);
		memcpy(G.discard[p], discard, sizeof(int) * discardCount);
		G.handCount[p] = handCount;
		G.deckCount[p] = deckCount;
		G.discardCount[p] = discardCount;



		memcpy(&G2, &G, sizeof(struct gameState));
		


		//Call function
		r = playTreasure_map(&G, handPos);


		/* -------------------------------------------------
		 * ----------------- count failures ---------------- 
		 * ------------------------------------------------- */
	
		newNumTreasureMaps = 0;
		for(i = 0; i < G.handCount[p]; i++){
			if(G.hand[p][i] == treasure_map)
				newNumTreasureMaps++;
		}


		if(numTreasureMaps == 1){
			//Card should not have been played
			notPlayedTests++;

			//function returns -1
			if(-1 != r)
				numFails[0]++;

			//gamestate unchanged
			if(0 != memcmp(&G, &G2, sizeof(struct gameState)))
				numFails[1]++;
		}
		else{
			//card should have been played
			playedTests++;

			//2 treasure maps trashed
			if(newNumTreasureMaps != numTreasureMaps - 2){
				numFails[2]++;
				//printf("numtreasure: %d\nnewnum: %d\n", numTreasureMaps, newNumTreasureMaps);
				//printf("last card in hand:%d\n",G2.hand[p][G2.handCount[p]-1]);
			}

			if(goldSupply >= 4){
				//four gold in supply
				
				//four gold added to deck
				if(0 != memcmp(&G.deck[p][deckCount], fourgold, sizeof(int) * 4)){
					numFails[3]++;
					//printf("%d,%d,%d,%d\n", G.deck[p][deckCount],G.deck[p][deckCount+1],G.deck[p][deckCount+2],G.deck[p][deckCount+3]);
				}

				//gold removed from supply
				if(G.supplyCount[gold] != (goldSupply - 4)){
					numFails[4]++;
					//printf("gold supply before: %d\nafter: %d\n", goldSupply, G.supplyCount[gold]);
				}
			}
			else{
				//less than four gold in supply

				//all gold from supply added to deck
				if(0 != memcmp(&G.deck[p][deckCount], fourgold, sizeof(int) * goldSupply)){
					numFails[3]++;
					//printf("%d,%d,%d,%d\n", G.deck[p][deckCount],G.deck[p][deckCount+1],G.deck[p][deckCount+2],G.deck[p][deckCount+3]);
			}
				//gold removed from supply
				if(G.supplyCount[gold] != 0){
					numFails[4]++;
					//printf("gold supply before: %d\nafter: %d\n", goldSupply, G.supplyCount[gold]);
				}
			}
			
			//supply piles unchanged before (<6) and after (>6) gold
			if(0 != memcmp(&G.supplyCount[0], &G2.supplyCount[0], sizeof(int) * 6)
					|| 0 != memcmp(&G.supplyCount[7], &G2.supplyCount[7], sizeof(int) * 20))
				numFails[5]++;


			//player tests
			for(i = 0; i < numPlayers; i++){
				if(i != p){
					playerChecks++;
					
					//hand unchanged
					if(0 != memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND))
						numFails[6]++;
					
					//deck unchanged
					if(0 != memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK))
						numFails[7]++;
					
					//discard unchanged
					if(0 != memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK))
						numFails[8]++;
				}
			}
		}
		//end tests


	}
	//END LOOP


	//Print summary of failures

	printf("TREASURE MAP not played returns -1           FAILS: %d/%d\n", numFails[0], notPlayedTests);
	printf("TREASURE MAP not played game state unchanged FAILS: %d/%d\n", numFails[1], notPlayedTests);
	printf("TREASURE MAP 2 treasure maps trashed         FAILS: %d/%d\n", numFails[2], playedTests);
	printf("TREASURE MAP 4 gold drawn                    FAILS: %d/%d\n", numFails[3], playedTests);
	printf("TREASURE MAP gold supply decreased           FAILS: %d/%d\n", numFails[4], playedTests);
	printf("TREASURE MAP supply unchanged                FAILS: %d/%d\n", numFails[5], playedTests);
	printf("TREASURE MAP other hands unchanged           FAILS: %d/%d\n", numFails[6], playerChecks);
	printf("TREASURE MAP other decks unchanged           FAILS: %d/%d\n", numFails[7], playerChecks);
	printf("TREASURE MAP other dicards unchanged         FAILS: %d/%d\n", numFails[8], playerChecks);


	return 0;
}

