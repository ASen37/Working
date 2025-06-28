#pragma once
#include <graphics.h>
#include <vector>
#include "object.h"

class Actor;
class Scene
{
protected:
	enum class SceneID
	{
		Manager = 0,
		MenuScene,
		GameScene
	};
public:
	Scene() = default;
	~Scene() = default;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void render() = 0;
	virtual void update(int delta) = 0;
	virtual void input(const ExMessage& msg) = 0;

	void clean();
	void switchTo();

	const std::vector<Object*>& get_obj() const { return vec_objects; }
	const std::vector<Actor*>& get_actors() const { return vec_actors; }

	template<typename T>
	void addObject(T* obj) {
		add_to_vec(obj, std::is_same<T, Actor>{});
	}


protected:
	std::vector<Object* > vec_objects;
	std::vector<Actor* > vec_actors;

private:
	void add_to_vec(Object* obj, std::false_type) {
		vec_objects.push_back(obj);
	}

	void add_to_vec(Actor* obj, std::true_type) {
		vec_actors.push_back(obj);
	}

};