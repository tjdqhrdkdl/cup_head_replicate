#include "yaBullet.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaAnimator.h"
namespace ya 
{
	Bullet::Bullet(Vector2 dir)
	{
		mDir = dir;
		mEffect = new ShootEffect();
		Scene* curScene = SceneManager::GetCurScene();
		curScene->AddGameObject(mEffect, eColliderLayer::UI);

		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
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
		if(other->isHitBox())
			mAnimator->Play(L"BulletDeath", false);
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