#include <iostream>

#include "games/GameState.h"

void main() {
	GameState gs;

	ColorEvent* cEvent = new ColorEvent(1);

	gs.eventManager.add(COLOR_EVENT, cEvent);
	gs.eventManager.execute();

	std::cout << "Hello World";
}