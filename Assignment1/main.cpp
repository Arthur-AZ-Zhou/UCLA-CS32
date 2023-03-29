	#include "Game.h"
	#include "Game.h"
	#include "Arena.h"
	#include "Arena.h"
	#include "History.h"
	#include "History.h"
	#include "Player.h"
	#include "Player.h"
	#include "Rabbit.h"
	#include "Rabbit.h"
	#include "globals.h"
	#include "globals.h"

int main() {
    //Create a game
    Game g(3, 5, 2);
    // Game g(10, 12, 40);
    g.play(); // Play the game
}