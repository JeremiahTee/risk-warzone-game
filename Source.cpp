#include "GameEngine.h"
#include "MapLoader.h"

//int main() { //This is the main driver
//	GameEngine* g = new GameEngine();
//
//	g->gameStartPhase();
//	g->startupPhase();
//	g->mainGameLoop();
//
//	delete g;
//	return 0;
//}

int main() { //This is the main driver
	GameEngine* g = new GameEngine();

	g->gameStartPhase();
	g->startupPhase();
	g->mainGameLoop();

	delete g;
	return 0;
}