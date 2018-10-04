#include "events/DamageEvent.h"

void DamageEvent::execute() {
	std::cout << "Damage: " << mDamage << std::endl;
}