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
	//subtract damage from our healht
	health = health - damage;
	//let the user know this actually happened
	cout << "Health: " <<  health << endl;
	//if we are dead we should do something
	if (health < 1)
		cout << "U Dead" << endl;
}

//key presses
//https://docs.godotengine.org/en/3.0/classes/class_@globalscope.html?highlight=%40GlobalScope
void Player::_physics_process(float delta)
{
	moving = false;

	//first we do left and right
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

	//then we do up and down
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

	//if we are not moving stop the animation
	//set it to the first frame
	//at some point we should create an idle animation
	if (!moving)
	{
		anim->stop();
		anim->set_frame(0ULL);
	}

	//move and collide
	KinematicCollision2D* collider = *move_and_collide((*Velocity * delta));

	//if the collider is a nullpointer we didnt hit anything
	if (collider != nullptr) {
		//if its a static object we can see this way
		if (collider->get_collider()->is_class("StaticBody2D"))
		{
			cout << "Hit Static Body" << endl;
		}
	}

	//reset velocity
	Velocity->x = 0;
	Velocity->y = 0;


}