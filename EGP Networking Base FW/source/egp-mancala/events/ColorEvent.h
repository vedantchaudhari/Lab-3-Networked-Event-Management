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

#include <iostream>

#include "events/Event.h"

class ColorEvent : public Event {
private:
	EVENT_TYPE mType;
	int color;

public:
	ColorEvent(int c) : mType(COLOR_EVENT), color(c) {};

	virtual void execute() override;
};