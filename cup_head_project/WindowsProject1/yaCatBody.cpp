#include "yaCatBody.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"

namespace ya
{
	CatBody::CatBody()
	{
		SetName(L"CatBody");
		SetPos({ 780,650 });
		mLeftArmAnimator = new Animator();
		mRightArmAnimator = new Animator();
		mBodyAnimator = new Animator();
		mTailAnimator = new Animator();

		AddComponent(mTailAnimator);
		AddComponent(mBodyAnimator);
		AddComponent(mLeftArmAnimator);
		AddComponent(mRightArmAnimator);

		mBodyAnimator->CreateAnimation(L"BodyIdle", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Body\\cat_idle_body_00", 6, 0.1f, false, false);
		mBodyAnimator->CreateAnimation(L"BodyDeath", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Death\\cat_death_body_00", 4, 0.06f, false, false);

		mTailAnimator->CreateAnimation(L"TailIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Tail\\cat_idle_tail_00", 17, 0.05f, false, false);
		mTailAnimator->CreateAnimation(L"TailIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Tail\\cat_idle_tail_00", 17, 0.05f, false, true);

		mLeftArmAnimator->CreateAnimation(L"LeftArmIdle", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Left Arm\\cat_idle_left_arm_00", 6, 0.1f, false, false);

		mRightArmAnimator->CreateAnimation(L"RightArmIdle", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Right Arm\\cat_idle_right_arm_00", 6, 0.1f, false, false);

		mTailAnimator->GetCompleteEvent(L"TailIdleRight") = std::bind(&CatBody::TailIdleComplete, this);
		mTailAnimator->GetCompleteEvent(L"TailIdleLeft") = std::bind(&CatBody::TailIdleComplete, this);

		mRightArmAnimator->Play(L"RightArmIdle", true);
		mLeftArmAnimator->Play(L"LeftArmIdle", true);
		mTailAnimator->Play(L"TailIdleLeft", true);
		mBodyAnimator->Play(L"BodyIdle", true);

		mRightArmAnimator->SetAddPos({ 125,0 });
		mLeftArmAnimator->SetAddPos({-125,0 });
		mTailAnimator->SetAddPos({ 250,-350 });
		mBodyAnimator->SetAddPos({ 0,0 });
	}

	CatBody::~CatBody()
	{
	}

	void CatBody::Tick()
	{
		GameObject::Tick();
		if (mBodyAnimator->GetPlayAnimation()->GetName() != L"BodyDeath") {
			if (mTailAnimator->GetPlayAnimation()->GetIndex() == 5)
			{
				Vector2 pos = mTailAnimator->GetAddPos();
				pos.x = 0;
				mTailAnimator->SetAddPos(pos);
			}
			if (mTailAnimator->GetPlayAnimation()->GetIndex() == 6)
			{
				Vector2 pos = mTailAnimator->GetAddPos();
				if (mTailAnimator->GetPlayAnimation()->GetName() == L"TailIdleRight")
					pos.x = 250;
				else
					pos.x = -250;
				mTailAnimator->SetAddPos(pos);
			}
		}
	}

	void CatBody::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void CatBody::SetDeath()
	{
		mLeftArmAnimator->SetPlayAnimation(nullptr);
		mRightArmAnimator->SetPlayAnimation(nullptr);
		mTailAnimator->SetPlayAnimation(nullptr);
		mBodyAnimator->Play(L"BodyDeath", true);

	}

	void CatBody::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void CatBody::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void CatBody::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void CatBody::TailIdleComplete()
	{
		if (mTailAnimator->GetPlayAnimation()->GetName() == L"TailIdleLeft")
			mTailAnimator->Play(L"TailIdleRight",false);
		else
			mTailAnimator->Play(L"TailIdleLeft", false);

	}

	void CatBody::Release()
	{
		mLeftArmAnimator->Release();
		mRightArmAnimator->Release();
		mBodyAnimator->Release();
		mTailAnimator->Release();


	}

}