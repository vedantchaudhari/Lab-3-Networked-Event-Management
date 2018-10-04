// Certificate of Authenticity
//
// EGP-405-01 Networking for Online Games
// Lab 3
// 8-27-2018
//
// Vedant Chaudhari, 1532077
//
// We certify that this work is entirely our own.The assessor of this project may reproduce this project 
// and provide copies to other academic staff, and/or communicate a copy of this project to a plagiarism 
// - checking service, which may retain a copy of the project on its database.

#include <iostream>

#include <stdio.h>
#include <string.h>

#include "games/GameState.h"
#include "util/Thread.h"

int handleNetworking(GameState* pGS) {
	while (1) {
		pGS->handleNetwork();
	}

	return 0;
}

int main(void) {
	GameState gs;

	ColorEvent* cEvent = new ColorEvent(1);
	DamageEvent* dEvent = new DamageEvent(2);
	HealEvent* hEvent = new HealEvent(33);

	gs.initNetwork();

	gs.eventManager.add(COLOR_EVENT, cEvent);
	gs.eventManager.add(DAMAGE_EVENT, dEvent);
	gs.eventManager.add(HEAL_EVENT, hEvent);

	egpThread networkingThread[1] = { 0 };
	egpThreadCreate(networkingThread, (egpThreadFunc)handleNetworking, &gs);

	while (gs.exit == false) {
		gs.handleInput();
		gs.handleUpdate();
	}

	egpThreadTerminate(networkingThread);
}