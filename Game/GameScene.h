#pragma once
#include "scene.h"

class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void render() override;
	virtual void update(int delta) override;
	virtual void input(const ExMessage& msg) override;

	virtual void clean();

public:
	SceneID id = SceneID::GameScene;

};