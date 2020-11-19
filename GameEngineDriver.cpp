#include "GameEngine.h"
int main()
{
	GameEngine g = GameEngine();
	
	g.gameStartPhase();
	g.startupPhase();
	g.mainGameLoop();
}