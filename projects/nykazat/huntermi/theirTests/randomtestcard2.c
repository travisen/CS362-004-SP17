#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <time.h>
#include <stdlib.h>

/* Random Tester for mine
 *
 * When choice1 or choice2 is not a treasure card
 * 	-checks that the function returns -1
 * When choice1 and choice2 are treasure cards
 * 	-checks that function returns -1 when combination is not valid
 * 		*cost of choice2 > 3 + cost of choice1
 * 		*choice2 supply pile is empty
 *		-otherwise, checks that choice1 is trashed
 *		-checks that choice2 is gained 
 *		-checks that the corresponding supply pile is decreased
 *	Always
 *		-checks that supply piles (other than choice2) are unchanged
 *		-checks that other player's hands, decks, and discards are unchanged
 *
*/


int main(){

	//declarations
	int test;
	int NUM_TESTS = 10000;
	int seed = 1000;

	int playerChecks = 0;
	int notPlayedTests[3] = {0};
	int playedTests = 0;

	int numFails[11] = {0};

	srand(time(NULL));//random number generator

	int i, j, r;

	int numPlayers = 4;
	int p = 0;
	int handPos = 0; //position of card before it is played

	int choice1; //position of card to discard
	int choice2; //supply pile number of card to gain
	int choiceCount[2];
	int newChoiceCount[2];

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

		handCount = (rand() % 49) + 2; //between 2 and 50 cards in the hand
		deckCount = rand() % 51; // between 0 and 50 cards in the deck
		discardCount = rand() % 51; // between 0 and 50 cards in the discard

		for(i = 0; i < handCount; i++){
			//hand[i] = rand() % 4 + province; //had has only province, copper, silver, gold
			hand[i] = rand() % (treasure_map + 1);
			if(hand[i] == mine)
				hand[i] = curse; //no extra mines
		}
		for(i = 0; i < deckCount; i++){
			deck[i] = rand() % (treasure_map + 1);
			if(deck[i] == mine)
				deck[i] = curse; //no extra mines
		}
		for(i = 0; i < discardCount; i++){
			discard[i] = rand() % (treasure_map + 1);
			if(discard[i] == mine)
				discard[i] = curse; // no extra mines
		}

		handPos = rand() % handCount;
		hand[handPos] = mine;

		G.numPlayers = numPlayers;
		G.whoseTurn = p;

		memcpy(G.hand[p], hand, sizeof(int) * handCount);
		memcpy(G.deck[p], deck, sizeof(int) * deckCount);
		memcpy(G.discard[p], discard, sizeof(int) * discardCount);
		G.handCount[p] = handCount;
		G.deckCount[p] = deckCount;
		G.discardCount[p] = discardCount;



		
		choice1 = (rand() % (handCount - 1)) + 1; //position between 1 and handCount - 1
		choice2 = rand() % (treasure_map + 2); //random card between curse and treasure_map+1
		if(choice2 == (treasure_map + 1)){//choice2 out of range
			if(rand() % 2 == 0)
				choice2 = curse - 1;
		}


		G.supplyCount[choice2] = rand() % 2; //supply is empty half the time
	


		memcpy(&G2, &G, sizeof(struct gameState));



		for(j = 0; j < G.handCount[p]; j++){
			if(G.hand[p][j] == G.hand[p][choice1])
				choiceCount[0]++;
			if(G.hand[p][j] == choice2)
				choiceCount[1]++;
		}


		//Call function

		r = playMine(&G, handPos, choice1, choice2);



		for(j = 0; j < G.handCount[p]; j++){
			if(G.hand[p][j] == G.hand[p][choice1])
				newChoiceCount[0]++;
			if(G.hand[p][j] == choice2)
				newChoiceCount[1]++;
		}


		// ------------------------------------------------------------ //
		// ---------------------- count failures ---------------------- //
		// ------------------------------------------------------------ //

		if((hand[choice1] < copper || hand[choice1] > gold) || (choice2 < copper || choice2 > gold)){
			notPlayedTests[0]++;
			if(r != -1)
				numFails[0]++;
		}
		else if(getCost(choice2) > getCost(hand[choice1]) + 3){
			notPlayedTests[1]++;
			if(r != -1)
				numFails[1]++;
		}
		else if(G2.supplyCount[choice2] == 0){
			notPlayedTests[2]++;
			if(r != -1)
				numFails[2]++;
		}
		else{
			//card should be played correctly
			playedTests++;

			if(choiceCount[0] - 1 != newChoiceCount[0]) //1 less of choice1 card type in hand
				numFails[3]++;
			if(choiceCount[1] + 1 != newChoiceCount[1]) // 1 more of choice2 card type in hand
				numFails[4]++;
			if(G.supplyCount[choice2] != G2.supplyCount[choice2] - 1) //1 less of choice2 in supply
				numFails[5]++;
		

			//mine is discarded
			if(G.hand[p][handPos] == mine)
				numFails[6]++;
		}

		//supply is unchanged
		//NEED TO SPLIT IN TWO
		if(0 != memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * choice2))
			numFails[7]++;
		else if(0 != memcmp(&G.supplyCount[choice2+1], &G2.supplyCount[choice2+1], sizeof(int) * (26 - choice2)))
			numFails[7]++;


		//other players' stuff unchanged
		for(i = 0; i < numPlayers; i++){
			if(i != p){
				playerChecks++;
				if(0 != memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND))
					numFails[8]++;
				if(0 != memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK))
					numFails[9]++;
				if(0 != memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK))
					numFails[10]++;
			}
		}



	}
	//END LOOP


	//print summary

	printf("MINE not played (invalid choices) FAILS: %d/%d\n", numFails[0], notPlayedTests[0]);
	printf("MINE not played (costs too much)  FAILS: %d/%d\n", numFails[1], notPlayedTests[1]);
	printf("MINE not played (supply empty)    FAILS: %d/%d\n", numFails[2], notPlayedTests[2]);
	printf("MINE treasure card trashed        FAILS: %d/%d\n", numFails[3], playedTests);
	printf("MINE treasure card gained         FAILS: %d/%d\n", numFails[4], playedTests);
	printf("MINE supply pile decreased        FAILS: %d/%d\n", numFails[5], playedTests);
	printf("MINE mine discarded               FAILS: %d/%d\n", numFails[6], playedTests);
	printf("MINE other supplies unchanged     FAILS: %d/%d\n", numFails[7], NUM_TESTS);
	printf("MINE other hands unchanged        FAILS: %d/%d\n", numFails[8], playerChecks);
	printf("MINE other decks unchanged        FAILS: %d/%d\n", numFails[9], playerChecks);
	printf("MINE other discards unchanged     FAILS: %d/%d\n", numFails[10], playerChecks);

	return 0;
}

