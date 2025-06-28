#include "SceneManager.h"

void SceneManager::onEnter() {

}

void SceneManager::onExit() {

}

void SceneManager::update(int delta) {
	current_scene->update(delta);
}

void SceneManager::render() {
	current_scene->render();
}

void SceneManager::input(const ExMessage& msg) {
	current_scene->input(msg);
}

void SceneManager::switchTo(SceneID id) {
	switch (id) {
	case SceneID::MenuScene:
		current_scene = menu;
		break;
	case SceneID::GameScene:
		current_scene = game;
		break;
	default:
		break;
	}
	current_scene->onEnter();
}