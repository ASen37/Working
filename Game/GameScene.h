#pragma once
#include "scene.h"
#include "Actor.h"
#include "camera.h"

extern Camera main_camera;

class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void onEnter() override;
	void onExit() override;

	void render(const Camera& camera) override;
	void update(int delta) override;
	void input(const ExMessage& msg) override;

	void move_and_collision(int delta) override;
	void clean() override;

	inline bool check_collision(const CollisionBox& cbox1, const CollisionBox& cbox2);
public:
	const SceneID id = SceneID::GAME;

};