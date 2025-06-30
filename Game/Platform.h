#pragma once
#include "object.h"
#include "vector2.h"

class Platform : public Object
{
public:
	Platform() {
		is_cbox_hide = false;
	}
	Platform(Vector2 pos, Vector2 size) : Object(pos, size) {
		cbox = CollisionBox(size);
		cbox.bind(center_pos);
		is_cbox_hide = false;
	}
	~Platform() = default;

	void update(int delta) override;
	void render(const Camera& camera) override;
	void clean() override;

private:

};


