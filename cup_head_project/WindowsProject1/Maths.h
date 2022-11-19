#pragma once
#include "Common.h"

#define PI 3.14159265f

struct Vector2
{
	float x;
	float y;

    Vector2 operator -()
    {
        return Vector2(-x, -y);
    }

    Vector2 operator+(const Vector2& other)
    {
        Vector2 temp;
        temp.x = x + other.x;
        temp.y = y + other.y;

        return temp;
    }

    Vector2 operator-(const Vector2& other)
    {
        Vector2 temp;
        temp.x = x - other.x;
        temp.y = y - other.y;

        return temp;
    }

    Vector2 operator*(const Vector2& other)
    {
        Vector2 temp;
        temp.x = x * other.x;
        temp.y = y * other.y;

        return temp;
    }

    Vector2 operator*(const float& value)
    {
        Vector2 temp;
        temp.x = x * value;
        temp.y = y * value;

        return temp;
    }

    Vector2 operator/(const float& value)
    {
        Vector2 temp;

        temp.x = x / value;
        temp.y = y / value;

        return temp;
    }

    Vector2& operator +=(const Vector2& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2& operator *=(const float value)
    {
        x *= value;
        y *= value;

        return *this;
    }

    Vector2& operator -=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    bool operator ==(const Vector2& other)
    {
        return (x == other.x && y == other.y);
    }
    //bool operator !=(const Vector2& other)
    //{
    //    return (x != other.x && y != other.y);
    //}

    constexpr Vector2(float _x, float _y) noexcept
        : x(_x)
        , y(_y)
    {

    }
    explicit Vector2(_In_reads_(2) const float* pArray)  noexcept
        : x(pArray[0])
        , y(pArray[1])
    {

    }

    void clear()
    {
        x = 0.0f;
        y = 0.0f;
    }

    float Length()
    {
        return sqrtf(x * x + y * y);
    }

    Vector2& Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;

        return *this;
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

	const std::wstring GetDirInStr();
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

namespace ya {
	namespace math
	{
		inline Vector2 Rotate(Vector2 vector, float degree)
		{
			float radian = (degree / 180.f) * PI;
			vector.Normalize();
			float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
			float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

			return Vector2(x, y);
		}

		inline float Dot(Vector2& v1, Vector2& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		inline float Cross(Vector2 v1, Vector2 v2)
		{
			return v1.x * v2.y - v1.y * v2.x;
		}

		inline float DegreeToRadian(float degree)
		{
			return degree * PI / 180.0f;
		}

		inline float RadianToDegree(float radian)
		{
			return radian * (180.0f / PI);
		}
	}
}