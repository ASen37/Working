#pragma once

#include <cmath>

class Vector2
{
public:
	float x;
	float y;

public:
	Vector2() = default;
	~Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {};

	// 重载加法相关运算符
	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}
	void operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
	}

	// 重载减法相关运算符
	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}
	void operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
	}

	// 重载乘法相关运算符
	float operator*(const Vector2& other) const {
		return x * other.x + y * other.y;
	}
	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}
	void operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
	}

	// 向量模长
	float length() {
		return std::sqrt(x * x + y * y);
	}

	// 标准化向量
	Vector2 normalize() {
		float len = length();
		if (len == 0) return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}
};
