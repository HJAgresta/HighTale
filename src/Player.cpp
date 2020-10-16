#include "Player.h"

void Player::_register_methods()
{
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
	register_method("takeHit", &Player::takeHit);
	register_property<Player, float>("speed", &Player::speed, 100.0f);

}


void Player::_init()
{
	speed = 100.0f;
	Velocity = make_unique<Vector2>();
	input = Input::get_singleton();
}


void Player::_ready()
{
	anim = (AnimatedSprite*)get_node("AnimatedSprite");
}

void Player::takeHit(int damage)
{
	health = health - damage;
	cout << "Health: " <<  health << endl;
	if (health < 1)
		cout << "U Dead" << endl;
}

//key presses
//https://docs.godotengine.org/en/3.0/classes/class_@globalscope.html?highlight=%40GlobalScope
void Player::_physics_process(float delta)
{
	moving = false;


	if (input->is_action_pressed("ui_left") && !input->is_action_pressed("ui_right"))
	{
		Velocity->x = Velocity->x - speed;
		if (!input->is_action_pressed("ui_up") && !input->is_action_pressed("ui_down"))
			anim->play("left");
		moving = true;
	}
	else if (input->is_action_pressed("ui_right"))
	{
		Velocity->x = Velocity->x + speed;
		if (!input->is_action_pressed("ui_up") && !input->is_action_pressed("ui_down"))
			anim->play("right");
		moving = true;
	}

	if (input->is_action_pressed("ui_down") && !input->is_action_pressed("ui_up"))
	{
		Velocity->y = Velocity->y + speed;
		anim->play("front");
		moving = true;
	}
	else if (input->is_action_pressed("ui_up"))
	{
		Velocity->y = Velocity->y - speed;
		anim->play("back");
		moving = true;
	}

	if (!moving)
	{
		anim->stop();
		anim->set_frame(0ULL);
	}
	KinematicCollision2D* collider = *move_and_collide((*Velocity * delta));

	if (collider != nullptr) {
		WARN_PRINT(collider->get_collider()->get_class());
		if (collider->get_collider()->is_class("StaticBody2D"))
		{
			cout << "Hit Static Body" << endl;
		}
	}

	Velocity->x = 0;
	Velocity->y = 0;


}