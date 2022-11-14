#include "yaBullet.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
namespace ya 
{
	Bullet::Bullet(Vector2 dir)
	{
		mDir = dir;
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

	void Bullet::OnCollisonEnter(Collider* other)
	{
		ObjectManager::Destroy(this);
		other->OnCollisionExit(this->GetComponent<Collider>());
	}

	void Bullet::OnCollisonStay(Collider* other)
	{
	}

	void Bullet::OnCollisonExit(Collider* other)
	{
	}
}