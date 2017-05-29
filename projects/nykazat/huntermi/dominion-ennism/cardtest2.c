#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "string.h"
#include "stdio.h"

#define MAX_HAND 500

/*
    Name: Michael Ennis
    Date: 30April2017
    Assignment 3
*/

/*
Card Tested: Adventurer
Card Type : Action Card
Card Cost : $6
Card Action: Reveal cards from your deck until you reveal 2 treasure cards.
    Put those cards into your hand and discard the other revealed cards.
*/

int main()
{
    printf("\n");
    printf("Adventurer Card Test \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);

    int currentPlayer = whoseTurn(testGameState);
    int copperHave = 0;     /* Current amount of copper cards */
    int silverHave = 0;     /* Current amount of silver cards */
    int goldHave =0;        /* Current amount of gold cards */
    int sumShouldHave = 0;                              /*Holds # of treasure cards expected */
    int cardsShouldHave = 0;
    int temphand[MAX_HAND];

    int j = 0;

    for(j = 0; j < testGameState->handCount[currentPlayer]; j++)
    {
        if(testGameState->hand[currentPlayer][j] == copper)
            copperHave++;
        else if(testGameState->hand[currentPlayer][j] == silver)
            silverHave++;
        else if(testGameState->hand[currentPlayer][j] == gold)
            goldHave++;
    }

    printf("Before card played you have: \n");
    printf("Copper: ");
    printf("%d  \n", copperHave);
    printf("Silver: ");
    printf("%d  \n", silverHave);
    printf("Gold: ");
    printf("%d  \n", goldHave);

    sumShouldHave = copperHave + silverHave + goldHave +2;
    cardsShouldHave = testGameState->handCount[currentPlayer]+2;

    /*Play adventurer Card */
    adventurer_Card(0, currentPlayer, 0, temphand, testGameState);

    int copperHave2 = 0;     /* Current amount of copper cards */
    int silverHave2 = 0;     /* Current amount of silver cards */
    int goldHave2 =0;        /* Current amount of gold cards */
    int sumHave = 0;
    int cardsHave = 0;

    for(j = 0; j < testGameState->handCount[currentPlayer]; j++)
    {
        if(testGameState->hand[currentPlayer][j] == copper)
            copperHave2++;
        else if(testGameState->hand[currentPlayer][j] == silver)
            silverHave2++;
        else if(testGameState->hand[currentPlayer][j] == gold)
            goldHave2++;
    }

    sumHave = copperHave2 + silverHave2 + goldHave2;
    cardsHave = testGameState->handCount[currentPlayer];

    printf("After card played you have: \n");
    printf("Copper: ");
    printf("%d  \n", copperHave2);
    printf("Silver: ");
    printf("%d  \n", silverHave2);
    printf("Gold: ");
    printf("%d  \n", goldHave2);


    if((sumShouldHave == sumHave) && (cardsShouldHave == cardsHave))
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED \n");
        if(sumShouldHave != sumHave)
            printf("Incorrect number of treasure cards \n");
        else if(cardsShouldHave != cardsHave)
            printf("Incorrect number of cards \n");
    }
    return 0;
}
