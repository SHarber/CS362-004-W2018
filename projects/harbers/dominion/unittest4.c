/********************************************************************/
/* Author: Sarah Harber												*/					
/* Description: Unit Test for Function fullDeckCount for dominion.c	*/	
/********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void assert_numCards(int, int);

int main(int argc, char** argv)
{
	// Initialize a new game
	struct gameState thisGame;	// This game state.
	int seed = 44;				// Seed for Game Initialization
	int numPlayers = 4;			// Set number of Players
	int i;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Intialize game state, number of players & starting cards
	initializeGame(numPlayers, k, seed, &thisGame);

	printf("*******************************************************************\n");
	printf("                   fullDeckCount Unit Test                         \n");
	printf("*******************************************************************\n");

	// Test 1: Start of the game there are 3 Estate Cards
	printf("Test 1: Start of the game there are 3 Estate Cards\n");
		assert_numCards(3, fullDeckCount(0, 1, &thisGame));

	// Test 2: If card is not in deck or hand 0 cards exists
	printf("Test 2: If card is not in deck or hand 0 cards exists\n");
		assert_numCards(0, fullDeckCount(0, 7, &thisGame));

	// Test 3: Card in Hand Returns Correct Number Of Cards
	printf("Test 3: Card in Hand Returns Correct Number Of Cards\n");
		// Draw all cards
			for (i = 0; i < 10; i++)
			{
				drawCard(0, &thisGame);
			}
			assert_numCards(3, fullDeckCount(0, 1, &thisGame));

	// Test 4: Cards in Discard Pile Returns Correct Number Of Cards
	printf("Test 4: Cards in Discard Pile Returns Correct Number Of Cards\n");
		// Discard all Cards
			for (i = 9; i > -1; i--)
			{
				discardCard(i, 0, &thisGame, 0);

			}
			assert_numCards(3, fullDeckCount(0, 1, &thisGame));


}

void assert_numCards(int expected, int actual)
{
	if (expected == actual)
		printf("TEST PASSED\n");
	else
		printf("TEST FAILED\n");

}