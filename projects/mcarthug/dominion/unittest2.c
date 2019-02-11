/*------------------------------------
Unit test for getCost() function
in dominion.c
-------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "myassert.h"
#include <stdlib.h>


// getCost() returns the cost of the specified card type or -1 if card doesn't exist

/* 
What to test
- Correct cost is returned for each type of card
  - How to test: pass each card into getCost() and check the correct cost is returned 
- If the card does not exist in the game, -1 is returned 
  - How to test: pass an arbitrary number > 26 into getCost() and check that -1 is returned 
*/

bool inArray(int item, int array[], int size){
	for (int i = 0; i < size; i++){
		if (array[i] == item){
			return true;
		}
	}
	return false;
}

int main(){
	printf("#############################\n");
	printf("#   FUNCTION UNIT TESTING   #\n");
	printf("#          getCost()        #\n");
	printf("#         unittest2.c       #\n");
	printf("#############################\n");
	
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
	
	// cost of each card independently looked up on http://wiki.dominionstrategy.com
	int costs0[] = {curse,copper};
	int costs2[] = {estate,embargo};
	int costs3[] = {silver,village,great_hall,steward,ambassador};
	int costs4[] = {feast,gardens,remodel,smithy,baron,cutpurse,salvager,sea_hag,treasure_map};
	int costs5[] = {duchy,council_room,mine,minion,tribute,outpost};
	int costs6[] = {gold,adventurer};
	int costs8[] = {province};
	
	int i, card, cost, gameCost;
	
	printf("-------------------\n");
	printf("Testing card costs\n");
	printf("-------------------\n");
	
	// check the cost of each card 
	for (i = 0; i < sizeof(cards)/sizeof(cards[0]); i++){
		card = cards[i];
		if (inArray(card,costs0, sizeof(costs0)/sizeof(costs0[0]))){
			cost = 0;
		}
		else if (inArray(card, costs2, sizeof(costs2)/sizeof(costs2[0]))){
			cost = 2;
		}
		else if (inArray(card, costs3, sizeof(costs3)/sizeof(costs3[0]))){
			cost = 3;
		}
		else if (inArray(card, costs4, sizeof(costs4)/sizeof(costs4[0]))){
			cost = 4;
		}
		else if (inArray(card, costs5, sizeof(costs5)/sizeof(costs5[0]))){
			cost = 5;
		}
		else if (inArray(card, costs6, sizeof(costs6)/sizeof(costs6[0]))){
			cost = 6;
		}
		else if (inArray(card, costs8, sizeof(costs8)/sizeof(costs8[0]))){
			cost = 8;
		}
		else{
			break;
		}
		gameCost = getCost(card);
		printf("Cost for card %d is %d, expected %d ", card, gameCost, cost);
		assertEqual(gameCost, cost, true);
	}
	
	printf("------------------------------------------------------\n");
	printf("Testing non-existent card does not have a cost\n");
	printf("------------------------------------------------------\n");
	
	
	int notACard = 27; // valid cards < 27
	
	gameCost = getCost(notACard);
	printf("Cost for non-existent card %d is %d, expected -1 ", notACard, gameCost);
	assertEqual(gameCost, -1, true);
	
	printf("ALL TEST PASSED!!!!!\n");
	return 0;
}