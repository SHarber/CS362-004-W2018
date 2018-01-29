/********************************************************************/
/* Author: Sarah Harber												*/					
/* Description: Unit Test for Function isGameOver for dominion.c	*/	
/********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void assert_GameOver(int);
void assert_GameNotOver(int);

int main(int argc, char** argv)
{
	// Initialize a new game
	struct gameState thisGame;	// This game state.
	int seed = 44;				// Seed for Game Initialization
	int numPlayers = 2;			// Set number of Players
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Intialize game state, number of players & starting cards
		initializeGame(numPlayers, k, seed, &thisGame);
	
	printf("*******************************************************************\n");
	printf("                      isGameOver Unit Test                         \n");
	printf("*******************************************************************\n");

	// Test 1: Province Supply Is Empty Game Over
	printf("Test 1: Province Supply Is Empty Game Over.\n");
		// Set Province Supply to Empty
			thisGame.supplyCount[province] = 0;
		// Assert if Test Passes
			assert_GameOver(isGameOver(&thisGame));
			thisGame.supplyCount[province] = 3;
			printf("\n");

	// Test 2: If 3 Supply Piles Are Empty Game Over
	printf("Test 2: If 3 Supply Piles Are Empty Game Over\n");
		// Set 3 Supply Piles to Empty
			thisGame.supplyCount[adventurer] = 0;
			thisGame.supplyCount[gardens] = 0;
			thisGame.supplyCount[embargo] = 0;
		// Assert if Test Passes
			assert_GameOver(isGameOver(&thisGame));
			printf("\n");

	// Test 3: If Only 2 Supply Piles Are Empty Game Is Not Over
	printf("Test 3: If Only 2 Supply Piles Are Empty Game Is Not Over\n");
		// Set 3 Supply Piles to Empty
			thisGame.supplyCount[adventurer] = 1;
			thisGame.supplyCount[gardens] = 0;
			thisGame.supplyCount[embargo] = 0;
		// Assert if Test Passes
			assert_GameNotOver(isGameOver(&thisGame));
			printf("\n");

	// Test 4: If Only 2 Supply Piles Are Empty Game Is Not Over
	printf("Test 4: If Only 2 Supply Piles Are Empty Game Is Not Over\n");
			// Set 3 Supply Piles to Empty
				thisGame.supplyCount[adventurer] = 1;
				thisGame.supplyCount[gardens] = 1;
				thisGame.supplyCount[embargo] = 0;
			// Assert if Test Passes
				assert_GameNotOver(isGameOver(&thisGame));
				printf("\n");

	// Test 5 If Only No Supply Piles Are Empty Game Is Not Over
	printf("Test 5: If Only No Supply Piles Are Empty Game Is Not Over\n");
			// Set 3 Supply Piles to Empty
				thisGame.supplyCount[adventurer] = 1;
				thisGame.supplyCount[gardens] = 1;
				thisGame.supplyCount[embargo] = 1;
			// Assert if Test Passes
				assert_GameNotOver(isGameOver(&thisGame));
				printf("\n");

	// Test 6:  If Providence Supply Is Not Empty Game Is Not Over
	printf("Test 6:  If Providence Supply Is Not Empty Game Is Not Over\n");
		// Set 3 Supply Piles to Empty
			thisGame.supplyCount[adventurer] = 1;
			thisGame.supplyCount[gardens] = 1;
			thisGame.supplyCount[embargo] = 1;
		// Assert if Test Passes
			assert_GameNotOver(isGameOver(&thisGame));
			printf("\n\n");

}

void assert_GameOver(int istrue)
{
	if (istrue == 1)
		printf("TEST PASSED\n");
	else
		printf("TEST FAILED\n");
}

void assert_GameNotOver(int istrue)
{
	if (istrue == 0)
		printf("TEST PASSED\n");
	else
		printf("TEST FAILED\n");
}







