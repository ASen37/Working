#pragma once

#include <graphics.h>
#include <iostream>
#include <vector>
#include "vector2.h"

class Object
{
public:
	struct CollisionBox
	{
		Vector2 position;
		Vector2 size;
		Vector2 center_pos;
	};
public:
	Object() = default;
	//Object(Vector2 pos, Vector2 size) 
	//	: position(pos)
	//	, size(size) {
	//	center_pos = position + size * 0.5f;
	//}
	~Object() = default;

	virtual void update(int delta) = 0;
	virtual void render() = 0;
	virtual void clean() = 0;

	inline void set_position(float x, float y) {
		position.x = x;
		position.y = y;
	}

	inline void set_size(float w, float h) {
		size.x = w;
		size.y = h;
	}

	/*
	 * @brief 设置碰撞和位置与大小，调试用函数
	 */
	void setCBox(Vector2 cbox_pos, Vector2 cbox_size) {
		cbox.position = cbox_pos;
		cbox.size = cbox_size;
		Vector2 del = size - cbox.size;
		del *= 0.5f;
		cbox.position += del;
	}

	/*
	 * @brief 用于将碰撞盒与渲染“盒”中心对齐
	 */
	void bindCBox(Vector2 cbox_size) {
		float cx = position.x + size.x * 0.5f;
		float cy = position.y + size.y * 0.5f;
		cbox.center_pos = Vector2(cx, cy);
		cbox.size = cbox_size;
		cbox.position.x = cx - cbox.size.x * 0.5f;
		cbox.position.y = cy - cbox.size.y * 0.5f;
	}

	void render_cbox() {
		setlinecolor(RGB(255, 0, 0));
		float x1 = cbox.center_pos.x - cbox.size.x * 0.5f;
		float y1 = cbox.center_pos.y - cbox.size.y * 0.5f;
		float x2 = cbox.center_pos.x + cbox.size.x * 0.5f;
		float y2 = cbox.center_pos.y + cbox.size.y * 0.5f;

		rectangle(x1, y1, x2, y2);
	}

	inline void update_cbox(Vector2 distence) {
		cbox.center_pos += distence;
	}

	const Vector2& get_position() const {
		return position;
	}

	const Vector2& get_size() const {
		return size;
	}

public:
	CollisionBox cbox;
	std::vector<Object*> elements;

protected:
	bool is_cbox_hide = true;
	const float gravity = 1.6e-3f;

	Vector2 position; // rendered position
	Vector2 center_pos; // for calculation
	Vector2 velocity;
	Vector2 size;
	
};


