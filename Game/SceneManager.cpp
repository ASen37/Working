#include "SceneManager.h"

void SceneManager::onEnter() {
	current_scene->onEnter();
}

void SceneManager::onExit() {
	current_scene->onExit();
}

void SceneManager::update(int delta) {
	current_scene->update(delta);
}

void SceneManager::render(const Camera& camera) {
	current_scene->render(camera);
}

void SceneManager::input(const ExMessage& msg) {
	current_scene->input(msg);
}

void SceneManager::switchTo(SceneID id) {
	switch (id) {
	case SceneID::MENU:
		current_scene = menu;
		current_scene->onEnter();
		break;
	case SceneID::GAME:
		current_scene = game;
		current_scene->onEnter();
		break;
	default:
		break;
	}
	current_scene->onEnter();
}

void SceneManager::switchTo(Scene* scene) {
	current_scene = scene;
	current_scene->onEnter();
}