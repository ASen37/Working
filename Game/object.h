#pragma once

#include <graphics.h>
#include <iostream>
#include <vector>
#include "vector2.h"

class Object
{
protected:
	struct CollisionBox
	{
		Vector2 position;
		Vector2 size;
	};
public:
	Object() = default;
	~Object() = default;

	virtual void update(int delta) = 0;
	virtual void render() = 0;
	virtual void clean() = 0;

	void set_position(float x, float y) {
		position.x = x;
		position.y = y;
	}

	/*
	 * @brief 用于将碰撞盒与渲染“盒”中心对齐
	 */
	void bindCBox(Vector2 cbox_pos, Vector2 cbox_size) {
		cbox.position = cbox_pos;
		cbox.size = cbox_size;
		Vector2 del = size - cbox.size;
		del *= 0.5f;
		cbox.position += del;
	}

	void render_cbox() {
		setlinecolor(RGB(255, 0, 0));
		rectangle(cbox.position.x, cbox.position.y,
			cbox.position.x + cbox.size.x, cbox.position.y + cbox.size.y);
	}

public:
	CollisionBox cbox;
	std::vector<Object*> elements;

protected:
	bool is_cbox_hide = true;
	const float gravity = 1.6e-3f;

	Vector2 position; // rendered position
	Vector2 velocity;
	Vector2 size;
	
};


