#pragma once
#include "Vector2.h"
#include "timer.h"

class Camera
{
public:
	Camera() {
		timer_shake.set_one_shot(true);
		timer_shake.set_callback([&]() {
			is_shaking = false;
			reset();
		});
	}
	~Camera() = default;

	const Vector2& get_position() const { return position; }
	void reset() { position = Vector2(0, 0); }

	void update(int delta) {
		timer_shake.update(delta);
		if (is_shaking) {
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

	void shake(float strength, int duration) {
		is_shaking = true;
		shaking_strength = strength;
		timer_shake.set_interval(duration);
		timer_shake.restart();
		std::cout << "Shaking" << std::endl;
		std::cout << strength << " " << duration << std::endl;
		//system("pause");
	}

private:
	Vector2 position;
	Vector2 viewport_size;

	Timer timer_shake;
	bool is_shaking = false;
	float shaking_strength;
};
