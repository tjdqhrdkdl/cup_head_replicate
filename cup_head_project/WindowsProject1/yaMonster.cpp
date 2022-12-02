#include "yaMonster.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaAnimator.h"

ya::Monster::Monster()
{
}

ya::Monster::~Monster()
{
}

void ya::Monster::Tick()
{
	
	OnHitCheck();
	GameObject::Tick();
}

void ya::Monster::Render(HDC hdc)
{
	GameObject::Render(hdc);
}

void ya::Monster::OnHitCheck()
{
	if (onHit)
	{
		onHitChecker += Time::DeltaTime();
		if (onHitChecker > 0.05f)
		{
			onHitChecker = 0;
			onHit = false;
			mAnimator->SetLighten(false);
		}
	}
}



void ya::Monster::OnCollisonEnter(Collider* other, Collider* my)
{
	GameObject* objOther = other->GetOwner();
	if (objOther->GetLayer() == eColliderLayer::Player_Projecttile)
	{
		if (mHp < 0)
			mDead = true;
		onHit = true;
		mAnimator->SetLighten(true);
	}
}
