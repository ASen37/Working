#pragma once
#include "object.h"
#include "vector2.h"

class Platform : public Object
{
public:
	Platform() {
		is_cbox_hide = false;
	}
	Platform(const Vector2& pos, const Vector2& s) {
		position = pos;
		size = s;
		bindCBox(position, size);
		is_cbox_hide = false;
	}
	~Platform() = default;

	void update(int delta) override;
	void render() override;
	void clean() override;

private:

};


