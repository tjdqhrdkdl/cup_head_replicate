#include "yaPeakingCat.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaWernerWermanPh3.h"

namespace ya
{
	PeakingCat::PeakingCat(Vector2 startPos, Vector2 destPos)
	{
		mbGoPeak = true;
		mStartPos = startPos;
		mDestPos = destPos;
		SetName(L"PeakingCat");
		SetPos(startPos);

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"PeakingCat", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Peaking\\cat_bg_peaking_00", 26, 0.1f, false, false);
		mAnimator->CreateAnimation(L"CatIntro", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Intro\\IntroBack\\cat_intro_00", 10, 0.05f, false, false);

		mAnimator->GetCompleteEvent(L"CatIntro") = std::bind(&PeakingCat::CatIntroCompleteEvent, this);
		mAnimator->Play(L"PeakingCat", true);
	}

	PeakingCat::~PeakingCat()
	{
	}

	void PeakingCat::Tick()
	{
		if (!mbPhase3)
		{
			if (mbOn)
			{
				Vector2 pos = GetPos();
				if (mbGoPeak && !mbArrive)
				{
					Vector2 dir = mDestPos - mStartPos;
					dir.Normalize();
					pos += dir * 700 * Time::DeltaTime();
					if (mDestPos.x > mStartPos.x)
					{
						if (pos.x > mDestPos.x)
						{
							mbArrive = true;
							pos = mDestPos;
						}
					}
					else
					{
						if (pos.x < mDestPos.x)
						{
							mbArrive = true;
							pos = mDestPos;

						}
					}
				}
				else if (mbGoPeak && mbArrive)
				{
					mTime += Time::DeltaTime();
					if (mTime > 2)
					{
						mbGoPeak = false;
						mTime = 0;
					}
				}
				else if (!mbGoPeak)
				{
					if (mTime < 2)
					{
						Vector2 dir = mDestPos - mStartPos;
						dir.Normalize();
						pos -= dir * 700 * Time::DeltaTime();
						mTime += Time::DeltaTime();
					}
				}
				SetPos(pos);
				GameObject::Tick();
			}
		}
		else
			GameObject::Tick();

		if (mbPhase3 && mAnimator->GetPlayAnimation()->GetName() != L"CatIntro")
		{
			SetPos({800,800});
			mAnimator->Play(L"CatIntro", false);
		}
	}

	void PeakingCat::Render(HDC hdc)
	{
		if (!mbPhase3)
		{
			if (mbOn)
				GameObject::Render(hdc);
		}
		else
		{
			GameObject::Render(hdc);
		}
	}

	void PeakingCat::Reset(Vector2 startPos, Vector2 destPos)
	{
		mStartPos = startPos;
		mDestPos = destPos;
		SetPos(mStartPos);
		mbGoPeak = true;
		mbArrive = false;
		mbOn = true;
		mTime = 0;
	}

	void PeakingCat::CatIntroCompleteEvent()
	{
		ObjectManager::Destroy(this);
		WernerWermanPh3* phase3 = ObjectManager::Instantiate<WernerWermanPh3>(SceneManager::GetCurScene(), eColliderLayer::FrontMonster);
		phase3->SetPhase2Object(mPhase2Object);
	}

	void PeakingCat::Release()
	{
		mAnimator->Release();
	}


}