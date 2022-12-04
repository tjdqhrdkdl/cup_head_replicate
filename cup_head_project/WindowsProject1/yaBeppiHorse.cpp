#include "yaBeppiHorse.h"
#include "yaAnimator.h"

namespace ya
{
	BeppiHorse::BeppiHorse()
		:mbYellow(true)
	{
		mBodyAnimator = new Animator();
		mHeadAnimator = new Animator();
		AddComponent(mBodyAnimator);
		AddComponent(mHeadAnimator);

		mBodyAnimator->SetLightenAnimation(mBodyAnimator->CreateAnimation(L"GreenBodyIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Body\\0_Horse_Body_", 4, 0.05f, true, false)
			, mBodyAnimator->CreateAnimation(L"LightenGreenBodyIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Body\\0_Horse_Body_", 4, 0.05f, true, false));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"GreenHeadIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Head\\0_Horse_Head_", 4, 0.05f, true, false, { -172,-53 })
			, mHeadAnimator->CreateAnimation(L"LightenGreenHeadIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Head\\0_Horse_Head_", 4, 0.05f, true, false, { -172,-53 }));

		mBodyAnimator->SetLightenAnimation(mBodyAnimator->CreateAnimation(L"GreenBodyIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Body\\0_Horse_Body_", 4, 0.05f, true, true)
			, mBodyAnimator->CreateAnimation(L"LightenGreenBodyIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Body\\0_Horse_Body_", 4, 0.05f, true, true));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"GreenHeadIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Head\\0_Horse_Head_", 4, 0.05f, true, true, { 172,-53 })
			, mHeadAnimator->CreateAnimation(L"LightenGreenHeadIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Head\\0_Horse_Head_", 4, 0.05f, true, true, { 172,-53 }));

		mBodyAnimator->SetLightenAnimation(mBodyAnimator->CreateAnimation(L"YellowBodyIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Body\\1_Horse_Body_", 4, 0.05f, true, false,{-20, 0})
			, mBodyAnimator->CreateAnimation(L"LightenYellowBodyIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Body\\1_Horse_Body_", 4, 0.05f, true, false, { -20, 0 }));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"YellowHeadIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Head\\1_Horse_Head_", 4, 0.05f, true, false, { -176,-57 })
			, mHeadAnimator->CreateAnimation(L"LightenYellowHeadIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Head\\1_Horse_Head_", 4, 0.05f, true, false, { -176,-57 }));

		mBodyAnimator->SetLightenAnimation(mBodyAnimator->CreateAnimation(L"YellowBodyIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Body\\1_Horse_Body_", 4, 0.05f, true, true, { 20, 0 })
			, mBodyAnimator->CreateAnimation(L"LightenYellowBodyIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Body\\1_Horse_Body_", 4, 0.05f, true, true, { 20, 0 }));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"YellowHeadIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Idle\\Head\\1_Horse_Head_", 4, 0.05f, true, true, { 176,-57 })
			, mHeadAnimator->CreateAnimation(L"LightenYellowHeadIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Idle\\Head\\1_Horse_Head_", 4, 0.05f, true, true, { 176,-57 }));


		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"GreenHeadAttackLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Attack\\0_Horse_Attack_", 8, 0.02f, true, false, { -180,-25 })
			, mHeadAnimator->CreateAnimation(L"LightenGreenHeadAttackLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Attack\\0_Horse_Attack_", 8, 0.02f, true, false, { -180,-25 }));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"GreenHeadAttackRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Attack\\0_Horse_Attack_", 8, 0.02f, true, true, { 180,-25 })
			, mHeadAnimator->CreateAnimation(L"LightenGreenHeadAttackRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Attack\\0_Horse_Attack_", 8, 0.02f, true, true, { 180,-25 }));

		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"YellowHeadAttackLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Attack\\1_Horse_Attack_", 8, 0.02f, true, false, { -185,-25 })
			, mHeadAnimator->CreateAnimation(L"LightenYellowHeadAttackLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Attack\\1_Horse_Attack_", 8, 0.02f, true, false, { -185,-25 }));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"YellowHeadAttackRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Attack\\1_Horse_Attack_", 8, 0.02f, true, true, { 185,-25 })
			, mHeadAnimator->CreateAnimation(L"LightenYellowHeadAttackRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\Lighten\\Attack\\1_Horse_Attack_", 8, 0.02f, true, true, { 185,-25 }));


		mBodyAnimator->CreateAnimation(L"YellowBodyEndLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\End\\1_Horse_End_", 5, 0.05f, true, false, { -130, 100 });
		mBodyAnimator->CreateAnimation(L"YellowBodyEndRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\End\\1_Horse_End_", 5, 0.05f, true, true, { 130, 100 });
		mBodyAnimator->CreateAnimation(L"GreenBodyEndLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\End\\0_Horse_End_", 5, 0.05f, true, false, { -130, 100 });
		mBodyAnimator->CreateAnimation(L"GreenBodyEndRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horse\\End\\0_Horse_End_", 5, 0.05f, true, true, { 130, 100 });

		mHeadAnimator->GetCompleteEvent(L"GreenHeadAttackLeft") = std::bind(&BeppiHorse::AttackCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"GreenHeadAttackRight") = std::bind(&BeppiHorse::AttackCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"YellowHeadAttackLeft") = std::bind(&BeppiHorse::AttackCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"YellowHeadAttackRight") = std::bind(&BeppiHorse::AttackCompleteEvent, this);




		mBodyAnimator->Play(L"YellowBodyIdleLeft", true);
		mHeadAnimator->Play(L"YellowHeadIdleLeft", true);
		
	
	}

	BeppiHorse::~BeppiHorse()
	{
	}

	void BeppiHorse::Tick()
	{
		GameObject::Tick();
		if (mbDirChanged)
		{
			if (mbRight)
			{
				if (mbYellow)
				{
					mBodyAnimator->Play(L"YellowBodyIdleRight", true);
					mHeadAnimator->Play(L"YellowHeadIdleRight", true);

				}
				else
				{
					mBodyAnimator->Play(L"GreenBodyIdleRight", true);
					mHeadAnimator->Play(L"GreenHeadIdleRight", true);
				}
			}
			else
			{
				if (mbYellow)
				{

					mBodyAnimator->Play(L"YellowBodyIdleLeft", true);
					mHeadAnimator->Play(L"YellowHeadIdleLeft", true);
				}
				else
				{
					mBodyAnimator->Play(L"GreenBodyIdleLeft", true);
					mHeadAnimator->Play(L"GreenHeadIdleLeft", true);
				}
			}
			mbDirChanged = false;
		}
	}

	void BeppiHorse::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BeppiHorse::SetLighten(bool light)
	{
		mBodyAnimator->SetLighten(light), mHeadAnimator->SetLighten(light);
	}

	void BeppiHorse::AttackCompleteEvent()
	{
		if (mbRight)
		{
			if (mbYellow)
				mHeadAnimator->Play(L"YellowHeadIdleRight", true);
			else
				mHeadAnimator->Play(L"GreenHeadIdleRight", true);
		}
		else
		{
			if (mbYellow)
				mHeadAnimator->Play(L"YellowHeadIdleLeft", true);
			else
				mHeadAnimator->Play(L"GreenHeadIdleLeft", true);
		}
	}

}