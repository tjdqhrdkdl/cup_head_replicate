#include "yaLightBulb.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaResources.h"
namespace ya
{
	LightBulb::LightBulb()
		:mHang(true)
	{
		SetName(L"LightBulb");
		SetPos({ 1635,405 });
		SetScale({ 50.0f,50.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"Drop", L"..\\Resources\\Image\\Beppi\\lightbulb\\Drop\\lightbulb_drop_00", 13, 0.03f, false, false);
		mAnimator->CreateAnimation(L"Explode", L"..\\Resources\\Image\\Beppi\\lightbulb\\Explode\\lightbulb_explode_00", 23, 0.03f, false, false);

		mAnimator->GetCompleteEvent(L"Explode") = std::bind(&LightBulb::ExplodeEndEvent, this);
		mPicture = Resources::Load<Picture>(L"BulbBasicImage", L"..\\Resources\\Image\\Beppi\\lightbulb\\Drop\\lightbulb_drop_0001.png");
	}

	LightBulb::~LightBulb()
	{
	}

	void LightBulb::Tick()
	{
		if (!mHang && !mExploded)
		{
			Vector2 pos = GetPos();
			pos.y += 500 * Time::DeltaTime();
			SetPos(pos);
		}
		GameObject::Tick();
	}

	void LightBulb::Render(HDC hdc)
	{
		Vector2 finalPos = GetPos();
		finalPos.x = finalPos.x - (mPicture->GetWidth() / 2);
		finalPos.y = finalPos.y - (mPicture->GetHeight());
		if (mHang)
		{
			TransparentBlt(hdc, finalPos.x, finalPos.y,
				mPicture->GetWidth(), mPicture->GetHeight(),
				mPicture->GetDC(), 0, 0, mPicture->GetWidth(),
				mPicture->GetHeight(), RGB(255, 0, 255));
		}

		GameObject::Render(hdc);
	}

	void LightBulb::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::FrontObject)
		{
			mAnimator->Play(L"Explode", false);
			mExploded = true;
			Vector2 pos = GetPos();
			pos.y = 700;
			SetPos(pos);
		}
	}

	void LightBulb::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void LightBulb::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void LightBulb::ExplodeEndEvent()
	{
		ObjectManager::Destroy(this);
	}

}