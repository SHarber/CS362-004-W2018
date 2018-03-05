//******************************************************************************
// Author: Sarah Harber
// Description:  Random test of Adventurer card in teh dominion game.
//******************************************************************************
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
int MAX_TESTS = 50;
//******************************************************************************
// Randomly test the Adventurer card.
// Inputs:  struct gameState *state
//          int currentPlayer
//          int temphand[]
//          int z
//          int drawntreasure
//          int cardDrawn
//******************************************************************************
int main(int argc, char**argv) {
    SelectStream(20);
    PutSeed(3);

    // Set up a game state that Adventurer will accept
    //******************************************************************
    struct gameState testGame;      // Test Game state
    struct gameState testGamePost;  // Test Game Post Adventurer state
    int seed;                       // Random Seed
    int n, i;                       // Loop Counters for tests
    int num_players;                // Number of Players
    int player;                     // Current Player
    int temphand[200];                // Temporary hand
    int drawntreasure = 0;          // Initialize Drawn Treasure to 0.
    int cardDrawn = -1;             // Initialize cards Drawn to -1
    int failedTests = 0;            // Failed Test Counters
    int passedTests = 0;            // Passed Test Counters
    //******************************************************************
    // Set kingdome cards
    int k[10]={adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    //******************************************************************
    printf("*******************************************************\n");
    printf("Random Testing Adventurer Card\n");
    printf("*******************************************************\n");
    //******************************************************************
    for (n = 0; n < MAX_TESTS; n++)
    {
        // Randomly assign number of players
        // Make sure atleast 2 players
            num_players = (rand() % 3) + 2;
        // Get Random seed
            seed = rand();
        // Initialzie testGame
            initializeGame(num_players, k, seed, &testGame);

        // Get current player who will play the Adventurer card
            player = rand() % num_players;
        // Set turn to player selected
            testGame.whoseTurn = player;
        // Randomly assign Deck count.
            testGame.deckCount[player] = floor(Random() * MAX_DECK);
        // Randomly assign Discard Counters
            testGame.discardCount[player] = floor(Random() * MAX_DECK);
        // Randomly assign hand Counters
            testGame.discardCount[player] = floor(Random() * MAX_HAND);
        // Randomly Assign Deck to current player
            for (i = 0; i < testGame.deckCount[player]; i++)
                testGame.deck[player][i] = rand() % treasure_map;
        // Randomly assign discard Count to current players
            for (i = 0; i < testGame.discardCount[player]; i++)
                testGame.discard[player][i] = rand() % treasure_map;
        // Draw 5 cards for player's hand.
            for (i = 0; i < 5; i++)
                drawCard(player, &testGame);
        // Copy Test Game's Game State
            memcpy(&testGamePost, &testGame, sizeof(testGame));
        // Play Adventurer Card
            int z = 0;
            playAdventurer(player, &testGamePost);

        // Get # of Treasures player's hand before hand.
            int numTreasuresPre = 0;
            for (i = 0; i < 5; i++)
                if(testGame.hand[player][i] == copper ||
                    testGame.hand[player][i] == silver ||
                    testGame.hand[player][i] == gold)
                    numTreasuresPre++;

        // Get # of Treasures after playing Adventuer.
            int numTreasuresPost = 0;
            for (i = 0; i < testGamePost.handCount[player]; i++)
                if(testGamePost.hand[player][i] == copper ||
                    testGamePost.hand[player][i] == silver ||
                    testGamePost.hand[player][i] == gold )
                    numTreasuresPost++;
           // printf("%d - %d \n", numTreasuresPre, numTreasuresPost);

        // Confirm Treasure count is the same.
            if(numTreasuresPre != numTreasuresPost)
            {
                //printf("ERROR: Test %d Failed due to Number of Treasures in Hand\n", n);
                failedTests++;
            }
            else{
                passedTests++;
            }
        // Confirm handCount is the same
            if ((testGame.handCount[player] + 2) !=  testGamePost.handCount[player])
            {
                printf("ERROR: Test %d Failed due to Number of Cards in Hand\n", n);
                failedTests++;
            }
            else
            {
                passedTests++;
            }
        // Confirm number of actions did not increase.
            if ((testGame.numActions-1) != testGamePost.numActions)
            {
                printf("ERROR: Test %d Failed number of actions did not decrease\n", n);
				printf("Number Of Actions Prior: %d \n", testGame.numActions);
				printf("Number Of Actions Post: %d \n", testGamePost.numActions);
                failedTests++;
            }
            else
            {
                passedTests++;
            }
        // Confirm Deck count decreases by one.
            if ((testGame.deckCount[player]-1) !=  testGamePost.deckCount[player])
            {
                printf("ERROR: Test %d Failed due to Number of Cards in Deck\n", n);
                failedTests++;
            }
            else
            {
                passedTests++;
            }


    }
    //******************************************************************
        printf("*******************************************************\n");
        printf("Number of Failed Tests: %d\n", failedTests);
        printf("Number of Passed Tests: %d\n", passedTests);
        printf("*******************************************************\n");

return 0;

}
