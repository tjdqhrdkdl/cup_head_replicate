#include "yaBeppiPhaseThree.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaHorseShoe.h"
#include "yaRollerCoaster.h"
#include "yaBossBeppiScene.h"
#include "yaBossExplosion.h"
#include "yaSound.h"
#include "yaResources.h"
namespace ya
{
	BeppiPhaseThree::BeppiPhaseThree(bool init)
		:
		 mCoasterTime(14.0f)
		, mCoasterTimeChecker(8.0f)
		, mDeathEffectTimeChecker(0.0f)
	{
		SetName(L"BeppiPhaseThree");
		mHp = 300;
		SetPos({ 1400,-300 });
		SetScale({ 400.0f,400.0f });
		mCollider = new Collider();
		AddComponent(mCollider);
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\0_Phase3_Idle_", 16, 0.04f, true, false, { -50,107 })
			, mAnimator->CreateAnimation(L"LightenIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\Lighten\\0_Phase3_Idle_", 16, 0.04f, true, false, { -50,107 }));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\0_Phase3_Idle_", 16, 0.04f, true, true, { 50,107 })
			, mAnimator->CreateAnimation(L"LightenIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Idle\\Lighten\\0_Phase3_Idle_", 16, 0.04f, true, true, { 50,107 }));

		mAnimator->CreateAnimation(L"EndIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\End\\Death_Front_a\\clown_horse_death_a_00", 6, 0.05f, false, false, { 20, 330 });
		mAnimator->CreateAnimation(L"EndIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\End\\Death_Front_a\\clown_horse_death_a_00", 6, 0.05f, false, true, { -20, 330 });

		mAnimator->CreateAnimation(L"EndDrop", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\End\\Death_Front_b\\clown_horse_death_b_00", 20, 0.08f, false, false, { 20, 500 });
	
		mAnimator->GetCompleteEvent(L"EndDrop") = std::bind(&BeppiPhaseThree::EndDropCompleteEvent, this);
		if (init)
		{
			BeppiHorse();
			BeppiPhaseThreeBack();
		}
		else
		{
			mBackAnimation = new BeppiPhaseThreeBack();
			mBackAnimation->SetPos(GetPos());
			SceneManager::GetCurScene()->AddGameObject(mBackAnimation, eColliderLayer::FrontMonster);

			mHorse = new BeppiHorse();
			mHorse->SetPos(GetPos());
			SceneManager::GetCurScene()->AddGameObject(mHorse, eColliderLayer::FrontMonster);


		}
		mAnimator->Play(L"IdleLeft", true);
		mbGoDown = true;
		mbYellowHorse = true;
		for (size_t i = 0; i < 3; i++)
		{
			mYellowShoeBlankIndex[i] = rand() % 13;
			for (size_t l = 0; l < i + 1; l++)
			{
				if (mYellowShoeBlankIndex[l] == mYellowShoeBlankIndex[i])
				{
					if (mYellowShoeBlankIndex[i]++ == 12)
					{
						mYellowShoeBlankIndex[i] = 5;
					}
				}
			}
		}
		mWarningSound = Resources::Load<Sound>(L"CoasterBell", L"..\\Resources\\Sound\\Clown\\sfx_level_clown_warning_lights_loop_01.wav");

		HorseShoe(true, true, true);
	}

	BeppiPhaseThree::~BeppiPhaseThree()
	{
	}

	void BeppiPhaseThree::Tick()
	{
		Monster::Tick();
		if (!mbEndFall)
		{
			mHorse->SetPos(GetPos());
		}
		else
		{
			Vector2 pos = mHorse->GetPos();
			pos.y -= 400 * Time::DeltaTime();
			mHorse->SetPos(pos);
		}
		mBackAnimation->SetPos(GetPos());

		PatternChoice();
		Move();
		Attack();
		SummonCoaster();

		if (!mbEndFall && IsDeathTimeOn())
		{
			mDeathEffectTimeChecker += Time::DeltaTime();
			if (mDeathEffectTimeChecker > 0.4f + (rand()%5)*0.1)
			{
				mDeathEffectTimeChecker = 0;
				Vector2 pos = GetPos();
				switch (rand() % 6)
				{
				case 0:
					pos += {60, 120};
					break;
				case 1:
					pos += {-150, 30};
					break;
				case 2:
					pos += {100, 50};
					break;
				case 3:
					pos += {-10, 250};
					break;
				case 4:
					pos += {-70, 40};
					break;
				case 5:
					pos += {100, 200};
					break;
				}

				BossExplosion* effect = ObjectManager::Instantiate<BossExplosion>(SceneManager::GetCurScene(), eColliderLayer::Effect);
				if (soundPlay == false)
				{
					soundPlay = true;
					effect->SoundPlay();
				}
				effect->SetPos(pos);
			}
		}
	}

	void BeppiPhaseThree::Render(HDC hdc)
	{
		Monster::Render(hdc);		
		if (mAnimator->isLighten())
		{
			mBackAnimation->GetAnimator()->SetLighten(true);
			mHorse->SetLighten(true);
		}
		else
		{
			mBackAnimation->GetAnimator()->SetLighten(false);
			mHorse->SetLighten(false);
		}
	}

	void BeppiPhaseThree::PatternChoice()
	{
		Vector2 pos = GetPos();
		if (mbGoUp && pos.y < -300 && !IsDeathTimeOn())
		{
			switch (rand() % 4)
			{
			case 0:
				mbYellowHorse = true;
				mbRight = true;
				break;
			case 1:
				mbYellowHorse = false;
				mbRight = true;
				break;
			case 2:
				mbYellowHorse = true;
				mbRight = false;
				break;
			case 3:
				mbYellowHorse = false;
				mbRight = false;
				break;
			}

			if (mbYellowHorse)
				mHorse->ChoiceYellow(true);
			else
				mHorse->ChoiceYellow(false);


			if (mbRight)
			{
				mAnimator->Play(L"IdleRight", true);
				pos.x = 200;


				mBackAnimation->GetAnimator()->Play(L"IdleRight", true);
				mHorse->ChoiceRight(true);
			}
			else
			{
				mAnimator->Play(L"IdleLeft", true);
				pos.x = 1400;


				mBackAnimation->GetAnimator()->Play(L"IdleLeft", true);
				mHorse->ChoiceRight(false);
			}

			SetPos(pos);
			mbGoUp = false;
			mbGoDown = true;
			for (size_t i = 0; i < 3; i++)
			{
				mYellowShoeBlankIndex[i] = rand() % 13;
				for (size_t l = 0; l < i + 1; l++)
				{
					if (mYellowShoeBlankIndex[l] == mYellowShoeBlankIndex[i])
					{
						if (mYellowShoeBlankIndex[i]++ == 12)
						{
							mYellowShoeBlankIndex[i] = 5;
						}
					}
				}
			}
		}
	}

	void BeppiPhaseThree::Move()
	{
		Vector2 pos = GetPos();
		if (mbEndFall)
		{
			pos.y += 400 * Time::DeltaTime();
			pos.x -= 100 * Time::DeltaTime();
		}
		else if (mbGoDown)
		{
			pos.y += 400 * Time::DeltaTime();
			if (IsDeathTimeOn())
				if (pos.y > 350)
				{
					mbGoDown = false;
					mAnimator->Play(L"EndDrop", false);
					mBackAnimation->GetAnimator()->Play(L"EndDrop", false);
				}
			if (pos.y > 500)
			{
				pos.y = 500;
				mbGoDown = false;
			}
		}
		else if (mbGoUp)
		{
			if (IsDeathTimeOn() && GetDeathTime() < 19)
			{
				pos.y -= 400 * Time::DeltaTime();
				if (GetDeathTime() < 15)
				{
					pos.x = 900;
					mbGoUp = false;
					mbGoDown = true;
					mAnimator->Play(L"EndIdleLeft", true);
					mBackAnimation->GetAnimator()->Play(L"EndIdleLeft", true);
					if (mbYellowHorse)
						mHorse->GetBodyAnimator()->Play(L"YellowBodyEndLeft", true);
					else
						mHorse->GetBodyAnimator()->Play(L"GreenBodyEndLeft", true);
				}
			}
			else if (IsDeathTimeOn())
				;
			else
				pos.y -= 400 * Time::DeltaTime();

		}
		SetPos(pos);
	}

	void BeppiPhaseThree::Attack()
	{
		Vector2 pos = GetPos();
		if (!mbGoDown && !mbGoUp && !IsDeathTimeOn())
		{
			mAttackTimeChecker += Time::DeltaTime();
			if (mbYellowHorse)
			{
				mShoeTimeChecker += Time::DeltaTime();
				if (mShoeTimeChecker > 0.15f && mShoeCounter < 10)
				{
					mShoeTimeChecker = 0;
					bool shoot = true;
					for (size_t i = 0; i < 3; i++)
					{
						if (mShoeCounter == mYellowShoeBlankIndex[i])
						{
							shoot = false;
							++mShoeCounter;
						}
					}
					if (shoot)
					{
						HorseShoe* shoeYellow = new HorseShoe(mbYellowHorse, mbRight);
						pos.y -= 100;
						if (mbRight)
						{
							pos.x += 300;
							mHorse->GetHeadAnimator()->Play(L"YellowHeadAttackRight", false);
							shoeYellow->SetStopXPos(pos.x + mShoeCounter++ * 120);
						}
						else
						{
							pos.x -= 300;
							mHorse->GetHeadAnimator()->Play(L"YellowHeadAttackLeft", false);
							shoeYellow->SetStopXPos(pos.x - mShoeCounter++ * 120);
						}
						shoeYellow->SetPos(pos);
						shoeYellow->SetBeppi(this);
						SceneManager::GetCurScene()->AddGameObject(shoeYellow, eColliderLayer::Monster_Projecttile);
					}
				}
				if (mAttackTimeChecker > 4.0f && !mbYellowDrop)
				{
					mbYellowDrop = true;
				}
				if (mAttackTimeChecker > 6.0f)
				{
					mAttackTimeChecker = 0;
					mShoeCounter = 0;
					mbYellowDrop = false;
					mbGoUp = true;
				}
			}

			else
			{
				mGreenShoeSetTimeChecker += Time::DeltaTime();
				mShoeTimeChecker += Time::DeltaTime();
				if (mShoeTimeChecker > 0.15f && mShoeCounter < 2)
				{
					mShoeTimeChecker = 0;

					HorseShoe* shoeGreen = new HorseShoe(mbYellowHorse, mbRight);
					pos.y -= 100;
					if (mbRight)
					{
						pos.x += 300;
						mHorse->GetHeadAnimator()->Play(L"GreenHeadAttackRight", false);
					}
					else
					{
						pos.x -= 300;
						mHorse->GetHeadAnimator()->Play(L"GreenHeadAttackLeft", false);
					}

					shoeGreen->SetPos(pos);
					shoeGreen->SetBeppi(this);

					SceneManager::GetCurScene()->AddGameObject(shoeGreen, eColliderLayer::Monster_Projecttile);
					++mShoeCounter;
				}
				if (mGreenShoeSetTimeChecker > 3 && mGreenShoeSetCounter < 2)
				{
					mGreenShoeSetTimeChecker = 0;
					mShoeCounter = 0;
					++mGreenShoeSetCounter;
				}
				if (mAttackTimeChecker > 11)
				{
					mAttackTimeChecker = 0;
					mGreenShoeSetTimeChecker = 0;
					mGreenShoeSetCounter = 0;
					mShoeTimeChecker = 0;
					mShoeCounter = 0;
					mbYellowDrop = false;
					mbGoUp = true;
				}
			}

		}
	}

	void BeppiPhaseThree::SummonCoaster()
	{
		mCoasterTimeChecker += Time::DeltaTime();		
		if (mCoasterTimeChecker > mCoasterTime - 0.6f)
		{
			if(!IsDeathTimeOn())
				mWarningSound->Play(false);
		}
		if (mCoasterTimeChecker > mCoasterTime && !IsDeathTimeOn())
		{
			mCoasterTimeChecker = 0;
			RollerCoaster* coaster = new RollerCoaster(10);
			coaster->Initialize();
			SceneManager::GetCurScene()->AddGameObject(coaster, eColliderLayer::FrontObject);
		}
	}

	void BeppiPhaseThree::EndDropCompleteEvent()
	{
		mbEndFall = true;
		ObjectManager::Destroy(mHorse, 15.0f);
		ObjectManager::Destroy(mBackAnimation, 15.0f);

		dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->SetPhase(4);
	}

	void BeppiPhaseThree::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
		if (mDead && !IsDeathTimeOn() && !mbGoDown && !mbGoUp)
		{
			if(mbRight)
			{
				mAnimator->Play(L"EndIdleRight", true);
				mBackAnimation->GetAnimator()->Play(L"EndIdleRight", true);
				if (mbYellowHorse)
					mHorse->GetBodyAnimator()->Play(L"YellowBodyEndRight", true);
				else
					mHorse->GetBodyAnimator()->Play(L"GreenBodyEndRight", true);
			}
			else
			{
				mAnimator->Play(L"EndIdleLeft", true);
				mBackAnimation->GetAnimator()->Play(L"EndIdleLeft", true);
				if (mbYellowHorse)
					mHorse->GetBodyAnimator()->Play(L"YellowBodyEndLeft", true);
				else
					mHorse->GetBodyAnimator()->Play(L"GreenBodyEndLeft", true);
			}
			mHorse->GetHeadAnimator()->SetPlayAnimation(nullptr);
			ObjectManager::Destroy(this, 22.0f);
			mbGoUp = true;
			mCollider->SetOff(true);
			mbYellowDrop = true;
			dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->SetPhase(4);
			mWarningSound->Stop(true);
		}
	}

	void BeppiPhaseThree::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseThree::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseThree::Release()
	{
		mAnimator->Release();
		BeppiPhaseThreeBack().Release();
		BeppiHorse().Release();
		HorseShoe(0,0,0).Release();
	}



}