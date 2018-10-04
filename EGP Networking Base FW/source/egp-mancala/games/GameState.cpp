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

#include "games/GameState.h"

void GameState::initNetwork() {
	char selection;

	std::cout << "(H)ost or (J)oin server?:\t";
	std::cin >> selection;

	std::cout << "Enter server port:\t";
	std::cin >> mNetworkData.serverPort;

	mpPeer = RakNet::RakPeerInterface::GetInstance();

	if (selection == 'H' || selection == 'h') {
		mNetworkData.isHost = true;
		mNetworkData.maxClients = 2;

		RakNet::SocketDescriptor sd(mNetworkData.serverPort, 0);
		mpPeer->Startup(mNetworkData.maxClients, &sd, 1);
	}
	else {
		RakNet::SocketDescriptor sd;
		mpPeer->Startup(1, &sd, 1);
	}
}

void GameState::handleNetwork() {

}

void GameState::handleUpdate() {
	while (eventManager.getEventListLength() > 0) {
		eventManager.execute();
	}
}