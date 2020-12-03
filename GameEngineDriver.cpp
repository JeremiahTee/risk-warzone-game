////=========================================
////      Authors                ID          
////	
////	David Kim           | 27151543 
////	Aryamann Mehra      | 40127106 
////	Jeremiah Tiongson   | 40055477 
////	Maxime Johnson      | 40081684 
////	Marjolaine Roy      | 40098364 
////=========================================

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