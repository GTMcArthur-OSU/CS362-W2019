/*------------------------------------
 Random unit test for great hall card
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

int checkGreatHall(struct gameState *baseline, int handPos, int player){
	int testPassed = 0;
	struct gameState testGame;
	// stuff for cardEffect()
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	
	// copy game state to a test case
	memcpy(&testGame, baseline, sizeof(struct gameState));
	
	// activate!
	cardEffect(great_hall, choice1, choice2, choice3, &testGame, handPos, &bonus);
	
	// update baseline to reflect what should have happened
	drawCard(player, baseline);
	baseline->numActions++;
	discardCard(handPos, player, baseline, 0);
	
	// tests
	if (assertEqual_bool(testGame.handCount[player], baseline->handCount[player])){
		testPassed++;
	}
	else {
		printf(" Hand size was not increased\n");
		memcpy(&testGame.handCount[player], &baseline->handCount[player], sizeof(int));
	}
	
	if (assertEqual_bool(testGame.deckCount[player], baseline->deckCount[player])){
		testPassed++;
	}
	else {
		printf(" Deck size was not decreased by 1\n");
		memcpy(&testGame.deckCount[player], &baseline->deckCount[player], sizeof(int));
	}
	
	if (assertEqual_bool(testGame.discardCount[player], baseline->discardCount[player])){
		testPassed++;
	}
	else {
		printf(" Discard size was not increased by 1\n");
		memcpy(&testGame.discardCount[player], &baseline->discardCount[player], sizeof(int));
	}
	
	if (assertEqual_bool(testGame.numActions, baseline->numActions)){
		testPassed++;
	}
	else {
		printf(" Great Hall did not add 1 action\n");
		memcpy(&testGame.numActions, &baseline->numActions, sizeof(int));
	}
	// test that everything else is the same
	if (assertEqual_bool(memcmp(&testGame, baseline, sizeof(struct gameState)),0)){
		testPassed++;
	}
	else {
		printf(" Error in gameState not caught by other tests\n");
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
	printf("#       Great Hall          #\n");
	printf("#    randomtestcard2.c      #\n");
	printf("#############################\n");

	int seed = 1000;
	//set up random number generator
	SelectStream(1);
	PutSeed((long)seed);
	
	int cases = 2000;
	int numPlayers = 4;
	
	int k[10] = {great_hall, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
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
		int deckCount; // randomized later 
		struct gameState baseline;
		int handPos = floor(Random()*4);  // randomly select hand position 
		
		// setup game 
		initializeGame(numPlayers, k, seed, &baseline);
		
		// put great hall in current players hand 
		baseline.hand[curPlayer][handPos] = great_hall;
				
		// randomize current players deck
		deckCount = floor(Random()*MAX_DECK);
		// ensure that there is always a card to draw, avoid shuffle
		if (deckCount < 1){
			deckCount += 1;
		}
		baseline.deckCount[curPlayer] = deckCount;
		for (int i = 0; i < deckCount; i++){
			int ndx = floor(Random()*16);
			baseline.deck[curPlayer][i] = ktv[ndx];
		}
		
		int passed = checkGreatHall(&baseline, handPos, curPlayer);
		totalPassed = totalPassed + passed;		
	}
	
	// report results
	printf("\\\\\\\\\\\\\\RESULTS SUMMARY///////\n");
	printf("Test Cases Run: %d\n", cases);
	if (assertEqual_bool(totalPassed, cases * 5)){
		printf("SUCCESS!!! ALL TESTS PASSED!!!\n");
	}
	else {
		printf("Tests failed %d of %d\n", (cases * 5) - totalPassed, cases * 5);
		printf("See failed tests above\n");
	}

	return 0;
}