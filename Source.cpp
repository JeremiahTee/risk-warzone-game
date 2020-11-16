#include "GameEngine.h"


int main() { //This is the main driver
	GameEngine* g = new GameEngine();
	g->start();
	g->startupPhase();
	delete g;
	return 0;
}