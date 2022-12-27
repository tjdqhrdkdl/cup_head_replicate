#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya
{

	class Animator;
	class WorldPlayer : public GameObject
	{
	public:

		WorldPlayer();
		~WorldPlayer();
		enum eWordPlayerState
		{
			WordPlayerState_None = 0x00000000,
			WordPlayerState_Input_Left = 0x00000001,
			WordPlayerState_Input_Right = 0x00000002,
			WordPlayerState_Input_Up = 0x00000004,
			WordPlayerState_Input_Down = 0x00000008,

		};
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void KeyInput();
		void SetAnimation();
		void Move();

		Vector2 GetBeforePos() { return mBeforePos; }
		void SetBeforePos(Vector2 pos) { mBeforePos = pos; }
		bool GetIsMoving() { return (mCurState != 0); }
		GameObject* GetEnterObject() { return mEnterBossObject; }

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


		void Release();
	private:
		float mSpeed;

		int mCurState;
		Animator* mAnimator;

		Picture* mBoxPicture;

		bool mbEnter;
		GameObject* mEnterBossObject;
		Vector2 mBeforePos;

	};
}
