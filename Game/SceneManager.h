#pragma once
#include "scene.h"
#include "MenuScene.h"
#include "GameScene.h"

extern MenuScene* menu;
extern GameScene* game;

class SceneManager : public Scene
{
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	void onEnter() override;
	void onExit() override;

	void render() override;
	void update(int delta) override;
	void input(const ExMessage& msg) override;

	void clean() {}
	void switchTo(SceneID id);

	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}

private:
	SceneManager() {}

public:
	Scene* current_scene = nullptr;
};