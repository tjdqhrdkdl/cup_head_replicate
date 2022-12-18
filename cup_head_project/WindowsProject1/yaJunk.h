#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class Junk : public GameObject
	{
	public:

		Junk(bool right, bool pink = false);
		~Junk();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetDestDir(Vector2 dir) { mDestDir = dir; }

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();
	private:
		float mAliveTime;
		float mAliveTimeChecker;
		float mSpeed;

		Animator* mAnimator;
		Vector2 mDestDir;

	};
}
