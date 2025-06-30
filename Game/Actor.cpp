#include "Actor.h"

void Actor::render(const Camera& camera) {
	if (!is_cbox_hide)
		Object::render_cbox(camera);
	update_position();
	//std::cout << "Position: " << position.x << " " << position.y << std::endl;
	current_animation->render(camera, position.x, position.y);
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
			//walk_velocity = MAX_MOVE_H_VELOCITY;
			break;
		case 0x44:
			//is_right_keydown = true;
			is_facing_right = true;
			moving_state |= static_cast<uint8_t>(MovingDir::R);
			//walk_velocity = MAX_MOVE_H_VELOCITY;
			break;
		case 0x57: // W
			moving_state |= static_cast<uint8_t>(MovingDir::U);
			jump();
			break;
		case 0x53: // S
			moving_state |= static_cast<uint8_t>(MovingDir::D);
			main_camera.shake(5, 500);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode) {
		case 0x41:
			is_left_keydown = false;
			moving_state &= ~static_cast<uint8_t>(MovingDir::L);
			break;
		case 0x44:
			is_right_keydown = false;
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
	//if (is_right_keydown) is_facing_right = true;
	//else if (is_left_keydown) is_facing_right = false;
	//int dir = is_right_keydown - is_left_keydown;
	if (moving_state != 0) {
		moving_horizontal(delta);
		is_running = true;
		current_animation = is_facing_right ? &animation_run_right
			: &animation_run_left;
	}
	else {
		current_animation = is_facing_right ? &animation_idle_right
			: &animation_idle_left;
	}
	moving_vertical(delta);
	current_animation->update(delta);
	//if (position.y <= 0) system("pause");
}

void Actor::moving_horizontal(int delta) {
	int x_dir = get_dir(moving_state & 0xC);		// x 的移动方向:0,1,-1
	int y_dir = get_dir((moving_state & 0x3) << 2); // y 的移动方向:0,1,-1
	
	Vector2 distence = Vector2(x_dir, y_dir) * delta * walk_velocity;
	center_pos += distence;
	cbox.bind(center_pos);
	//std::cout << "Moving_state: " << x_dir << " " << y_dir << std::endl;
}

void Actor::jump() {
	//if (!number_of_jumps) return;
	number_of_jumps--;
	velocity += { 0, -jump_velocity };
}

void Actor::land() {
	number_of_jumps = MAX_NUMBER_OF_JUMPS;
}

void Actor::moving_vertical(int delta) {
	float last_velocity_y = velocity.y;
	velocity.y += gravity * delta;
	Vector2 distence = velocity * (float)delta;
	center_pos += distence;
	cbox.bind(center_pos);
}
