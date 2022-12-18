#pragma once
#include "Common.h"
#include "yaMonster.h"
namespace ya
{
	class BeppiPhaseThreeBack : public Monster
	{
	public:
		BeppiPhaseThreeBack();
		~BeppiPhaseThreeBack();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		Animator* GetAnimator() { return mAnimator; }

		
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();
	private:
	};
}
