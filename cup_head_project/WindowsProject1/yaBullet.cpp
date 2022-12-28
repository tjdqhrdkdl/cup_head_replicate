#include "yaBullet.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaSpreader.h"
namespace ya 
{
	Bullet::Bullet(Vector2 dir, bool special)
	{
		mDir = dir;
		mSpecial = special;
		mEffect = new ShootEffect();
		Scene* curScene = SceneManager::GetCurScene();
		curScene->AddGameObject(mEffect, eColliderLayer::Effect);

		AddComponent(new Collider());
		mAnimator = new Animator();
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Tick()
	{
		GameObject::Tick();
	}

	void Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Bullet::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->isHitBox() && !(other->isBulletPassing()))
		{
			if (other->GetOwner()->GetLayer() == eColliderLayer::FrontMonster
				|| other->GetOwner()->GetLayer() == eColliderLayer::BehindMonster)
			{
				Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
				if (monster == nullptr)
					;
				else
				{
					float hp = monster->GetHp();
					hp -= GetDamage();
					monster->SetHp(hp);
					if(!mSpecial)
						mOwner->PlusSpecialPointF(GetDamage() / 100);
				}

			}
			if (!mSpecial)
			{
				mAnimator->Play(L"BulletDeath", false);
				GetComponent<Collider>()->SetOff(true);
			}
		}
	}

	void Bullet::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Bullet::OnCollisonExit(Collider* other, Collider* my)
	{
	}
	
	void Bullet::BulletDeathCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}
}