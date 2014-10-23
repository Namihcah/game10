
#include <iostream>

#include "game.h"

using game10_game::Game10;

int main(int argc, char *argv[])
{
	Game10 game;	

	int score = game.start();
	std::cout << "Your Score: " << score << "\n";
}

