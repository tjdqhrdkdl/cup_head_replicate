#pragma once
#define KEY_PRESSED(KEY) ya::Input::GetKeyState(KEY)==eKeyState::PRESSED
#define KEY_UP(KEY) ya::Input::GetKeyState(KEY)==eKeyState::UP
#define KEY_DOWN(KEY) ya::Input::GetKeyState(KEY)==eKeyState::DOWN

enum class eSceneType
{
	Logo,
	Title,
	Map,
	BossVegetable,
	BossBeppi,
	End,
	Max,
};
enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent, //≈ı∏Ì
	Blakc,
	Gray, //167 0 67
	White,
	End,
};
enum class eComponentType
{
	Animator,
	Collider,
	Sound,
	End,
};
enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
};
#define _COLLIDER_LAYER 16
enum class eColliderLayer
{
	Default,
	BackGround,
	BehindObject,
	FrontObject,
	Effect,
	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,


	UI = _COLLIDER_LAYER - 1,
	End = _COLLIDER_LAYER,
};
enum class eGunType
{
	PeaShooter,
	Spreader,
	CrackShot,
};
union CollisionId
{
	struct {
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;
};