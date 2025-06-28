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
		if (actor->get_velocity().y <= 0) continue;
		for (Object* obj : vec_objects) {
			const Object::CollisionBox& cbx1 = actor->cbox;
			const Object::CollisionBox& cbx2 = obj->cbox;
			if (cbx2.position.x == 300) {
				std::cout << "POS: " << cbx2.position.x << " " << cbx2.position.y << std::endl;
				std::cout << "SIZE: " << cbx2.size.x << " " << cbx2.size.y << std::endl;
			}
			//if (cbx1.position.x + cbx1.size.x <= cbx2.position.x ||
			//	cbx1.position.x >= cbx2.position.x + cbx2.size.x) continue;
			
			if (check_collision(cbx1, cbx2)) {
				std::cout << "Collision " << cbx1.center_pos.x << " " << cbx1.center_pos.y << std::endl;
				const Vector2& cur_vel = actor->get_velocity();
				const Vector2& cur_pos = actor->get_position();
				const Vector2& cur_siz = actor->get_size();

				/*
				 * @ brief 关于一下这段代码的一些解释：
				 * @ description 这里的 delta_pos_y 相当于这一逻辑帧内，玩家脚或碰撞盒底部越过碰撞体顶部的距离
				 * 也就是说当前两者碰撞盒矩形已经相交，我们需要将两者的位置进行调整，使得两者不再相交
				 * last_tick_foot_pos_y 相当于上一逻辑帧的玩家脚或碰撞盒底部位置
				 * 也就是说，上一逻辑帧的玩家脚或碰撞盒底部位置，如果小于碰撞体顶部位置，
				 * 说明玩家脚或碰撞盒已经完全越过碰撞体顶部，需要进行一些处理
				 * 具体的处理方式是，将玩家的位置调整到碰撞体底部的位置，并将速度设置为 0，
				 * 并重新绑定碰撞盒，使得玩家的碰撞盒大小恢复到正常大小
				 */
				float delta_pos_y = cur_vel.y * delta;
				float last_tick_foot_pos_y = cbx1.position.y + cbx1.size.y - delta_pos_y;
				if (last_tick_foot_pos_y <= cbx2.position.y)
				{
					actor->set_position(cur_pos.x, cbx2.position.y - cur_siz.y - (cbx1.size.y - cur_siz.y) * 0.5f);
					actor->set_velocity(cur_vel.x, 0);
					actor->bindCBox(cbx1.size);
					actor->land();
					break;
				}
			}
		}
	}

}

void GameScene::clean() {

}

inline bool GameScene::check_collision(const Object::CollisionBox& cbox1, const Object::CollisionBox& cbox2) {
	Vector2 min1 = cbox1.center_pos - cbox1.size * 0.5f;
	Vector2 max1 = min1 + cbox1.size;
	Vector2 min2 = cbox2.center_pos - cbox2.size * 0.5f;
	Vector2 max2 = min2 + cbox2.size;
	
	return (max1.x >= min2.x && min1.x <= max2.x) && 
		(max1.y >= min2.y && min1.y <= max2.y);
}