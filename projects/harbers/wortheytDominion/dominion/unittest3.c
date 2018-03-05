/********************************************************************/
/* Author: Sarah Harber												*/					
/* Description: Unit Test for Function whosTurn for dominion.c		*/	
/********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void assertTurn(int expected, int actual);

int main(int argc, char** argv)
{
	// Initialize a new game
	struct gameState thisGame;	// This game state.
	int seed = 44;				// Seed for Game Initialization
	int numPlayers = 4;			// Set number of Players
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Intialize game state, number of players & starting cards
	initializeGame(numPlayers, k, seed, &thisGame);

	printf("*******************************************************************\n");
	printf("                      whoseTurn Unit Test                          \n");
	printf("*******************************************************************\n");

	// Test 1: Player 1 starts the game.
	printf("Test 1: Player starts the game\n");
		assertTurn(0, whoseTurn(&thisGame));

	// Test 2:  Player 2 is now up.
	printf("Test 1: Player 2's Turn\n");
		// End turn.
		endTurn(&thisGame);
		assertTurn(1, whoseTurn(&thisGame));

	// Test 3: Player 3's Turn
	printf("Test 3: Player 3's Turn\n");
		// End turn.
		endTurn(&thisGame);
		assertTurn(2, whoseTurn(&thisGame));
		
	// Test 4: Player 4's Turn
	printf("Test 4: Player 4's Turn\n");
		// End turn.
		endTurn(&thisGame);
		assertTurn(3, whoseTurn(&thisGame));

	// Test 5: Player 1's Turn
	printf("Test 5: Player 1's Turn\n");
		// End turn.
		endTurn(&thisGame);
		assertTurn(0, whoseTurn(&thisGame));

}

void assertTurn(int expected, int actual)
{
	if (expected == actual)
		printf("TEST PASSED\n");
	else
		printf("TEST FAILED\n");

}