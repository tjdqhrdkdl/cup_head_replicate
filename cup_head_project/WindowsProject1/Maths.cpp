#include "Maths.h"
#include <math.h>

Vector2 Vector2::Zero = { 0.0f,0.0f };
Vector2 Vector2::One = { 1.0f,1.0f };
Vector2 Vector2::Up = { 0.0f,-1.0f };
Vector2 Vector2::Down = { 0.0f,1.0f };
Vector2 Vector2::Right = { 1.0f,0.0f };
Vector2 Vector2::Left = { -1.0f,0.0f };
Vector2 Vector2::LeftUp = { -sqrtf(0.5f),-sqrtf(0.5f) };
Vector2 Vector2::LeftDown = { -sqrtf(0.5f), sqrtf(0.5f) };
Vector2 Vector2::RightUp = { sqrtf(0.5f),-sqrtf(0.5f) };
Vector2 Vector2::RightDown = { sqrtf(0.5f), sqrtf(0.5f) };

const std::wstring Vector2::GetDirInStr()
{
	if (isUp())
		return L"Up";
	else if (isDown())
		return  L"Down";
	else if (isRight())
		return  L"Right";
	else if (isLeft())
		return L"Left";
	else if (isRightUp())
		return L"RightUp";
	else if (isRightDown())
		return L"RightDown";
	else if (isLeftUp())
		return L"LeftUp";
	else if (isLeftDown())
		return L"LeftDown";

	else
		return L"";
}
