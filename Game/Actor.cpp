#include "Actor.h"

void Actor::render() {
	if (!is_cbox_hide)
		Object::render_cbox();
	current_animation->render(position.x, position.y);
}

void Actor::clean() {

}

void Actor::input(const ExMessage& msg) {
	switch (msg.message) {
	case WM_KEYDOWN:
		switch (msg.vkcode) {
		case 0x41:
			//is_left_keydown = true;
			is_facing_right = false;
			moving_state |= static_cast<uint8_t>(MovingDir::L);
			break;
		case 0x44:
			//is_right_keydown = true;
			is_facing_right = true;
			moving_state |= static_cast<uint8_t>(MovingDir::R);
			break;
		case 0x57: // W
			moving_state |= static_cast<uint8_t>(MovingDir::U);
			jump();
			break;
		case 0x53: // S
			moving_state |= static_cast<uint8_t>(MovingDir::D);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode) {
		case 0x41:
			//is_left_keydown = false;
			moving_state &= ~static_cast<uint8_t>(MovingDir::L);
			break;
		case 0x44:
			//is_right_keydown = false;
			moving_state &= ~static_cast<uint8_t>(MovingDir::R);
			break;
		case 0x57: // W
			moving_state &= ~static_cast<uint8_t>(MovingDir::U);
			break;
		case 0x53: // S
			moving_state &= ~static_cast<uint8_t>(MovingDir::D);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Actor::update(int delta) {
	//int dir = is_right_keydown - is_left_keydown;
	if (moving_state != 0) {
		run(delta);
		//float distence = delta * walk_velocity * dir;
		//position.x += distence;
		is_running = true;
		current_animation = is_facing_right ? &animation_run_right
			: &animation_run_left;
	}
	else {
		current_animation = is_facing_right ? &animation_idle_right
			: &animation_idle_left;
	}
	move_and_collision(delta);
	current_animation->update(delta);
}

void Actor::run(int delta) {
	int x_dir = get_dir(moving_state & 0xC);
	int y_dir = get_dir((moving_state & 0x3) << 2);
	
	Vector2 distence = Vector2(x_dir, 0) * walk_velocity * delta;
	position += distence;
	cbox.position += distence;
	//std::cout << "Moving_state: " << x_dir << " " << y_dir << std::endl;
}

void Actor::jump() {
	if (!number_of_jumps) return;
	number_of_jumps--;
	velocity += { 0, jump_velocity };
}

void Actor::move_and_collision(int delta) {
	float last_velocity_y = velocity.y;
	velocity.y += 0 * delta;
	Vector2 del = velocity * (float)delta;
	position += del;
	cbox.position += del;

	if (velocity.y > 0) {
		
	}



}

bool Actor::check_collision(const CollisionBox& cbox1, const CollisionBox& cbox2) {
	Vector2 pos_1 = cbox1.position + Vector2(0, cbox1.size.y);
	Vector2 pos_2 = cbox2.position + Vector2(0, cbox2.size.y);
	float x1 = pos_1.x, y1 = pos_1.y;
	float x2 = pos_2.x, y2 = pos_2.y;

	return x1 < x2 + cbox2.size.x && x1 + cbox1.size.x > x2 &&
		y1 < y2 + cbox2.size.y && y1 + cbox1.size.y > y2;
}