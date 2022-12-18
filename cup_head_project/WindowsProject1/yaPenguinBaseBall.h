#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class ShootEffect;
	class BaseBall : public GameObject
	{
	public:

		BaseBall(Vector2 dir);
		~BaseBall();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		ShootEffect* mShootEffect;

		void Release();
	private:
		float mAliveTime;
		float mAliveTimeChecker;
		float mSpeed;
		
		Animator* mAnimator;
		Vector2 mDestDir;

	};
}
