#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"
namespace ya 
{
	class Bullet;
	class Animator;
	class Player : public GameObject
	{
	public:
		enum ePlayerState
		{
			PlayerState_None = 0x00000000,
			PlayerState_Input_Left	= 0x00000001,
			PlayerState_Input_Right = 0x00000002,
			PlayerState_Input_Up	= 0x00000004,
			PlayerState_Input_Down  = 0x00000008,
			PlayerState_Input_X		= 0x00000010,
			PlayerState_Input_C		= 0x00000020,
			PlayerState_OnDash		= 0x00000040,
			PlayerState_OnJump		= 0x00000080,
			PlayerState_OnHit		= 0x00000100,
			PlayerState_OnEX		= 0x00000200,
			PlayerState_OnUlt		= 0x00000400,
			PlayerState_LookRight	= 0x00000800,
			PlayerState_OnShoot		= 0x00001000,
		};
		Player();
		~Player();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;
		
		void PlayerKeyInput();
		void SetShooterCoolTime(eGunType guntype);
		Vector2 SetBulletStartPos(Bullet*);

		int GetCurState() { return mCurState; }

		void SetAnimation();
		void Shoot();
		void Move();
	private:
		float mSpeed;
		
		Vector2 mGunDir;

		bool mReloading;
		float mShooterCoolTime;
		float mShooterCoolTimeChecker;
		float mShootAnimationTimeChecker;
		UINT mShootPoint;
		eGunType mCurGunType;

		Animator* mAnimator;
		int mCurState;
	};
}
