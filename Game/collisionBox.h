#pragma once
#include "Vector2.h"

class CollisionBox
{
public:
	CollisionBox() = default;
	CollisionBox(Vector2& cbox_size) 
		: cbox_size(cbox_size) 
		, cbox_center_pos(Vector2(0.0f, 0.0f)) {}
	~CollisionBox() = default;

	inline const Vector2& cbox_get_center_pos() const { return cbox_center_pos; }
	inline const Vector2& cbox_get_size() const { return cbox_size; }
	
	void cbox_set_size(Vector2& new_size) { cbox_size = new_size; }
	void bind(const Vector2& actor_center_pos) {
		cbox_center_pos = actor_center_pos;
	}
private:
	Vector2 cbox_center_pos;
	Vector2 cbox_size;
};
