/*------------------------------------
Unit test for fullDeckCount() function
in dominion.c
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "myassert.h"
#include <stdlib.h>




// fullDeckCount() tallies how may a specific player has of a specific card
// in their deck (hand + discard pile + draw pile)

/*
What to test
- each part of deck is counted
  - How to test: put the card in each deck and check that the correct count is returned
- correct player's deck is counted
  - How to test: game has multiple players in it, each with the card in their hand.
    Correct count is returned 
- correct card is counted
  - How to test: deck contains multiple cards, correct count for just the specified card is returned
- if the specified card is not found in deck then nothing is counted
  - How to test: deck contains cards but not the specified one, 0 is returned 
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
	int numberPlayers = 2;
	int totalCardTypes = sizeof(cards)/sizeof(int);  // how many different card types there are
	int result = 3; // expected result from fullDeckCount() 
	int deckPart[totalCardTypes];
	for (int i = 0; i < totalCardTypes; i++){
		deckPart[i] = cards[i];
	}
	
	printf("#############################\n");
	printf("#   FUNCTION UNIT TESTING   #\n");
	printf("#      fullDeckCount()      #\n");
	printf("#         unittest1.c       #\n");
	printf("#############################\n");
	
	// fill out player's decks
	for (int i = 0; i < numberPlayers; i++){
		game.handCount[i] = totalCardTypes;
		game.discardCount[i] = totalCardTypes;
		game.deckCount[i] = totalCardTypes;
		
		memcpy(game.hand[i], deckPart, sizeof(int) * totalCardTypes);
		memcpy(game.discard[i], deckPart, sizeof(int) * totalCardTypes);
		memcpy(game.deck[i], deckPart, sizeof(int) * totalCardTypes);
	}
	
	// test that each card can be found in each part of each players deck
	for (int i = 0; i < numberPlayers; i++){
		printf("----------------------------\n");
		printf("Counting cards for Player %d\n", i);
		printf("----------------------------\n");
		for (int j = 0; j < totalCardTypes; j++){
			int count = fullDeckCount(i, j, &game);
			printf("For card %d, fullDeckCount = %d, expected = %d ", j, count, result);
			assertEqual(count, result, true);
		}
	}
	
	// replace copper with outpost
	for (int i = 0; i < numberPlayers; i++){
		for (int j = 0; j < totalCardTypes; j++){
			if (game.hand[i][j] == copper){
				game.hand[i][j] = outpost;
			}
			if (game.discard[i][j] == copper){
				game.discard[i][j] = outpost;
			}
			if (game.deck[i][j] == copper){
				game.deck[i][j] = outpost;
			}
		}
	}
	
	// counting coppers should find nothing
	for (int i = 0; i < numberPlayers; i++){
		printf("---------------------------------------------------\n");
		printf("Counting coppers in deck without them for Player %d\n", i);
		printf("---------------------------------------------------\n");
		int count = fullDeckCount(i, copper, &game);
		printf("For copper, fullDeckCount = %d, expected = %d ", count, 0);
		assertEqual(count, 0, true);  // shouldn't be able to find any coppers 
	}
	
	printf("ALL TEST PASSED!!!!!\n");
	return 0;
}
