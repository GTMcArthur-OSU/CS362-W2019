CFLAGS= -Wall -fpic -coverage -lm -std=c99 -D_XOPEN_SOURCE

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresults: dominion.o rngs.o randomtestcard1.c randomtestcard2.c myassert.c myassert.h

	echo "----- randomtestcard1.c - RESULTS -----" > randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c myassert.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out	
	echo "------ randomtestcard1.c - COVERAGE -----" >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out

	echo "----- randomtestcard2.c - RESULTS -----" > randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c myassert.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out	
	echo "------ randomtestcard2.c - COVERAGE -----" >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out

	echo "----- randomtestcard3.c - RESULTS -----" > randomtestcard3.out
	gcc -o randomtestcard3 randomtestcard3.c myassert.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard3 >> randomtestcard3.out	
	echo "------ randomtestcard3.c - COVERAGE -----" >> randomtestcard3.out
	gcov -b dominion.c >> randomtestcard3.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
