CFLAGS = -Wall -fpic -coverage -lm
GCOVFLAGS = -b
UNITTESTS = unittest1 unittest2 unittest3 unittest4
CARDTESTS = cardtest1 cardtest2 cardtest3 cardtest4
RANDOMTESTS = randomtestcard1 randomtestcard2 randomtestadventurer

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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


unittestresults.out: $(UNITTESTS) $(CARDTESTS)



unittest1: dominion.c rngs.c unittest1.c
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out

	
unittest2: dominion.c rngs.c unittest2.c
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out

	
unittest3: dominion.c rngs.c unittest3.c
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out

	
unittest4: dominion.c rngs.c unittest4.c
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out


cardtest1: dominion.c rngs.c cardtest1.c	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c cardtest1.c rngs.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out
	

cardtest2: dominion.c rngs.c cardtest2.c	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c cardtest2.c rngs.c $(CFLAGS)
	cardtest2 >>unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out
	

cardtest3: dominion.c rngs.c cardtest3.c	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c cardtest3.c rngs.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out
	

cardtest4: dominion.c rngs.c cardtest4.c	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c cardtest4.c rngs.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out

temp: dominion.c rngs.c temp.c	
	echo "temp.c:" >> unittestresults.out
	gcc -o temp dominion.c temp.c rngs.c $(CFLAGS)
	temp >> unittestresults.out
	gcov $(GCOVFLAGS) dominion.c >> unittestresults.out


randomtests: $(RANDOMTESTS)


randomtestcard1: dominion.c rngs.c randomtestcard1.c
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 dominion.c randomtestcard1.c rngs.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov $(GCOVFLAGS) dominion.c >> randomtestcard1.out


randomtestcard2: dominion.c rngs.c randomtestcard2.c
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 dominion.c randomtestcard2.c rngs.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov $(GCOVFLAGS) dominion.c >> randomtestcard3.out


randomtestadventurer: dominion.c rngs.c randomtestadventurer.c
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer dominion.c randomtestadventurer.c rngs.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov $(GCOVFLAGS) dominion.c >> randomtestadventurer.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out
	rm -f cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer
