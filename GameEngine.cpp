#include "GameEngine.h"

#include <ctime>
#include <process.h>

using std::vector;

//Map initialization
Map Game::map = Map();
//Vector to hold turns
vector<Player> Game::turns = {};

//Game::Game(int playerCount, std::string& map)
//{
//	srand((unsigned)time(NULL) * _getpid());
//	totalPlayers = playerCount;
//	setObservers();	
//}


void GameEngine::gameStartPhase() {
	cout << "Initializing game engine..." << endl;

	string fileName = queryDirectory("maps");
	cout << "Loading " + fileName + " from file..." << endl;
	createMap("maps\\"+fileName);

	cout << "Checking map validity..." << endl;
	if (map->validate()) {
		cout << "Map is valid!" << endl;
	}
	else {
		cout << "Map is invalid, terminating..." << endl;
		validExecution = false;
	}

	if (validExecution) {
		cout << "Creating players...";
		int playerCount = queryPlayerCount();
		cout << "Creating players..." << endl;
		players = createPlayers(playerCount);

		deck = new Deck(10, 10, 10, 10, 10, 10);

		//Enable/Disable Observers HERE, ask JT when it is go time.
	}
	cout << "\n";
}

vector<Player>& Game::getPlayerTurns()
{
	
}

void Game::setArmies()
{
	
}

void Game::setMap()
{
	
}

void Game::setObservers()
{
	
}

void Game::startupPhase()
{
	
}