#include "events/ColorEvent.h"

void ColorEvent::execute() {
	std::cout << "Color Event Executed: "  << mColor << std::endl;
}