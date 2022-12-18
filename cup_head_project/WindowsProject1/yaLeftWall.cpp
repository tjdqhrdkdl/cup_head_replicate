#include "yaLeftWall.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaCamera.h"
#include "yaRigidbody.h"
#include "yaSceneManager.h"
namespace ya
{
	LeftWall::LeftWall()
	{
		Collider* collider = new Collider();
		collider->SetHitBox(false);
		AddComponent(collider);
		SetPos({ -105, 900 });
		SetScale({ 200, 950 });
	}

	LeftWall::~LeftWall()
	{
	}

	void LeftWall::Tick()
	{
		SetPos(Camera::CalculatePos(GetPos()));
		GameObject::Tick();
	}

	void LeftWall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LeftWall::OnCollisonEnter(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{
			if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
			{
				Player* player = dynamic_cast<Player*>(other->GetOwner());
				Vector2 plPos = player->GetPos();
				plPos.x = GetPos().x + GetScale().x * 0.5 + 1 + player->GetScale().x * 0.5;
				player->SetPos(plPos);
			}
		}
	}

	void LeftWall::OnCollisonStay(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{
			if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
			{
				Player* player = dynamic_cast<Player*>(other->GetOwner());
				Vector2 plPos = player->GetPos();
				plPos.x = GetPos().x + GetScale().x * 0.5 + 1 + player->GetScale().x * 0.5;
				player->SetPos(plPos);
			}
		}
	}

	void LeftWall::OnCollisonExit(Collider* other, Collider* my)
	{

	}

}