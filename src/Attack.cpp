#include "Attack.h"

void Attack::_register_methods()
{
	register_method("_init", &Attack::_init);
	register_method("counter", &Attack::counter);
	register_property("Direction", &Attack::Direction, Vector2(0,0));
}

void Attack::_init()
{

}

void Attack::destroy()
{
	this->queue_free();
}

void Attack::counter()
{
	this->queue_free();
}