#include "GameEngine.h"
int main()
{
	GameEngine* g = new GameEngine();
	
	g->gameStartPhase();
	g->startupPhase();
	g->mainGameLoop();

	delete g;
	return 0;
}