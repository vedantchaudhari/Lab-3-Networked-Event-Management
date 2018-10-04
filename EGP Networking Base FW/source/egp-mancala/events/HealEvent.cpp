#include "events/HealEvent.h"

void HealEvent::execute() {
	std::cout << "Heal: " << mAmount << std::endl;
}