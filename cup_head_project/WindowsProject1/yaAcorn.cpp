#include "yaAcorn.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaGround.h"
#include "yaBossCarnationScene.h"
#include "yaPlayer.h"

namespace ya
{
	Acorn::Acorn()
		:mAliveTime(10)
		, mAliveTimeChecker(0)

	{
		SetName(L"Acorn");
		SetScale({ 100.0f, 40.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Rotation", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Acorn\\Rotation\\Acorn_", 9, 0.035f, false, false);
		mAnimator->CreateAnimation(L"Shoot", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Acorn\\Shoot\\Acorn_", 5, 0.03f, false, false);
		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Acorn\\Death\\FX_C_", 7, 0.04f, false, false);

		mAnimator->GetCompleteEvent(L"Death") = std::bind(&Acorn::DeathCompleteEvent, this);
		mAnimator->Play(L"Rotation", true);
	}

	Acorn::~Acorn()
	{
	}

	void Acorn::Tick()
	{
		GameObject::Tick();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
		}
		if (mAnimator->GetPlayAnimation()->GetName() == L"Rotation")
		{
			mRotationTimeChecker += Time::DeltaTime();
			if (mRotationTimeChecker > mShootTime)
			{
				mRotationTimeChecker = 0;
				mAnimator->Play(L"Shoot", true);
				Vector2 plPos = dynamic_cast<BossCarnationScene*>(SceneManager::GetCurScene())->GetScenePlayer()->GetPos();
				mDestDir = (plPos - GetPos()).Normalize();
			}
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"Shoot")
		{
			Vector2 pos = GetPos();
			pos += mDestDir * 600 * Time::DeltaTime();
			SetPos(pos);
		}
	}

	void Acorn::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Acorn::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr
			|| other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			mAnimator->Play(L"Death", false);
			GetComponent<Collider>()->SetOff(true);
		}
	}

	void Acorn::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Acorn::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Acorn::DeathCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void Acorn::Release()
	{
		mAnimator->Release();
	}

}