#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


/* Tests endTurn
 * -checks that number of buys, actions and coins are reset
 * -checks that whose turn changes
 * -checks that a new hand (5 cards) is drawn
 * -checks that supply counts are unchanged
 * -checks that other players' hands, decks and discards are unchanged
 *
 */

int main(){

	//initialize the gamestate

	int seed = 1000;
	int i;
	int numPlayers = 4;
	int p = 0; //player number
	int nextPlayer;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};
	struct gameState G, G2;

	initializeGame(numPlayers, k, seed, &G);

	//tests the function for each player
	for(p = 0; p < numPlayers; p++){


		nextPlayer = p + 1;
		if(nextPlayer == numPlayers)
			nextPlayer = 0;


		G.numBuys = -1;
		G.numActions = -1;
		G.coins = -1;
		G.whoseTurn = p;


		memcpy(&G2, &G, sizeof(struct gameState));


		//call the function
		printf("ending player %d's turn\n", p);
		endTurn(&G);


		//count coins in nextplayers hand
		int coins = 0;
		for(i = 0; i < G.handCount[nextPlayer]; i++){
			if(G.hand[nextPlayer][i] == copper)
				coins++;
			if(G.hand[nextPlayer][i] == copper)
				coins += 2;
			if(G.hand[nextPlayer][i] == copper)
				coins += 3;
		}


		//assert the results

		//check that number of buys is reset
		asserttrue(G.numBuys == 1, "END TURN number of buys reset to 1");

		//check that number of actions is reset
		asserttrue(G.numActions == 1, "END TURN number of actions reset to 1");

		//check that coins reset?
		asserttrue(G.coins != coins, "END TURN coins reset");

		//check that whose turn has changed
		asserttrue(G.whoseTurn == nextPlayer, "END TURN whose turn incremented");


		//NOTE: check that player p has no cards, handcount is 0

		//check that a new hand is drawn
		asserttrue(G.handCount[nextPlayer] == 5, "END TURN next player's hand has 5 cards");
		asserttrue(memcmp(G.hand[nextPlayer], G2.hand[nextPlayer], sizeof(int) * 5), "END TURN next player has new hand drawn");


		//check that supply hasn't changed
		asserttrue(0 == memcmp(G.supplyCount, G2.supplyCount, sizeof(int) * 27), "END TURN supply unchanged");


		//check hands, decks, and discards other than player and nextPlayer
		for(i = 0; i < numPlayers; i++){
			if(i != p && i != nextPlayer){
				printf("player %d:\n", i);

				//check other hands aren't modified
				asserttrue(0 == memcmp(G.hand[i], G2.hand[i], sizeof(int) * MAX_HAND), "END TURN other hands unchanged");

				//check other decks aren't modified
				asserttrue(0 == memcmp(G.deck[i], G2.deck[i], sizeof(int) * MAX_DECK), "END TURN other decks unchanged");

				//check other discards aren't modified
				asserttrue(0 == memcmp(G.discard[i], G2.discard[i], sizeof(int) * MAX_DECK), "END TURN other discards unchanged");

			}
		}
	}
	//end loop

	return 0;
}
