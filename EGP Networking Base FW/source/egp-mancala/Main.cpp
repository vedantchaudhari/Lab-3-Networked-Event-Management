#include <iostream>

#include <stdio.h>
#include <string.h>

#include "games/GameState.h"

int main(void) {
	GameState gs;

	ColorEvent* cEvent = new ColorEvent(1);
	DamageEvent* dEvent = new DamageEvent(2);

	gs.initNetwork();

	gs.eventManager.add(COLOR_EVENT, cEvent);
	gs.eventManager.add(DAMAGE_EVENT, dEvent);

	while (1) {
		gs.handleNetwork();
		gs.handleUpdate();
	}

	std::cout << "Hello World";
}