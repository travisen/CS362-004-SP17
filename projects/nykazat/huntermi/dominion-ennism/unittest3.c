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
int fullDeckCount(int player, int card, struct gameState *state)

*/

int main()
{
    printf("\n");
    printf("fullDeckCount Unit Test: \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);

    int currentPlayer = whoseTurn(testGameState);

    int card = curse;

    testGameState->deckCount[currentPlayer] = 3;
    testGameState->handCount[currentPlayer] = 3;
    testGameState->discardCount[currentPlayer] = 3;

    testGameState->deck[currentPlayer][0] = card;
    testGameState->deck[currentPlayer][1] = minion;
    testGameState->deck[currentPlayer][2] = curse;

    testGameState->hand[currentPlayer][0] = curse;
    testGameState->hand[currentPlayer][1] = card;
    testGameState->hand[currentPlayer][2] = embargo;

    testGameState->discard[currentPlayer][0] = cutpurse;
    testGameState->discard[currentPlayer][1] = card;
    testGameState->discard[currentPlayer][2] = card;

    int count = fullDeckCount(currentPlayer, card, testGameState);

    if( count == 6)
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED \n");
    }
    return 0;
}
