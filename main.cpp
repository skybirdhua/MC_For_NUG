#include <iostream>
#include <stdlib.h>
#include<time.h>
#include <math.h>
#include <fstream>
#include <stdio.h>
using namespace std;
#include "initialization.h"
#include "net.h"
#include "agent.h"
#include "game.h" 
#include "agents.h"

int main()
{
	buildNeighbor4(n);
	initialAgent();
	for (int repeat = 0; repeat < REPEAT; repeat++) {
		srand(time(0));
		initialStrategy();
		for (int iter = 0; iter < ITER; iter++) {
			cout << repeat<<","<< iter << endl;
			renewReputation(iter);
			renewWeight_random();
			renewUtility();
			renewStrategy();
		}
	}
}