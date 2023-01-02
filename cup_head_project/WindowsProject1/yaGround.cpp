#include "yaGround.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaCamera.h"
#include "yaRigidbody.h"
namespace ya
{
	Ground::Ground()
	{
		AddComponent(new Collider());
		SetPos({ 800, 900 });
		SetScale({ 1700, 200 });
	}

	Ground::~Ground()
	{
	}

	void Ground::Tick()
	{
		GameObject::Tick();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			if (player->isFalling())
			{
				dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(true);
				plPos.y = GetPos().y - GetScale().y;
				player->SetPos(plPos);
			}
		}
	}

	void Ground::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Ground::OnCollisonExit(Collider* other, Collider* my)
	{

	}

}