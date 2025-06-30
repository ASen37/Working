#pragma once

#include <graphics.h>
#include <iostream>
#include <vector>
#include "vector2.h"
#include "collisionBox.h"
#include "camera.h"

class Object
{
public:
	Object() = default;
	Object(Vector2 pos, Vector2 size) 
		: position(pos)
		, size(size) {
		center_pos = position + size * 0.5f;
		//cbox.bind(center_pos);
	}
	~Object() = default;

	virtual void update(int delta) = 0;
	virtual void render(const Camera& camera) = 0;
	virtual void clean() = 0;

	/*
	 * @brief Actor 相关函数
	 */
	const CollisionBox& get_cbox() const { return cbox; };
	const Vector2& get_size() const { return size; }
	const Vector2& get_center_pos() const { return center_pos; }

	const void set_position(const Vector2& pos) { position = pos; }
	const void set_size(const Vector2& size) { this->size = size; }

	void update_position() {
		position = center_pos - size * 0.5f;
	}

	void render_cbox() {
		setlinecolor(RGB(255, 0, 0));
		const Vector2& cbox_center_pos = cbox.cbox_get_center_pos();
		const Vector2& cbox_size = cbox.cbox_get_size();

		float x1 = cbox_center_pos.x - cbox_size.x * 0.5f;
		float y1 = cbox_center_pos.y - cbox_size.y * 0.5f;
		float x2 = cbox_center_pos.x + cbox_size.x * 0.5f;
		float y2 = cbox_center_pos.y + cbox_size.y * 0.5f;

		rectangle(x1, y1, x2, y2);
	}

	void render_cbox(const Camera& camera) {
		setlinecolor(RGB(255, 0, 0));
		const Vector2& cbox_center_pos = cbox.cbox_get_center_pos();
		Vector2 render_center_pos = cbox_center_pos - camera.get_position();
		const Vector2& cbox_size = cbox.cbox_get_size();

		float x1 = render_center_pos.x - cbox_size.x * 0.5f;
		float y1 = render_center_pos.y - cbox_size.y * 0.5f;
		float x2 = render_center_pos.x + cbox_size.x * 0.5f;
		float y2 = render_center_pos.y + cbox_size.y * 0.5f;

		rectangle(x1, y1, x2, y2);
	}

public:
	std::vector<Object*> elements;

protected:
	bool is_cbox_hide = true;
	const float gravity = 1.6e-3f;

	Vector2 position; // for rendering & initialization
	Vector2 center_pos; // for calculation
	Vector2 velocity = { 0, 0 };
	Vector2 size;
	
	CollisionBox cbox;
};


