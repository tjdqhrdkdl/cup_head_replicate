#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"
namespace ya 
{
	class Bullet;
	class Animator;
	class Rigidbody;
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
			PlayerState_OnParry		= 0x00002000,

		};
		Player();
		~Player();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void PlusSpecialPointF(float f) { mSpecialPointFloat += f; }

		void PlayerKeyInput();
		void SetShooterCoolTime(eGunType guntype);
		void SetGunDir();
		void SetGunEXDir(); 
		Vector2 SetBulletStartPos(Bullet*);
		Vector2 SetEXBulletStartPos(Bullet*);
		Vector2 GetPrevPos() { return mPrevPos; }
		int GetCurState() { return mCurState; }
		

		bool isFalling() { return mFalling; }
		void SetAnimation();
		void Shoot();
		void Move();
		void Duck();
		void Dash();
		void Jump();
		void EX();
		void Parry();

		void EXCompleteEvent();
	private:
		int mCurState;
		UINT mSpecialPoint;
		float mSpecialPointFloat;


		bool mReloading;
		bool mFalling;
		bool mCanDash;
		bool mCanEX;

		float mSpeed;
		float mShooterCoolTime;
		float mShooterCoolTimeChecker;
		float mShootAnimationTimeChecker;
		float mEXAnimationTimeChecker;
		float mDashTimeChecker;
		float mJumpTimeChecker;

		UINT mShootPoint;
		Vector2 mGunDir;
		Vector2 mPrevPos;
		eGunType mCurGunType;
		Animator* mAnimator;
		Rigidbody* mRigidbody;

	};
}
