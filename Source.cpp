#include "GameEngine.h"


int main() { //This is the main driver
	GameEngine* g = new GameEngine();

	g->startupPhase();

	delete g;
	return 0;
}