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
isGameOver(struct gameState *state)
*/

int main()
{
    printf("\n");
    printf("isGameOver Unit Test: \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);

    int testsPassed = 0;
    int totalTests = 0;
    int testTemp = 0;

    /*Test after Init*/
    testTemp = isGameOver(testGameState);       /*Should be 0*/
    if (testTemp == 1)
    {
        printf("TEST FAILED \n");
        return 0;
    }

    /*Test Province End Game */
    testTemp = 0;
    testGameState->supplyCount[province] = 0;
    testTemp = isGameOver(testGameState);       /*Should be 1*/
    if (testTemp == 0)
    {
        printf("TEST FAILED \n");
        return 0;
    }
    testGameState->supplyCount[province] = 10;  /*Reset Provinces */

    /*Set 1 pile and Test */
    testTemp = 0;
    testGameState->supplyCount[smithy] = 0;
    testTemp = isGameOver(testGameState);       /*Should be 0*/
    if (testTemp == 1)
    {
        printf("TEST FAILED \n");
        return 0;
    }

    /*Set 2nd pile and Test */
    testTemp = 0;
    testGameState->supplyCount[adventurer] = 0;
    testTemp = isGameOver(testGameState);       /*Should be 0*/
    if (testTemp == 1)
    {
        printf("TEST FAILED \n");
        return 0;
    }

    /*Set 3rd pile and Test */
    testTemp = 0;
    testGameState->supplyCount[estate] = 0;
    testTemp = isGameOver(testGameState);       /*Should be 1*/
    if (testTemp == 0)
    {
        printf("TEST FAILED \n");
        return 0;
    }

    /*All Tests passed*/
    printf("TEST SUCCESSFULLY COMPLETED \n");
    return 0;
}
