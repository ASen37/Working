#pragma once
#include <graphics.h>
#include <iostream>
#include "object.h"
#include "animation.h"
#include "utils.h"

class SceneManager;

extern Atlas atlas_player_idle_left;
extern Atlas atlas_player_idle_right;
extern Atlas atlas_player_run_left;
extern Atlas atlas_player_run_right;

extern SceneManager& manager;

class Actor : public Object
{
public:
	enum class MovingDir
	{
		U = 0x1,
		D = 0x2,
		L = 0x4,
		R = 0x8
	};
public:
	Actor() {
		animation_idle_left.set_atlas(&atlas_player_idle_left);
		animation_idle_right.set_atlas(&atlas_player_idle_right);
		animation_run_left.set_atlas(&atlas_player_run_left);
		animation_run_right.set_atlas(&atlas_player_run_right);

		animation_idle_left.set_interval(120);
		animation_idle_right.set_interval(120);
		animation_run_left.set_interval(120);
		animation_run_right.set_interval(120);

		position = { 100, 100 };
		size = { (float)atlas_player_idle_right.get_image(0)->getwidth() + 10.0f, 
				 (float)atlas_player_idle_right.get_image(0)->getheight()  + 10.0f};
		std::cout << position.x << " " << position.y << " " << size.x << " " << size.y << std::endl;
		bindCBox(position, size + Vector2(100.0f, 100.0f));
		std::cout << cbox.position.x << " " << cbox.position.y << " " << cbox.size.x << " " << cbox.size.y << std::endl;
		is_cbox_hide = false;
	}
	~Actor() {
		clean();
	}

	void input(const ExMessage& msg);
	void update(int delta) override;
	void render() override;
	void clean() override;
	void run(int delta);

	void jump();
	bool check_collision(const CollisionBox& cbox1, const CollisionBox& cbox2);
	void move_and_collision(int delta);


private:
	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;

	Animation* current_animation = nullptr;

private:
	uint8_t moving_state = 0x0;
	int number_of_jumps = 1;

	float walk_velocity = 0.32f;
	float jump_velocity = 1.0f;

	bool is_left_keydown = false;
	bool is_right_keydown = false;
	bool is_facing_right = true;
	bool is_running = false;
};
