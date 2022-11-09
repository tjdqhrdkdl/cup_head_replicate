#include "yaBullet.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"

namespace ya 
{
	Bullet::Bullet()
	{

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
	}

	void Bullet::OnCollisonStay(Collider* other)
	{
	}

	void Bullet::OnCollisonExit(Collider* other)
	{
	}
}