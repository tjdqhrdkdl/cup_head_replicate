#include "Maths.h"
#include <math.h>

Vector2 Vector2::Zero = { 0.0f,0.0f };
Vector2 Vector2::One = { 1.0f,1.0f };
Vector2 Vector2::Up = { 0.0f,-1.0f };
Vector2 Vector2::Down = { 0.0f,1.0f };
Vector2 Vector2::Right = { 1.0f,0.0f };
Vector2 Vector2::Left = { -1.0f,0.0f };
Vector2 Vector2::LeftUp = { -sqrtf(0.5f),sqrtf(0.5f) };
Vector2 Vector2::LeftDown = { -sqrtf(0.5f), -sqrtf(0.5f) };
Vector2 Vector2::RightUp = { sqrtf(0.5f),sqrtf(0.5f) };
Vector2 Vector2::RightDown = { sqrtf(0.5f), -sqrtf(0.5f) };
