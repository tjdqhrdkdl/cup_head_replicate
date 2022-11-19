#include "yaGround.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaCamera.h"
#include "yaRigidbody.h"
namespace ya
{
	Ground::Ground()
		:mPlayer(nullptr)
	{
		AddComponent(new Collider());
		SetPos({ 800, 700 });
		SetScale({ 1700, 5 });
	}

	Ground::~Ground()
	{
	}

	void Ground::Tick()
	{
		SetPos(Camera::CalculatePos(GetPos()));
		GameObject::Tick();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisonEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Vector2 plPos = player->GetPos();
		Vector2 plPrevPos = player->GetPrevPos();
		Vector2 gPos = GetPos();
		Vector2 gScale = GetScale();
		if (player->isFalling())
		{
			dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(true);
			mPlayer = player;
		}
	}

	void Ground::OnCollisonStay(Collider* other)
	{
	}

	void Ground::OnCollisonExit(Collider* other)
	{

	}

}