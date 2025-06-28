#include "GameScene.h"

void GameScene::onEnter() {
	std::cout << "Enter GameScene" << std::endl;
}

void GameScene::onExit() {
	std::cout << "Exit GameScene" << std::endl;
}

void GameScene::render() {
	if (!vec_actors.empty()) {
		for (auto actor : vec_actors) actor->render();
	}
	if (!vec_objects.empty()) {
		for (auto obj : vec_objects) obj->render();
	}
}

void GameScene::update(int delta) {
	if (!vec_actors.empty()) {
		for(auto actor : vec_actors) actor->update(delta);
	}
	if (!vec_objects.empty()) {
		for (auto obj : vec_objects) obj->update(delta);
	}
	move_and_collision(delta);
}

void GameScene::input(const ExMessage& msg) {
	for(auto actor : vec_actors) actor->input(msg);
}

void GameScene::move_and_collision(int delta) {
	if (vec_actors.empty())
		return;
	
	for (Actor* actor : vec_actors) {
		//if (actor->get_velocity().y <= 0) continue;
		for (Object* obj : vec_objects) {
			const CollisionBox& cbox1 = actor->get_cbox();
			const CollisionBox& cbox2 = obj->get_cbox();
			//std::cout << "Check res: " << check_collision(cbox1, cbox2) << std::endl;
			if (check_collision(cbox1, cbox2)) {
				//std::cout << "Collision!" << std::endl;
				//system("pause");
				break;
			}
		}
	}
	}

}

void GameScene::clean() {

}

inline bool GameScene::check_collision(const CollisionBox& cbox1, const CollisionBox& cbox2) {
	//std::cout << cbox1.cbox_get_center_pos().x << " " << cbox2.cbox_get_center_pos().x << std::endl;
	//std::cout << cbox1.cbox_get_size().x << " " << cbox2.cbox_get_size().x << std::endl;
	//std::cout << cbox1.cbox_get_center_pos().y << " " << cbox2.cbox_get_center_pos().y << std::endl;
	//std::cout << cbox1.cbox_get_size().y << " " << cbox2.cbox_get_size().y << std::endl;

	return (std::abs(cbox1.cbox_get_center_pos().x - cbox2.cbox_get_center_pos().x))
		<= ((cbox1.cbox_get_size().x + cbox2.cbox_get_size().x) * 0.5f) 
		&& (std::abs(cbox1.cbox_get_center_pos().y - cbox2.cbox_get_center_pos().y))
		<= ((cbox1.cbox_get_size().y + cbox2.cbox_get_size().y) * 0.5f);
	// return 后半部分可能不会触发，但是我没又准确的数学证明
}