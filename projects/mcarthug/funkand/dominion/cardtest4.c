/*------------------------------------
 Unit test for Great Hall card
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "myassert.h"

// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)



// Great Hall card action: +1 card, +1 Action


/* What to test:
	- 1 card added to hand from deck
		- How to test: one new card shows up in hand, deck count goes down by 1 
	- Great Hall card is discarded
		- How to test: hand size didn't increase (+1 from action, -1 from discard)
	- Great Hall results in 1 additional actions
		- How to test: check that numActions has gone up by 1 
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
	
	// set current player's first card to a smithy to ensure it is in his hand 
	baseline.hand[curPlayer][handPos] = great_hall;
	
	printf("#############################\n");
	printf("#     CARD UNIT TESTING     #\n");
	printf("#         Great Hall        #\n");
	printf("#        cardtest4.c        #\n");
	printf("#############################\n");

	// copy game state to a test case
	memcpy(&testGame, &baseline, sizeof(struct gameState));
	
	cardEffect(great_hall, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	printf("Hand size does not increase ");
	assertEqual(testGame.handCount[curPlayer], baseline.handCount[curPlayer], false);
	
	printf("Deck size decreased by 1 ");
	assertEqual(testGame.deckCount[curPlayer], baseline.deckCount[curPlayer] - 1, false);
	
	printf("Discard size increased by 1 ");
	assertEqual(testGame.discardCount[curPlayer], baseline.discardCount[curPlayer] + 1, false);
	
	printf("Great Hall adds 1 action ");
	assertEqual(testGame.numActions, baseline.numActions + 1, false);
	
	// count for each type of card from hand before and after playing great hall
	int oldHand[treasure_map+1];
	int newHand[treasure_map+1];
	memset(oldHand, 0, sizeof(oldHand));  // initialize everything to 0
	memset(newHand, 0, sizeof(newHand)); // initialize everything to 0
	
	// read baseline hand 
	for (int i = 0; i < baseline.handCount[curPlayer]; i++){
		int card = baseline.hand[curPlayer][i];
		oldHand[card] = oldHand[card] + 1;
	}
	// remove discarded great hall from baseline hand 
	oldHand[great_hall] = oldHand[great_hall] - 1;
	
	// read hand after playing great hall
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