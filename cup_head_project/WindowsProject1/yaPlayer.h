#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"
namespace ya 
{
	class Animator;
	class Player : public GameObject
	{
	public:
		enum ePlayerState
		{
			PlayerState_LookLeft = 0x00000001,
			PlayerState_OnAir = 0x00000002,
			PlayerState_OnHit = 0x00000004,
			PlayerState_CoolShoot = 0x00000008,
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
		std::wstring GetPlayerStrDir();
		std::wstring GetPlayerXDir();

		short GetState() { return mState; }
		void Shoot();
	private:
		float mSpeed;
		
		Vector2 mGunDir;
		float mShooterCoolTime;
		float mShooterCoolTimeChecker;
		UINT mShootPoint;
		eGunType mCurGunType;

		Animator* mAnimator;
		int mState;
	};
}
