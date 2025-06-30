#include "Platform.h"

void Platform::update(int delta) {
	//std::cout << position.x << " " << position.y << std::endl;
	//std::cout << size.x << " " << size.y << std::endl;
	//std::cout << cbox.center_pos.x << " " << cbox.center_pos.y << std::endl;
	//std::cout << cbox.position.x << " " << cbox.position.y << std::endl;
	//std::cout << cbox.size.x * 0.5f << " " << cbox.size.y * 0.5f << std::endl;
	//std::cout << "----------------------------------" << std::endl;
}

void Platform::render(const Camera& camera) {
	Object::render_cbox(camera);
}

void Platform::clean() {

}