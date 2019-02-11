/*------------------------------------
Unit test for whoseTurn() function
in dominion.c
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "myassert.h"
#include <stdlib.h>

// whoseTurn() returns the integer from gameState that represents the player whose turn it is now

/* 
What to test
- correct player index is returned
	- How to test: set gameState.whoseTurn to lowest and highest player index and check correct
		integer is returned.
*/

int main(){
	
	printf("#############################\n");
	printf("#   FUNCTION UNIT TESTING   #\n");
	printf("#        whoseTurn()        #\n");
	printf("#        unittest3.c        #\n");
	printf("#############################\n");

	
	int lowestIndex = 0;
	int highestIndex = MAX_PLAYERS - 1;  // subtract one because player index is 0 based
	int player;
	struct gameState game;
	
	game.whoseTurn = lowestIndex;
	player = whoseTurn(&game);
	printf("whoseTurn(lowestIndex) = %d, expected %d ", player, lowestIndex);
	assertEqual(player, lowestIndex, true);
	
	game.whoseTurn = highestIndex;
	player = whoseTurn(&game);
	printf("whoseTurn(highestIndex) = %d, expected %d ", player, highestIndex);
	assertEqual(player, highestIndex, true);
	
	printf("ALL TEST PASSED!!!!!\n");
	return 0;
}