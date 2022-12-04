#include "yaRightWall.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaCamera.h"
#include "yaRigidbody.h"
#include "yaSceneManager.h"
namespace ya
{
	RightWall::RightWall()
	{
		Collider* collider = new Collider();
		collider->SetHitBox(false);
		AddComponent(collider);
		SetPos({ 1710, 900 });
		SetScale({ 200, 950 });
	}

	RightWall::~RightWall()
	{
	}

	void RightWall::Tick()
	{
		SetPos(Camera::CalculatePos(GetPos()));
		GameObject::Tick();
	}

	void RightWall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RightWall::OnCollisonEnter(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{
			if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
			{
				Player* player = dynamic_cast<Player*>(other->GetOwner());
				Vector2 plPos = player->GetPos();
				plPos.x = 1540;
				player->SetPos(plPos);
			}
		}
	}

	void RightWall::OnCollisonStay(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			plPos.x = 1540;
			player->SetPos(plPos);
		}
		}
	}

	void RightWall::OnCollisonExit(Collider* other, Collider* my)
	{

	}

}