#pragma once
#define KEY_PRESSED(KEY) ya::Input::GetKeyState(KEY)==eKeyState::PRESSED
#define KEY_UP(KEY) ya::Input::GetKeyState(KEY)==eKeyState::UP
#define KEY_DOWN(KEY) ya::Input::GetKeyState(KEY)==eKeyState::DOWN

enum class eSceneType
{
	Logo,
	Title,
	Map,
	BossCarnation,
	BossBeppi,
	BossWernerWerman,
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
	Rigidbody,
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
	BehindMonster,
	BehindMonsterHat,
	FrontObject,
	FrontMonster,
	Monster_Projecttile,
	Effect,
	Player,
	Player_Projecttile,
	Top_Effect,

	UI = _COLLIDER_LAYER - 2,
	Camera = _COLLIDER_LAYER - 1,
	End = _COLLIDER_LAYER,
};
enum class eUIType
{
	Gun,
	HP,
	MP,
	SHOP,
	INVENTORY,
	TITLEOPTION_START,
	TITLEOPTION_OPTION,
	TITLEOPTION_EXIT,
	PLAYOPTION_PANEL,
	PLAYOPTION_RESUME,
	PLAYOPTION_RETRY,
	PLAYOPTION_EXIT,


	END,
};
enum class eGunType
{
	PeaShooter,
	CrackShot,
	Spreader,
	End,
};

enum class eBossType
{
	WernerWerman,
	Beppi,
	Carnation,
	End
};
union CollisionId
{
	struct {
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;
};

