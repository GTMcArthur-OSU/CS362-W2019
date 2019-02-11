/*------------------------------------
Unit test for isGameOver() function
in dominion.c
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "myassert.h"
#include <stdlib.h>

// isGameOver() checks for the province supply pile being depleted OR three other supply piles
// being depleted.  The game ends when one of those conditions is reached

/*
What to test
- Game does not end when all supply card piles are populated
	- How to test: fill up gameState.supplyCount for each card, check that 0 is returned
- Game does not end when < 3 piles are depleted 
	- HOw to test: test just one and two piles depleted, check that 0 is returned 
- Province pile is empty
	- How to test: only province of gameState.supplyCount is empty, check that 1 is returned
- Each card, except province, triggers the end of the game when it's pile is empty along with
  that of 2 other cards
	- How to test: loop over each card, setting its and two other's gameState.supplyCount to 0
	  check that 1 is returned.
- All supply card piles, except province are depleted
	- How to test: set all cards' supply to 0, except province, check that 1 is returned. 
*/

int main(){
	
	int cards[] = {curse,
    estate,
    duchy,
    province,
    copper,
    silver,
    gold,
    adventurer,
    /* If no/only 1 treasure found, stop when full deck seen */
    council_room,
    feast, /* choice1 is supply # of card gained) */
    gardens,
    mine, /* choice1 is hand# of money to trash, choice2 is supply# of
	     money to put in hand */
    remodel, /* choice1 is hand# of card to remodel, choice2 is supply# */
    smithy,
    village,
    baron, /* choice1: boolean for discard of estate */
    /* Discard is always of first (lowest index) estate */
    great_hall,
    minion, /* choice1:  1 = +2 coin, 2 = redraw */
    steward, /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
    tribute,
    ambassador, /* choice1 = hand#, choice2 = number to return to supply */
    cutpurse,
    embargo, /* choice1 = supply# */
    outpost,
    salvager, /* choice1 = hand# to trash */
    sea_hag,
    treasure_map};
	
	struct gameState game;
	int status;
	int totalCardTypes = sizeof(cards)/sizeof(int);  // how many different card types there are
	int supply[totalCardTypes];
	
	printf("#############################\n");
	printf("#   FUNCTION UNIT TESTING   #\n");
	printf("#        isGameOver()       #\n");
	printf("#         unittest4.c       #\n");
	printf("#############################\n");
	
	// fill up supply
	for (int i = 0; i < totalCardTypes; i++){
		supply[i] = 10;
	}
	
	// initialize game supply piles
	memcpy(game.supplyCount, supply, sizeof(int) * totalCardTypes);
	
	
	printf("--------------------------------\n");
	printf("Testing 1 depleted supply pile  \n");
	printf("--------------------------------\n");
	status = isGameOver(&game);
	printf("Game is NOT over with 0 depleted supply piles ");
	assertEqual(status, 0, false);
	// loop over all cards 
	for (int i = 0; i < totalCardTypes; i++){
		if (i == province){
			printf("Province not tested here\n");
		}
		else {
			game.supplyCount[i - 1] = 10; // reset previous depleted pile 
			game.supplyCount[i] = 0;
			printf("Game is NOT over with 1 depleted supply pile for card %d ", i);
			status = isGameOver(&game);
			assertEqual(status, 0, false);
		}
	}
	
	// re-initialize game supply piles
	memcpy(game.supplyCount, supply, sizeof(int) * totalCardTypes);
	
	printf("--------------------------------\n");
	printf("Testing 2 depleted supply pile  \n");
	printf("--------------------------------\n");
	// loop over all cards 
	for (int i = 0; i < totalCardTypes; i++){
		if (i == province){
			printf("Province not tested here\n");
		}
		else if (i == 0){
			game.supplyCount[0] = 0;
			game.supplyCount[1] = 0;
			status = isGameOver(&game);
			printf("Game is NOT over with 2 depleted supply piles for cards 0 & 1 ");
			assertEqual(status, 0, false);
			i++; // skip card 1, test would be redundant 
		}
		else {
			game.supplyCount[i - 1] = 10; // reset previous depleted pile 
			game.supplyCount[i] = 0;
			printf("Game is NOT over with 2 depleted supply piles for cards 0 & %d ", i);
			assertEqual(status, 0, false);
		}
	}
	
	// re-initialize game supply piles
	memcpy(game.supplyCount, supply, sizeof(int) * totalCardTypes);	
	// deplete province pile
	game.supplyCount[province] = 0;
	
	printf("------------------------------\n");
	printf("Testing depleted province pile\n");
	printf("------------------------------\n");
	status = isGameOver(&game);
	printf("Testing that game should be over ");
	assertEqual(status, 1, true);
	
	// re-initialize game supply piles
	memcpy(game.supplyCount, supply, sizeof(int) * totalCardTypes);
	printf("-------------------------------\n");
	printf("Testing 3 depleted supply piles\n");
	printf("-------------------------------\n");
	// loop over all cards 
	for (int i = 0; i < totalCardTypes; i++){
		if (i == province){
			printf("Province not tested here\n");
		}
		else if (i == 0){
			game.supplyCount[0] = 0;
			game.supplyCount[1] = 0;
			game.supplyCount[2] = 0;
			status = isGameOver(&game);
			printf("Game is over with 3 depleted supply piles for cards 0, 1, 2 ");
			assertEqual(status, 1, false);
			
			// reset card supply 
			game.supplyCount[2] = 10;
			i = i + 2; // skip cards 1 & 2, test would be redundant 
		}
		else {
			game.supplyCount[i - 1] = 10; // reset previous depleted pile 
			game.supplyCount[i] = 0;
			status = isGameOver(&game);
			printf("Game is over with 3 depleted supply piles for cards 0, 1, %d ", i);
			assertEqual(status, 1, false);
		}
	}
	
	// empty supply except for province 
	for (int i = 0; i < totalCardTypes; i++){
		if (i == province){
			supply[i] = 10;
		}
		else {
			supply[i] = 0;
		}
	}
	// re-initialize game supply piles
	memcpy(game.supplyCount, supply, sizeof(int) * totalCardTypes);	
	printf("------------------------------------------\n");
	printf("Testing all piles depleted except province\n");
	printf("------------------------------------------\n");
	status = isGameOver(&game);
	printf("Testing that game should be over ");
	assertEqual(status, 1, true);
	
	
	return 0;
}