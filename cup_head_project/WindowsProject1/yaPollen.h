#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class Pollen : public GameObject
	{
	public:

		Pollen(bool pink=false);
		~Pollen();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();

	private:
		float mAliveTime;
		float mAliveTimeChecker;
		float mGoTimeChecker;
		float mSpeed;

		bool mbGoRight;

		Animator* mAnimator;

	};
}
