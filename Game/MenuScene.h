#pragma once
#include "scene.h"

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void render() override;
	virtual void update(int delta) override;
	virtual void input(const ExMessage& msg) override;

	virtual void clean();
	virtual void switchTo();

public:
	const SceneID id = SceneID::MENU;
};