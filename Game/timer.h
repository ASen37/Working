#pragma once
#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart() {
		passed_time = 0;
		is_shotted = false;
	}

	void set_interval(int ms) { interval = ms; }					// 设置定时器定时间隔
	void set_one_shot(bool flag) { is_one_shot = flag; }			// 设置定时器触发状态（是否单次触发）
	void set_callback(std::function<void()> cb) { callback = cb; }	// 设置定时器回调函数

	void pause() { is_paused = true; }								// 暂停定时器
	void resume() { is_paused = false; }							// 恢复定时器

	void update(int delta) {										// 更新定时器
		if (is_paused) return;

		passed_time += delta;
		if (passed_time >= interval) {
			if (!is_one_shot || (is_one_shot && !is_shotted))
				callback();
			is_shotted = true;
			passed_time = 0;
		}
	}

private:
	int passed_time;				// 定时器已经过去的时间
	int interval;					// 定时器定时间隔

	bool is_paused;					// 定时器是否处于暂停状态
	bool is_one_shot;				// 回调是否单次触发
	bool is_shotted;				// 回调是否已经触发
	std::function<void()> callback;	// 回调函数
};
