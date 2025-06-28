#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Game Object
	Game game;

	while (game.running())
	{
			
		//update
		game.Update();

		//render
		game.Render();

	}

	return 0;
}