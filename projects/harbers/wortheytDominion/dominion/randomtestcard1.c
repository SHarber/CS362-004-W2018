//******************************************************************************
// Author: Sarah Harber
// Description:  Random test of Smithy card in the dominion game.
//******************************************************************************
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
int MAX_TESTS = 150;
//******************************************************************************
// Randomly test the Smithy card.
// Inputs:  struct gameState *state
//          int currentPlayer
//          int handPos
//******************************************************************************

int main(int argc, char**argv) {
    SelectStream(20);
    PutSeed(3);

    // Set up a game state that Smithy will accept
    //******************************************************************
    struct gameState testGame;      // Test Game state
    struct gameState testGamePost;  // Test Game Post Adventurer state
    int seed;                       // Random Seed
    int n, i;                       // Loop Counters for tests
    int num_players;                // Number of Players
    int player;                     // Current Player
    int failedTests = 0;            // Failed Test Counters
    int passedTests = 0;            // Passed Test Counters
    //******************************************************************
    // Set kingdome cards
    int k[10]={adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    //******************************************************************
    printf("*******************************************************\n");
    printf("Random Testing Smithy Card\n");
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
        // Assign first card as Smithy for handposition for discard
            testGame.deck[player][0] = smithy;
        // Randomly Assign Deck to current player
            for (i = 1; i < testGame.deckCount[player]; i++)
            {
                testGame.deck[player][i] = rand() % treasure_map;
            }

        // Randomly assign discard Count to current players
            for (i = 0; i < testGame.discardCount[player]; i++)
                testGame.discard[player][i] = rand() % treasure_map;
        // Draw 5 cards for player's hand.
            for (i = 0; i < 5; i++)
                drawCard(player, &testGame);
        // Copy Test Game's Game State
            memcpy(&testGamePost, &testGame, sizeof(testGame));
        // Play Smithy Card
            int handPos = 0;
			playSmithy(player, &testGame, handPos);

        // Confirm handCount is two more than prior.
            if ((testGame.handCount[player] + 2) !=  testGamePost.handCount[player])
            {
                printf("ERROR: Test %d Failed due to Number of Cards in Hand\n", n);
				printf("Expected Hand Count: %d \n", (testGame.handCount[player] + 2));
				printf("Actual Hand Count: %d \n", testGamePost.handCount[player]);
                failedTests++;
            }
            else
            {
                passedTests++;
            }

        // Confirm discard pile has one more card in it.
            if ((testGame.discardCount[player] + 1) !=  testGamePost.discardCount[player])
            {
                printf("ERROR: Test %d Failed discard pile did not increment\n", n);
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
                failedTests++;
            }
            else
            {
                passedTests++;
            }

        // Confirm Deck Count Decreases
            if ((testGame.deckCount[player]-3) !=  testGamePost.deckCount[player])
            {
                //printf("ERROR: Test %d Failed due to Number of Cards in Deck\n", n);
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
