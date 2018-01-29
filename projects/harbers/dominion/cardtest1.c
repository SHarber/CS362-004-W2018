/********************************************************************/
/* Author: Sarah Harber												*/					
/* Description: Smithy Card Test for dominion.c              		*/	
/********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void assertTurn(int expected, int actual);
const int debug = 0;

int main(int argc, char** argv)
{
	// Initialize a new game
	struct gameState thisGame;	// This game state.
	struct gameState testGame;	// Test Game
	int seed = 44;				// Seed for Game Initialization
	int numPlayers = 4;			// Set number of Players
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Intialize game state, number of players & starting cards
	initializeGame(numPlayers, k, seed, &thisGame);

	printf("*******************************************************************\n");
	printf("                         Smithy Card Test                          \n");
	printf("*******************************************************************\n");

	// Copy Game State
		memcpy(&testGame, &thisGame, sizeof(struct gameState));

	// Confirm Hand Position is 0.
		if(debug == 1)
			printf("Smithy Hand Position: %d", thisGame.deck[0][0]);

	// Play Smithy
		cardEffect(smithy, 0, 0, 0, &thisGame, 0, 0);

	// Test 1: Smithy Card Moved to Discard Pile
		printf("Test 1: Smithy Card Moved to Discard Pile\n");

		// Get Discard Pile's Current Count
			printf("Discard Pile Count Before:	%d\n", testGame.discardCount[0]);
			printf("Discard Pile Count After:	%d\n", thisGame.discardCount[0]);
			if( testGame.discardCount[0] < thisGame.discardCount[0])
				printf("TEST PASSED \n");
			else
				printf("TEST FAILED \n");

	// Test 2: Hand Count Increases by 2
		printf("Test 2: Hand Count Increases by 2\n");
			printf("Hand Cout Before:	%d\n", testGame.handCount[0]);
			printf("Hand Count After:	%d\n", thisGame.handCount[0]);
			if( testGame.handCount[0] == (thisGame.handCount[0]+2))
				printf("TEST PASSED \n");
			else
				printf("TEST FAILED \n");

	// Test 3: Number of Actions does Not Change
		printf("Test 3: Number of Actions is decreased by one\n");
			printf("Number Of Actions Before:	%d\n", testGame.numActions);
			printf("Number Of Actions After:	%d\n", thisGame.numActions);
			if( testGame.numActions == (thisGame.numActions + 1))
				printf("TEST PASSED \n");
			else
				printf("TEST FAILED \n");

	// Test 4: Number of Buys does Not Change
		printf("Test 4: Number of Buys does Not Change\n");
			printf("Number Of Buys Before:	%d\n", testGame.numBuys);
			printf("Number Of Buys After:	%d\n", thisGame.numBuys);
			if( testGame.numBuys == thisGame.numBuys)
				printf("TEST PASSED \n");
			else
				printf("TEST FAILED \n");

}