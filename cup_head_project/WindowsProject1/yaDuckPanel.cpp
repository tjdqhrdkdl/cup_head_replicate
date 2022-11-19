#include "yaDuckPanel.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaObjectManager.h"
#include "yaResources.h"
namespace ya
{
	DuckPanel::DuckPanel(bool pink)
		:mSpeed(200)
		,mAliveTime(10.0f)
		,mPink(pink)
	{
		SetName(L"DuckPannel");
		SetPos({ 1600,385 });
		SetScale({ 100.0f,100.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"Spin", L"..\\Resources\\Image\\Beppi\\Duck\\Yellow\\Spin\\duck_spin_00", 11, 0.05f, false, false);
		mAnimator->CreateAnimation(L"PinkSpin", L"..\\Resources\\Image\\Beppi\\Duck\\Pink\\Spin\\p_duck_spin_00", 11, 0.05f, false, false);

		if(mPink)
			mPicture = Resources::Load<Picture>(L"PinkDuckBasicImage", L"..\\Resources\\Image\\Beppi\\Duck\\Pink\\Spin\\p_duck_spin_0010.png");
		else
			mPicture = Resources::Load<Picture>(L"DuckBasicImage", L"..\\Resources\\Image\\Beppi\\Duck\\Yellow\\Spin\\duck_spin_0010.png");
	}

	DuckPanel::~DuckPanel()
	{
	}

	void DuckPanel::Tick()
	{
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
			ObjectManager::Destroy(this);
		Vector2 pos = GetPos();

		if (pos.y > 385)
			mDown = false;
		else if (pos.y < 250)
			mDown = true;

		pos.x -= mSpeed * Time::DeltaTime();
		if (mDown)
			pos.y += mSpeed * Time::DeltaTime();
		else
			pos.y -= mSpeed * Time::DeltaTime();
		SetPos(pos);
		GameObject::Tick();
	}

	void DuckPanel::Render(HDC hdc)
	{
		Vector2 finalPos = GetPos();
		finalPos.x = finalPos.x - (mPicture->GetWidth() / 2);
		finalPos.y = finalPos.y - (mPicture->GetHeight());
		if (!mSpin)
		{
			TransparentBlt(hdc, finalPos.x, finalPos.y,
				mPicture->GetWidth(), mPicture->GetHeight(),
				mPicture->GetDC(), 0, 0, mPicture->GetWidth(),
				mPicture->GetHeight(), RGB(255, 0, 255));
		}
		GameObject::Render(hdc);
	}

	void DuckPanel::OnCollisonEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player_Projecttile)
		{
			mSpin = true;
			if(mPink)
				mAnimator->Play(L"PinkSpin", true);
			else
				mAnimator->Play(L"Spin", true);
			GetComponent<Collider>()->SetScale({ 0,0 });
		}
	}

	void DuckPanel::OnCollisonStay(Collider* other)
	{
	}

	void DuckPanel::OnCollisonExit(Collider* other)
	{
	}

}