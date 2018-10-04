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

#include "events/EventManager.h"
#include "network/CustomPackets.h"

#include "RakNet/BitStream.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/RakPeerInterface.h"

enum NETWORK_MESSAGE_TYPE {
	ID_BASE_MESSAGE = ID_USER_PACKET_ENUM,
	ID_COLOR_EVENT_MSG,
	ID_DAMAGE_EVENT_MSG,
	ID_HEAL_EVENT_MSG
};

class GameState {
private:
	struct NetworkData {
		bool isHost;

		unsigned int maxClients;
		unsigned short serverPort;
	};
	
public:
	EventManager eventManager;
	NetworkData mNetworkData;

	RakNet::RakPeerInterface* mpPeer;
	RakNet::SystemAddress hostAddress;
	RakNet::SystemAddress clientAddress;

	bool exit = false;

	GameState();
	~GameState();

	void initNetwork();

	// Game Loop
	void handleDisplay();
	void handleInput();
	void handleNetwork();
	void handleUpdate();
};