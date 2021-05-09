#include "Player.h"

void Player::_register_methods()
{
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
	register_method("TakeHit", &Player::TakeHit);
	register_property<Player, float>("speed", &Player::speed, 100.0f);
	register_property<Player, float>("Health", &Player::Health, 100.0f);
	register_property<Player, float>("hitTime", &Player::hitTime, 1.0f);
	register_property<Player, float>("counterTime", &Player::counterTime, 1.0f);
	register_property<Player, float>("counterCooldown", &Player::counterCooldown, 1.0f);

}


void Player::_init()
{
	//registered properties
	speed = 100.0f;
	Health = 100.0f;
	hitTime = 1.0f;
	counterTime = 1.0f;
	counterCooldown = 1.0f;

	//unresistered properties
	stateTimer = 0.0f;
	Velocity = make_unique<Vector2>();
	input = Input::get_singleton();
	hitAnimAppend = "hit-";
}


void Player::_ready()
{
	anim = (AnimatedSprite*)get_node("AnimatedSprite");
}

bool Player::TakeHit(float damage, Attack* incoming)
{

	switch (PlayerState)
	{
	case COUNTER:

		incoming->counter();
		PlayerState = DEFAULT;

		return false;

	default:
		//subtract damage from our healht
		Health = Health - damage;

		PlayerState = HIT;
		stateTimer = 0;

		anim->play(hitAnimAppend + anim->get_animation());

		//if we are dead we should do something
		if (Health < 1)
			this->Destroy();

		incoming->destroy();

		return true;
	}
}

//key presses
//https://docs.godotengine.org/en/3.0/classes/class_@globalscope.html?highlight=%40GlobalScope
void Player::_physics_process(float delta)
{
	switch (PlayerState)
	{
	case COUNTER:
		stateTimer += delta;

		if (stateTimer > counterTime)
		{
			stateTimer = 0.0f;
			PlayerState = COOLDOWN;
			anim->stop();
			anim->set_frame(3ULL);
			break;
		}

		break;

	case COOLDOWN:
		stateTimer += delta;

		if (stateTimer > counterCooldown)
		{
			PlayerState = DEFAULT;
			break;
		}

		break;

	case HIT:
		stateTimer += delta;

		if (stateTimer > hitTime)
		{
			anim->play(anim->get_animation().right(hitAnimAppend.length()));

			PlayerState = DEFAULT;
			break;
		}

		break;
	default:


		if (input->is_action_pressed("counter"))
		{
			stateTimer = 0.0f;
			PlayerState = COUNTER;
			anim->stop();
			anim->set_frame(1ULL);
			break;
		}


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
			anim->play("down");
			moving = true;
		}
		else if (input->is_action_pressed("ui_up"))
		{
			Velocity->y = Velocity->y - speed;
			anim->play("up");
			moving = true;
		}

		//if we are not moving stop the animation
		//set it to the first frame
		//at some point we should create an idle animation
		if (!moving && PlayerState != HIT)
		{
			anim->stop();
			anim->set_frame(0ULL);
		}

		//move and collide
		move_and_collide((*Velocity * delta));

		//reset velocity
		Velocity->x = 0;
		Velocity->y = 0;

		break;
	}
}