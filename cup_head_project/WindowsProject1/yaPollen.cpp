#include "yaPollen.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"

namespace ya
{
	Pollen::Pollen(bool pink)
	{
		mPink = pink;
		SetName(L"Pollen");
		SetScale({ 50.0f, 50.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"PinkIdle", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Firing Pollen\\Pollen\\Pollen_A_", 6, 0.03f, false, false);
		mAnimator->CreateAnimation(L"NormalIdle", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Firing Pollen\\Pollen\\Pollen_B_", 6, 0.03f, false, false);

		if (mPink)
			mAnimator->Play(L"PinkIdle", true);
		else
			mAnimator->Play(L"NormalIdle", true);
	}

	Pollen::~Pollen()
	{
	}

	void Pollen::Tick()
	{
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > 10)
			ObjectManager::Destroy(this);

		GameObject::Tick();
		Vector2 pos = GetPos();
		pos.x -= Time::DeltaTime() * 400;
		pos.y += Time::DeltaTime() * 100 * sinf(pos.x / 100);
		SetPos(pos);
		if (mParried)
			ObjectManager::Destroy(this);
	}

	void Pollen::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Pollen::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			ObjectManager::Destroy(this);
		}
	}

	void Pollen::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Pollen::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Pollen::Release()
	{
		mAnimator->Release();

	}

}