/*------------------------------------
 Random unit test for adventurer card
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
#include <math.h>


// signal handling: borrowed from Piazza post 120
void sig_segv_handler(int sig_num){
	
	char* msg = "\n!!!SEGFAULT detected!!!\n";
	write(1, msg, 25);
	exit(0);
}


int checkAdventurer(struct gameState *baseline, int handPos, int player){
	int testPassed = 0;
	struct gameState testGame;
	// stuff for cardEffect()
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	// copy game state to a test case
	memcpy(&testGame, baseline, sizeof(struct gameState));
	
	// activate!
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// count up treasures in deck and discard 
	int expTres = 0; // how many treasure cards to expect in hand
	int deckTres = 0;
	int discardTres = 0;
	for (int i = 0; i < baseline->deckCount[player]; i++){
		if (baseline->deck[player][i] == copper || baseline->deck[player][i] == silver || baseline->deck[player][i] == gold){
			deckTres++;
		}
	}
	if (deckTres < 2){
		// look for more treasure in discard pile 
		for (int i = 0; i < baseline->discardCount[player]; i++){
			if (baseline->discard[player][i] == copper || baseline->discard[player][i] == silver || baseline->discard[player][i] == gold){
				discardTres++;
			}
		}
		if((deckTres + discardTres) < 2){
			expTres = deckTres + discardTres;
		}
		else{
			expTres = 2;
		}
	}
	else{
		expTres = 2;
	}
	
	// compare treasure count in hands 
	int oldTres = 0;
	int newTres = 0;
	for (int i = 0; i < baseline->handCount[player]; i++){
		if(baseline->hand[player][i] == copper){
			oldTres++;
		}
		else if(baseline->hand[player][i] == silver){
			oldTres++;
		}
		else if(baseline->hand[player][i] == gold){
			oldTres++;
		}
	}
	
	for (int i = 0; i < testGame.handCount[player]; i++){
		if(testGame.hand[player][i] == copper){
			newTres++;
		}
		else if(testGame.hand[player][i] == silver){
			newTres++;
		}
		else if(testGame.hand[player][i] == gold){
			newTres++;
		}
	}
	
	// tests
	if (assertEqual_bool(newTres, oldTres + expTres)){
		testPassed++;
	}
	else {
		printf(" Treasure in hand %d, expected %d\n", newTres, oldTres + expTres);
	}
	if (assertEqual_bool(testGame.supplyCount[estate],baseline->supplyCount[estate])){
		testPassed++;	
	}
	else {
		printf(" Estate victory points were changed\n");
	}
	if (assertEqual_bool(testGame.supplyCount[duchy],baseline->supplyCount[duchy])){
		testPassed++;		
	}
	else {
		printf(" Duchy victory points were changed\n");
	}
	if (assertEqual_bool(testGame.supplyCount[province],baseline->supplyCount[province])){
		testPassed++;		
	}
	else {
		printf(" Province victory points were changed\n");
	}
	
	return testPassed;
}

int main(){
	// signal handling: borrowed from Piazza post 120
	// register handlers for SIGSEGV
    struct sigaction sa = {0};
    sa.sa_handler = sig_segv_handler;
	sigfillset(&sa.sa_mask);
	sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);
	
	printf("#############################\n");
	printf("#   CARD RANDOM TESTING     #\n");
	printf("#       Adventurer          #\n");
	printf("#    randomtestcard1.c      #\n");
	printf("#############################\n");
	
	int seed = 1000;
	//set up random number generator
	SelectStream(1);
	PutSeed((long)seed);
	
	int cases = 2000;
	int numPlayers = 4;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int tv[6] = {copper, silver, gold, estate, duchy, province};
	int ktv[16];  // kingdom, treasure, victory cards that can possibly be in a deck   
	for (int i = 0; i < 16; i++){
		if (i < 10){
			ktv[i] = k[i];
		}
		else{
			ktv[i] = tv[i-10];
		}
	}
	
	int totalPassed = 0;  // track how many test passed 
	for (int j = 0; j < cases; j++){
		int curPlayer = floor(Random()*3);  // randomly select player 
		int deckCount, discardCount;  // to be randomized later 
		struct gameState baseline;
		int handPos = floor(Random()*4);  // randomly select hand position 
		
	
		// setup game 
		initializeGame(numPlayers, k, seed, &baseline);
		
		// put adventurer in current players hand 
		baseline.hand[curPlayer][handPos] = adventurer;
		
		// randomize current players deck
		deckCount = floor(Random()*MAX_DECK);
		baseline.deckCount[curPlayer] = deckCount;
		for (int i = 0; i < deckCount; i++){
			int ndx = floor(Random()*16);
			baseline.deck[curPlayer][i] = ktv[ndx];
		}
		// randomize current players discard
		discardCount = floor(Random()*MAX_DECK);
		baseline.discardCount[curPlayer] = discardCount;
		for (int i = 0; i < discardCount; i++){
			int ndx = floor(Random()*16);
			baseline.discard[curPlayer][i] = ktv[ndx];
		}
		
		int passed = checkAdventurer(&baseline, handPos, curPlayer);
		totalPassed = totalPassed + passed;
	}
	
	// report results
	printf("\\\\\\\\\\\\\\RESULTS SUMMARY///////\n");
	printf("Test Cases Run: %d\n", cases);
	if (assertEqual_bool(totalPassed, cases * 4)){
		printf("SUCCESS!!! ALL TESTS PASSED!!!\n");
	}
	else {
		printf("Tests failed %d of %d\n", (cases * 4) - totalPassed, cases * 4);
		printf("See failed tests above\n");
	}
	
	return 0;
}