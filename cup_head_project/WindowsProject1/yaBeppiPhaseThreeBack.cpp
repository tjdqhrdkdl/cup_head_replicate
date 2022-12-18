#include "yaBeppiPhaseThreeBack.h"
#include "yaAnimator.h"
#include "yaCollider.h"
namespace ya
{
	BeppiPhaseThreeBack::BeppiPhaseThreeBack()
	{
		SetName(L"BeppiPhaseThreeBack");
		mHp = 200;		
		SetScale({ 400.0f,400.0f });

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\1_Phase3_Idle_", 16, 0.04f, true, false, { -50,107 })
			, mAnimator->CreateAnimation(L"LightenIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\Lighten\\1_Phase3_Idle_", 16, 0.04f, true, false, { -50,107 }));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\1_Phase3_Idle_", 16, 0.04f, true, true, { 50,107 })
			, mAnimator->CreateAnimation(L"LightenIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\Lighten\\1_Phase3_Idle_", 16, 0.04f, true, true, { 50,107 }));

		
		mAnimator->CreateAnimation(L"EndIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\End\\Death_Back_a\\clown_horse_death_a_bottom_00", 6, 0.05f, false, false, { 25,300 });
		mAnimator->CreateAnimation(L"EndIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\End\\Death_Back_a\\clown_horse_death_a_bottom_00", 6, 0.05f, false, true, { -25,300 });

		mAnimator->CreateAnimation(L"EndDrop", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\End\\Death_Back_b\\clown_horse_death_b_bottom_00", 20, 0.08f, false, false, { 20, 500 });

		mAnimator->Play(L"IdleLeft", true);
	}

	BeppiPhaseThreeBack::~BeppiPhaseThreeBack()
	{
	}

	void BeppiPhaseThreeBack::Tick()
	{
		GameObject::Tick();
	}

	void BeppiPhaseThreeBack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BeppiPhaseThreeBack::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseThreeBack::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseThreeBack::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseThreeBack::Release()
	{
		mAnimator->Release();
	}

}