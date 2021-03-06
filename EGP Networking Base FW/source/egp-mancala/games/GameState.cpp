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

GameState::GameState() {
	mpPeer = RakNet::RakPeerInterface::GetInstance();
}

GameState::~GameState() {
	RakNet::RakPeerInterface::DestroyInstance(mpPeer);
}

void GameState::initNetwork() {
	char selection;

	std::cout << "(H)ost or (J)oin server?:\t";
	std::cin >> selection;

	std::cout << "Enter server port:\t";
	std::cin >> mNetworkData.serverPort;

	if (selection == 'H' || selection == 'h') {
		mNetworkData.isHost = true;
		mNetworkData.maxClients = 2;
		
		RakNet::SocketDescriptor sd(mNetworkData.serverPort, 0);
		mpPeer->Startup(mNetworkData.maxClients, &sd, 1);
		mpPeer->SetMaximumIncomingConnections(mNetworkData.maxClients);

	}
	else {
		mNetworkData.isHost = false;

		RakNet::SocketDescriptor sd;
		mpPeer->Startup(1, &sd, 1);
		mpPeer->Connect("127.0.0.1", mNetworkData.serverPort, 0, 0);
	}
}

void GameState::handleInput() {
	if (GetAsyncKeyState(0x43) & 1) {		// C KEY PRESSED
		ColorEventPacket colorEvent[1];
		colorEvent->typeID = ID_COLOR_EVENT_MSG;
		colorEvent-> color = rand() % 100;

		if (mNetworkData.isHost) {
			mpPeer->Send((char*)colorEvent, sizeof(ColorEventPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				clientAddress, false);
		}
		else {
			mpPeer->Send((char*)colorEvent, sizeof(ColorEventPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				hostAddress, false);
		}
	}
	else if (GetAsyncKeyState(0x44) & 1) {	// D KEY PRESSED
		DamageEventPacket damageEvent[1];
		damageEvent->typeID = ID_DAMAGE_EVENT_MSG;
		damageEvent->damage = rand() % 100;
		
		if (mNetworkData.isHost) {
			mpPeer->Send((char*)damageEvent, sizeof(DamageEventPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				clientAddress, false);
		}
		else {
			mpPeer->Send((char*)damageEvent, sizeof(DamageEventPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				hostAddress, false);
		}
	}
	else if (GetAsyncKeyState(0x45) & 1) {	// E KEY PRESSED
		HealEventPacket healEvent[1];
		healEvent->typeID = ID_HEAL_EVENT_MSG;
		healEvent->amount = rand() % 100;

		if (mNetworkData.isHost) {
			mpPeer->Send((char*)healEvent, sizeof(HealEventPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				clientAddress, false);
		}
		else {
			mpPeer->Send((char*)healEvent, sizeof(HealEventPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0,
				hostAddress, false);
		}
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {
		exit = true;
	}
}

void GameState::handleNetwork() {
	RakNet::Packet* packet;

	for (
		packet = mpPeer->Receive();
		packet;
		mpPeer->DeallocatePacket(packet), packet = mpPeer->Receive()
		) {
		switch (packet->data[0]) {
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			std::cout << "A client has disconnected" << std::endl;
			break;
		case ID_REMOTE_CONNECTION_LOST:
			std::cout << "A client has lost connection" << std::endl;
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			std::cout << "A client has connected" << std::endl;
			clientAddress = packet->systemAddress;
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			std::cout << "Connected to server" << std::endl;
			hostAddress = packet->systemAddress;
			break;
		}
		case ID_NEW_INCOMING_CONNECTION:
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			std::cout << "Server is full" << std::endl;
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			if (mNetworkData.isHost) {
				printf("A client has disconnected. \n");
			}
			else {
				printf("Server has disconnected. \n");
			}
			break;
		case ID_CONNECTION_LOST:
			if (mNetworkData.isHost) {
				printf("A client has lost connection. \n");
			}
			else {
				printf("Server has lost connection. \n");
			}
			break;
		case ID_COLOR_EVENT_MSG:
		{
			ColorEventPacket* currPacket = (ColorEventPacket*)packet->data;
			ColorEvent* cEvent = new ColorEvent(currPacket->color);
			eventManager.add(cEvent->getType(), cEvent);

			break;
		}
		case ID_DAMAGE_EVENT_MSG:
		{
			DamageEventPacket* currPacket = (DamageEventPacket*)packet->data;
			DamageEvent* dEvent = new DamageEvent(currPacket->damage);
			eventManager.add(dEvent->getType(), dEvent);

			break;
		}
		case ID_HEAL_EVENT_MSG:
		{
			HealEventPacket* currPacket = (HealEventPacket*)packet->data;
			HealEvent* hEvent = new HealEvent(currPacket->amount);
			eventManager.add(hEvent->getType(), hEvent);

			break;
		}
		default:
			std::cout << "Default MSG" << std::endl;
			break;
		}
	}
}

void GameState::handleUpdate() {
	while (eventManager.getEventListLength() > 0) {
		eventManager.execute();
	}
}