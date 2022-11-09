#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2& operator +(Vector2 other) 
	{ 
		x += other.x;
		y += other.y;
		return *this; 
	}
	Vector2 operator -(Vector2 other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& operator /(float f)
	{
		x /= f;
		y /= f;
		return *this;
	}
	Vector2& operator *(float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	bool operator ==(Vector2 other)
	{
		if (x == other.x && y == other.y)
			return true;
		return false;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const Vector2& other) = default;
	Vector2() = default;
	~Vector2() = default;

	bool OutWindow()
	{
		if (y > 5000 or y < -2000 or x < -2000 or x>5000)
			return true;
		return false;
	}
	bool isRight() { return *this == Vector2::Right; }
	bool isRightUp() { return *this == Vector2::RightUp; }
	bool isRightDown() { return *this == Vector2::RightDown; }
	bool isLeft() { return *this == Vector2::Left; }
	bool isLeftUp() { return *this == Vector2::LeftUp; }
	bool isLeftDown() { return *this == Vector2::LeftDown; }
	bool isUp() { return *this == Vector2::Up; }
	bool isDown() { return *this == Vector2::Down; }

	static Vector2 Zero;
	static Vector2 One;
	static Vector2 Right;
	static Vector2 Left;
	static Vector2 Up;
	static Vector2 Down;
	static Vector2 LeftUp;
	static Vector2 LeftDown;
	static Vector2 RightUp;
	static Vector2 RightDown;

};