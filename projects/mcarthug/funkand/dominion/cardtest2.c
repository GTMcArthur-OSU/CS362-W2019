/*------------------------------------
 Unit test for adventurer card
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "myassert.h"
#include <signal.h>
#include <unistd.h>

// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)



// Adventurer card action: reveal cards from deck until two treasure cards (copper, silver, gold) are found 
// add treasure cards to deck and discard the other revealed cards.

/*
What to test:
	- that two treasures are found in a deck with two or more treasures 
		- How to test: create a draw pile with two treasures in it, check that two treasures 
		are added to the hand, this will happen when game is initialized 
	- that only one treasure is found in a deck with one treasure in it	
		- How to test: create draw pile with only 1 treasure, check that just one treasure is 
		added to the hand
	- that 0 treasure is found in a deck without any treasure in it 
		- How to test: create a draw pile with 0 treasure, check that no treasure is added to the hand
	- Adventurer is terminal
		- How to test: check that numActions hasn't changed
*/



// signal handling: borrowed from Piazza post 120
void sig_segv_handler(int sig_num){
	
	char* msg = "\n!!!SEGFAULT detected!!!\n";
	write(1, msg, 25);
	exit(0);
}


int main(){
	// signal handling: borrowed from Piazza post 120
	// register handlers for SIGSEGV
    struct sigaction sa = {0};
    sa.sa_handler = sig_segv_handler;
	sigfillset(&sa.sa_mask);
	sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);



	int seed = 1000;
	int numPlayers = 2;
	int curPlayer = 0;
	struct gameState baseline, testGame;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// stuff for cardEffect()
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
	
	printf("#############################\n");
	printf("#     CARD UNIT TESTING     #\n");
	printf("#       Adventurer          #\n");
	printf("#        cardtest2.c        #\n");
	printf("#############################\n");

	// setup game 
	initializeGame(numPlayers, k, seed, &baseline);
	
	// set current player's first card to a adventurer to ensure it is in his hand 
	baseline.hand[curPlayer][handPos] = adventurer;
	
	// copy game state to a test case
	memcpy(&testGame, &baseline, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	printf("Adventurer is terminal ");
	assertEqual(testGame.numActions, baseline.numActions, false);
	
	// Find 2 Treasure Cards 
	// count up treasure cards
	int oldTres = 0;
	int newTres = 0;
	for (int i = 0; i < baseline.handCount[curPlayer]; i++){
		if(baseline.hand[curPlayer][i] == copper){
			oldTres++;
		}
		else if(baseline.hand[curPlayer][i] == silver){
			oldTres++;
		}
		else if(baseline.hand[curPlayer][i] == gold){
			oldTres++;
		}
	}
	
	for (int i = 0; i < testGame.handCount[curPlayer]; i++){
		if(testGame.hand[curPlayer][i] == copper){
			newTres++;
		}
		else if(testGame.hand[curPlayer][i] == silver){
			newTres++;
		}
		else if(testGame.hand[curPlayer][i] == gold){
			newTres++;
		}
	}
	
	printf("Hand started with %d treasure cards, now has %d, expected %d ", oldTres, newTres, oldTres + 2 );
	assertEqual(newTres, oldTres+2, false);
	
	//reset game
	memset(&baseline,0,sizeof(baseline));
		
	// setup game 
	initializeGame(numPlayers, k, seed, &baseline);
	
	// set current player's first card to a adventurer to ensure it is in his hand 
	baseline.hand[curPlayer][handPos] = adventurer;
	
	// reset deck to hold just 1 treasure card 
	for(int i = 0; i < baseline.deckCount[curPlayer]; i++){
		if (i == 0){
			baseline.deck[curPlayer][i] = gold;
		}
		else{
			baseline.deck[curPlayer][i] = smithy;
		}
	}
	
	// copy game state to a test case
	memcpy(&testGame, &baseline, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// Find 1 Treasure Cards 
	// count up treasure cards
	oldTres = 0;
	newTres = 0;
	for (int i = 0; i < baseline.handCount[curPlayer]; i++){
		if(baseline.hand[curPlayer][i] == copper){
			oldTres++;
		}
		else if(baseline.hand[curPlayer][i] == silver){
			oldTres++;
		}
		else if(baseline.hand[curPlayer][i] == gold){
			oldTres++;
		}
	}
	
	for (int i = 0; i < testGame.handCount[curPlayer]; i++){
		if(testGame.hand[curPlayer][i] == copper){
			newTres++;
		}
		else if(testGame.hand[curPlayer][i] == silver){
			newTres++;
		}
		else if(testGame.hand[curPlayer][i] == gold){
			newTres++;
		}
	}
	
	printf("Hand started with %d treasure cards, now has %d, expected %d ",oldTres, newTres, oldTres + 1 );
	assertEqual(newTres, oldTres+1, false);
	
	
	//reset game
	memset(&baseline,0,sizeof(baseline));
		
	// setup game 
	initializeGame(numPlayers, k, seed, &baseline);
	
	// set current player's first card to a adventurer to ensure it is in his hand 
	baseline.hand[curPlayer][handPos] = adventurer;
	
	// reset deck to hold 0 treasure card 
	for(int i = 0; i < baseline.deckCount[curPlayer]; i++){
		baseline.deck[curPlayer][i] = smithy;
	}
	
	// copy game state to a test case
	memcpy(&testGame, &baseline, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// Find 0 Treasure Cards 
	// count up treasure cards
	oldTres = 0;
	newTres = 0;
	for (int i = 0; i < baseline.handCount[curPlayer]; i++){
		if(baseline.hand[curPlayer][i] == copper){
			oldTres++;
		}
		else if(baseline.hand[curPlayer][i] == silver){
			oldTres++;
		}
		else if(baseline.hand[curPlayer][i] == gold){
			oldTres++;
		}
	}
	
	for (int i = 0; i < testGame.handCount[curPlayer]; i++){
		if(testGame.hand[curPlayer][i] == copper){
			newTres++;
		}
		else if(testGame.hand[curPlayer][i] == silver){
			newTres++;
		}
		else if(testGame.hand[curPlayer][i] == gold){
			newTres++;
		}
	}
	
	printf("Hand started with %d treasure cards, now has %d, expected %d ",oldTres, newTres, oldTres);
	assertEqual(newTres, oldTres, false);
	
	printf("No change to Estate victory points ");
	assertEqual(testGame.supplyCount[estate],baseline.supplyCount[estate], false);
	printf("No change to Duchy victory points ");
	assertEqual(testGame.supplyCount[duchy],baseline.supplyCount[duchy], false);
	printf("No change to Province victory points ");
	assertEqual(testGame.supplyCount[province],baseline.supplyCount[province], false);
	
	return 0;
}