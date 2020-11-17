#include "Attack.h"

void Attack::_register_methods()
{
	register_method("_init", &Attack::_init);
}

void Attack::_init()
{

}

void Attack::destroy()
{
	this->queue_free();
}