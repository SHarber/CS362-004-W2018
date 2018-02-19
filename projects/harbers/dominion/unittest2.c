/********************************************************************/
/* Author: Sarah Harber												*/
/* Description: Unit Test for Function scoreFor for dominion.c	*/
/********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void assertScore(int, int);

int main(int argc, char** argv)
{
	// Initialize a new game
	struct gameState thisGame;	// This game state.
	int seed = 44;				// Seed for Game Initialization
	int numPlayers = 2;			// Set number of Players
	int i = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	// Intialize game state, number of players & starting cards
	initializeGame(numPlayers, k, seed, &thisGame);

	printf("*******************************************************************\n");
	printf("                      scoreFor Unit Test                         \n");
	printf("*******************************************************************\n\n");
	printf("Print Player 1's Initial Deck to Confirm Score Should be 3\n");
	for (i = 0; i < 10; i++)
	{
		printf("Card %d: %d\n", i, thisGame.deck[0][i]);
	}
	
	printf("Test 1: Score at Beginning of the Game is 3\n");
		// Score for Player 1 Should be 3
			assertScore(scoreFor(0, &thisGame), 3);

	// Test 2: Curse Added to Player's Deck Decreases Score by 1.
	printf("Test 2: Curse Added to Player's Deck Decreases Score by 1\n");
		// Add curse to player 1's deck.
			thisGame.deck[0][11] = curse;
		// Score for Player 1 Should be 2.
			assertScore(scoreFor(0, &thisGame), 2);
	
	// Test 3: Adding an Estate Should Increase Score By 1.
	printf("Test 3: Adding an Estate Increases Score By 1\n");
		// Add curse to player 1's deck.
			thisGame.deck[0][12] = estate;
		// Score for Player 1 Should be 3.
			assertScore(scoreFor(0, &thisGame), 3);

	// Test 4: Adding a Duchy Increases Score by 3
	printf("Test 4: Adding A Duchy Increases Score By 3\n");
		// Add Duchy to Player 1's deck.
			thisGame.deck[0][13] = duchy;
		// Score for Player 1 Should be 6.
			assertScore(scoreFor(0, &thisGame), 6);

	// Test 5: Adding a Province Increases Score by 6
	printf("Test 5: Adding a Province Increases Score by 6\n");
		// Add Province to Player 1's deck.
			thisGame.deck[0][14] = province;
		// Score for Player 1 Should be 12.
			assertScore(scoreFor(0, &thisGame), 12);

	// Test 6: A Garden Card adds A Victory Point For Every 10 Cards In Player's Deck
	printf("Test 6: A Garden Card adds A Victory Point For Every 10 Cards In Player's Deck\n");
		// Add Garden to Player 1's deck.
			thisGame.deck[0][15] = gardens;
		// Score for Player 1 Should be 13.
			assertScore(scoreFor(0, &thisGame), 13);

	// Test 7: Great Hall Adds 1 Point To Score
	printf("Test 7: Great Hall Adds 1 Point To Score\n");
		// Add Great Hall to Player 1's deck.
			thisGame.deck[0][16] = great_hall;
		// Score for Player 1 Should be 14.
			assertScore(scoreFor(0, &thisGame), 14);

	// Test 8: Player Draws 5 Cards From Hand, Score is Unchanged
	printf("Test 8: Player Draws 5 Cards From Hand, Score is Unchanged\n");
		for (i = 0; i < 5; i++)
		{
			drawCard(0, &thisGame);
		}
		assertScore(scoreFor(0, &thisGame), 14);

	// Test 9: All Player's Cards moved to Discard Pile, Score is the Same.
	printf("Test 9: All Player's Cards moved to Discard Pile, Score is the Same\n");
		// Move All Cards to Discard Pile.
			for(i = 0; i < 12; i++)
			{
				drawCard(0, &thisGame);
				discardCard(0, 0, &thisGame, 0);
			}
		// Confirm Score is the same (14)
			assertScore(scoreFor(0, &thisGame), 14);

}


void assertScore(int expected, int actual)
{
	if (expected == actual)
		printf("TEST PASSED\n");
	else
		printf("TEST FAILED\n");
}

