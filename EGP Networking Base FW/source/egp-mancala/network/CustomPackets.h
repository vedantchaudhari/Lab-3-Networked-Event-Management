#pragma once

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

#pragma pack(push, 1)
struct ColorEventPacket {
	unsigned char typeID;
	int color;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DamageEventPacket {
	unsigned char typeID;
	int damage;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct HealEventPacket {
	unsigned char typeID;
	int amount;
};
#pragma pack(pop)