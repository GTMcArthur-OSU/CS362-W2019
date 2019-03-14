/*------------------------------------
 Unit test for village card
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "myassert.h"

// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)



// Village card action: +1 card, +2 Action


/* What to test:
	- 1 card added to hand from deck
		- How to test: one new card shows up in hand, deck count goes down by 1 
	- Village card is discarded
		- How to test: hand size didn't increase (+1 from action, -1 from discard)
	- Village results in 2 additional actions
		- How to test: check that numActions has gone up by 2 
*/


int main(){
	int seed = 1000;
	int numPlayers = 2;
	int curPlayer = 0;
	struct gameState baseline, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// stuff for cardEffect()
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
	
	// setup game 
	initializeGame(numPlayers, k, seed, &baseline);
	
	// set current player's first card to a village to ensure it is in his hand 
	baseline.hand[curPlayer][handPos] = village;
	
	printf("#############################\n");
	printf("#     CARD UNIT TESTING     #\n");
	printf("#         Village            #\n");
	printf("#        cardtest3.c        #\n");
	printf("#############################\n");

	// copy game state to a test case
	memcpy(&testGame, &baseline, sizeof(struct gameState));
	
	cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	printf("Hand size does not increase ");
	assertEqual(testGame.handCount[curPlayer], baseline.handCount[curPlayer], false);
	
	printf("Deck size decreased by 1 ");
	assertEqual(testGame.deckCount[curPlayer], baseline.deckCount[curPlayer] - 1, false);
	
	printf("Discard size increased by 1 ");
	assertEqual(testGame.discardCount[curPlayer], baseline.discardCount[curPlayer] + 1, false);
	
	printf("Village adds 2 actions ");
	assertEqual(testGame.numActions, baseline.numActions + 2, false);
	
	// count for each type of card from hand before and after playing village
	int oldHand[treasure_map+1];
	int newHand[treasure_map+1];
	memset(oldHand, 0, sizeof(oldHand));  // initialize everything to 0
	memset(newHand, 0, sizeof(newHand)); // initialize everything to 0
	
	// read baseline hand 
	for (int i = 0; i < baseline.handCount[curPlayer]; i++){
		int card = baseline.hand[curPlayer][i];
		oldHand[card] = oldHand[card] + 1;
	}
	// remove discarded village from baseline hand 
	oldHand[village] = oldHand[village] - 1;
	
	// read hand after playing village
	for (int i = 0; i < testGame.handCount[curPlayer]; i++){
		int card = testGame.hand[curPlayer][i];
		newHand[card] = newHand[card] + 1;
	}
	
	// Compare old and new hands to count up the new cards 
	int newCards = 0;
	for (int i = 0; i <= treasure_map; i++){
		newCards = newCards + (newHand[i] - oldHand[i]);
	}
	
	printf("1 new card added to hand ");
	assertEqual(newCards, 1, false);
	
	printf("No change to Estate victory points ");
	assertEqual(testGame.supplyCount[estate],baseline.supplyCount[estate], false);
	printf("No change to Duchy victory points ");
	assertEqual(testGame.supplyCount[duchy],baseline.supplyCount[duchy], false);
	printf("No change to Province victory points ");
	assertEqual(testGame.supplyCount[province],baseline.supplyCount[province], false);
	
	return 0;
}