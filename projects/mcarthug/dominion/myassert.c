#include "myassert.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

bool assertEqual_bool(int item1, int item2){
	if(item1 == item2){
		return true;
	}
	else {
		printf("!!!FAIL!!!");
		return false;
	}
}

void assertEqual(int item1, int item2, bool exitIfFail){
	if(item1 == item2){
		printf("---PASS---\n");
	}
	else {
		printf("!!!FAIL!!!\n");
		if (exitIfFail){
			printf("!!!!!!!!!!EXITING!!!!!!!!!!\n");
			exit(1);
		}
	}
}