#include "yaPh2WallGround.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaCamera.h"
#include "yaRigidbody.h"
#include "yaInput.h"
#include "yaCollisionManager.h"
namespace ya
{
	Ph2WallGround::Ph2WallGround()
	{
		Collider* col = new Collider();
		col->SetBulletPassing(true);
		AddComponent(col);
		SetPos({ 820, 450 });
		SetScale({ 1250, 50 });
	}

	Ph2WallGround::~Ph2WallGround()
	{
	}

	void Ph2WallGround::Tick()
	{
		GameObject::Tick();
	}

	void Ph2WallGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ph2WallGround::FreePlayers()
	{
		for (size_t i = 0; i < mOnPlayer.size(); i++)
		{
			Rigidbody* plRbody = dynamic_cast<Rigidbody*>(mOnPlayer[i]->GetComponent(eComponentType::Rigidbody));
			plRbody->SetGround(false);
		}
	}

	void Ph2WallGround::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			Rigidbody* plRbody = dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody));
			if (player->GetJumpCollider() == other
				&& plRbody->GetVelocity().y > 0)
			{
				dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(true);
				plPos.y = GetPos().y - GetScale().y;
				player->SetPos(plPos);
				mOnPlayer.push_back(player);
			}

			else if (player->GetJumpCollider() == other
				&& plRbody->GetVelocity().y <= 0)
			{
				CollisionId id = {};
				id.left = my->GetId();
				id.right = other->GetId();
				std::map<UINT64, bool>::iterator iter = CollisionManager::GetCollisionInfo()->find(id.ID);
				iter->second = false;

			}
		}
	}

	void Ph2WallGround::OnCollisonStay(Collider* other, Collider* my)
	{

		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player->GetComponent<Collider>()->GetScale() == Vector2(90.0f, 60.0f))
			{
				if (KEY_DOWN(eKeyCode::Z))
				{
					dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(false);
				}
			}
		}
	}

	void Ph2WallGround::OnCollisonExit(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player->GetJumpCollider() == other)
			{
				for (size_t i = 0; i < mOnPlayer.size(); i++)
				{
					if (mOnPlayer[i] == player)
					{
						mOnPlayer.erase(mOnPlayer.begin() + i);
						dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(false);
						break;
					}
				}
			}
		}
	}

}