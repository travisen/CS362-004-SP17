#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "string.h"
#include "stdio.h"

/*
    Name: Michael Ennis
    Date: 30April2017
    Assignment 3
*/

/*
Unit Test Function:
int updateCoins(int player, struct gameState *state, int bonus)

*/


int main()
{
    printf("\n");
    printf("updateCoins Unit Test: \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);
    int currentPlayer = whoseTurn(testGameState);
    int bonus = 0;
    int tempCoins = 0;

    /*current copper on init = 4, testing against that number */
    testGameState->coins = 6;
    updateCoins(currentPlayer, testGameState, bonus);
    tempCoins = testGameState->coins;

    if(tempCoins == 4);
    {
        printf("Init Coins Test Success. \n");
    }

    testGameState->hand[currentPlayer][0] = copper; // 1 total
    testGameState->hand[currentPlayer][1] = copper; // 2 total
    testGameState->hand[currentPlayer][2] = silver; // 4 total
    testGameState->hand[currentPlayer][3] = silver; // 6 total
    testGameState->hand[currentPlayer][4] = gold;   // 9 total
    bonus = 33;


    updateCoins(currentPlayer, testGameState, bonus);
    tempCoins = testGameState->coins;
    if(tempCoins == 42)
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED END \n");
        printf("%d \n", tempCoins);
    }
    return 0;
}
