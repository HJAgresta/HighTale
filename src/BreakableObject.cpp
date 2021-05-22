#include "BreakableObject.h"


void BreakableObject::_register_methods()
{
	register_method("_init", &BreakableObject::_init);
	register_method("TakeHit", &BreakableObject::TakeHit);
	register_property("Health", &BreakableObject::Health, 100.0f);
}

void BreakableObject::_init()
{

}