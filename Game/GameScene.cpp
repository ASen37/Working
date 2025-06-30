#include "GameScene.h"

void GameScene::onEnter() {
	std::cout << "Enter GameScene" << std::endl;
}

void GameScene::onExit() {
	std::cout << "Exit GameScene" << std::endl;
}

void GameScene::render(const Camera& camera) {
	if (!vec_actors.empty()) {
		for (auto actor : vec_actors) actor->render(camera);
	}
	if (!vec_objects.empty()) {
		for (auto obj : vec_objects) obj->render(camera);
	}
}

void GameScene::update(int delta) {
	if (!vec_actors.empty()) {
		for(auto actor : vec_actors) actor->update(delta);
	}
	if (!vec_objects.empty()) {
		for (auto obj : vec_objects) obj->update(delta);
	}
	main_camera.update(delta);
	move_and_collision(delta);
}

void GameScene::input(const ExMessage& msg) {
	for(auto actor : vec_actors) actor->input(msg);
}

/*
 * @brief 碰撞检测处理，后续需要优化，优化方向：
 * 1. 只检测从玩家中心到碰撞盒中心坐标所成向量 与 玩家移动向量相同的物体/玩家
 * 2. 穿透修正，需要加入碰撞时的方向（左右侧壁检测），侧壁需将玩家左右推出发生穿透的距离
 */
void GameScene::move_and_collision(int delta) {
	if (vec_actors.empty())
		return;
	
	for (Actor* actor : vec_actors) {
		if (actor->get_velocity().y <= 0) continue;
		for (Object* obj : vec_objects) {
			const CollisionBox& cbox1 = actor->get_cbox();
			const CollisionBox& cbox2 = obj->get_cbox();
			if (check_collision(cbox1, cbox2)) {
				const Vector2& max_point1 = cbox1.cbox_get_center_pos() + cbox1.cbox_get_size() * 0.5f;
				const Vector2& min_point2 = cbox2.cbox_get_center_pos() - cbox2.cbox_get_size() * 0.5f;
				float overlapH = min((max_point1.x - min_point2.x), (cbox1.cbox_get_size().x));
				float overlapV = min((max_point1.y - min_point2.y), (cbox1.cbox_get_size().y));

				actor->position_correction({ 0, -overlapV });
				actor->set_velocity(actor->get_velocity().x, 0);
				//std::cout << "Collision: " << actor->get_center_pos().x << " " << actor->get_center_pos().y << std::endl;
				//system("pause");
				break;
			}
		}
	}

}

void GameScene::clean() {

}

// 碰撞检测函数：AABB算法，但是用的是中心坐标系
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