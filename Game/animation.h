#pragma once

#include <functional>
#include "atlas.h"
#include "utils.h"
#include "camera.h"

class Animation
{
public:
	Animation() = default;
	~Animation() = default;

	void reset() {
		timer = 0;
		idx_frame = 0;
		interval = 0;
	}

	void set_atlas(Atlas* atlas) {
		reset();
		m_atlas = atlas;
	}

	void set_interval(int val) { interval = val; }
	void set_loop(bool flag) { is_loop = flag; }
	int get_idx_frame() const { return idx_frame; }

	IMAGE* get_frame() const { return m_atlas->get_image(idx_frame); }

	bool check_finished() {
		if (is_loop) return false;
		return (idx_frame == m_atlas->get_size() - 1);
	}
	
	void update(int delta) {
		timer += delta;
		if (timer >= interval) {
			timer = 0;
			idx_frame++;
			if (idx_frame >= m_atlas->get_size()) {
				idx_frame = is_loop ? 0 : m_atlas->get_size() - 1;
				if (!is_loop && callback)
					callback();
			}
		}
	}

	void render(const Camera& camera, int x, int y) const {
		//putimage_alpha(x, y, m_atlas->get_image(idx_frame));
		putimage_alpha(camera, x, y, m_atlas->get_image(idx_frame));
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

private:
	int timer = 0;
	int interval = 0;
	int idx_frame = 0;
	bool is_loop = true;
	Atlas* m_atlas = nullptr;
	std::function<void()> callback = nullptr;
};