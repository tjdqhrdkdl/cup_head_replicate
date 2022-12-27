#include "yaBottomWoodCart.h"
#include "yaTime.h"
#include "yaObjectManager.h"
#include "yaSceneManager.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"

namespace ya
{
	BottomWoodCart::BottomWoodCart()
	{
		SetName(L"BottomWoodCart");
		SetPos({ 800,800 });
		SetScale({ 250.0f,80.0f });
		mGroundCollider = new Collider();
		AddComponent(mGroundCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);
	}

	BottomWoodCart::~BottomWoodCart()
	{
	}

	void BottomWoodCart::Tick()
	{
		GameObject::Tick();

	}

	void BottomWoodCart::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BottomWoodCart::Move(Vector2 pos)
	{
		for (size_t i = 0; i < mOnPlayer.size(); i++)
		{
			Vector2 pPos = mOnPlayer[i]->GetPos();
			pPos.x += pos.x - GetPos().x;
			mOnPlayer[i]->SetPos(pPos);
		}
		SetPos(pos);
	}

	void BottomWoodCart::OnCollisonEnter(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			Rigidbody* plRbody = dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody));
			if (player->GetJumpCollider() == other
				&& plRbody->GetVelocity().y > 0)
			{
				plRbody->SetGround(true);
				plPos.y = GetPos().y - GetScale().y + 1;
				player->SetPos(plPos);
				mOnPlayer.push_back(player);
			}
		}

		if (!(curscene->isIntro()))
		{
			if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
			{
				Player* player = dynamic_cast<Player*>(other->GetOwner());
				Vector2 plPos = player->GetPos();
				Rigidbody* plRbody = dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody));
				bool go = true;
				for (size_t i = 0; i < mOnPlayer.size(); i++)
				{
					if (mOnPlayer[i] == player)
						go = false;
				}
				if (go && plRbody->GetVelocity().y <= 0)
				{
					if(plPos.x < GetPos().x)
						plPos.x = GetPos().x - GetScale().x * 0.5 - 1 - player->GetScale().x *0.5;
					else
						plPos.x = GetPos().x + GetScale().x * 0.5 + 1 + player->GetScale().x * 0.5;
					player->SetPos(plPos);
				}
			}
		}
	}

	void BottomWoodCart::OnCollisonStay(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{
			if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
			{
				Player* player = dynamic_cast<Player*>(other->GetOwner());
				Vector2 plPos = player->GetPos();
				Rigidbody* plRbody = dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody));
				bool go = true;
				for (size_t i = 0; i < mOnPlayer.size(); i++)
				{
					if (mOnPlayer[i] == player)
						go = false;
				}
				if (go&& plRbody->GetVelocity().y <= 0)
				{
					if (plPos.x < GetPos().x)
						plPos.x = GetPos().x - GetScale().x * 0.5 - 1 - player->GetScale().x * 0.5;
					else
						plPos.x = GetPos().x + GetScale().x * 0.5 + 1 + player->GetScale().x * 0.5;
					player->SetPos(plPos);
				}
			}
		}

	}

	void BottomWoodCart::OnCollisonExit(Collider* other, Collider* my)
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

	void BottomWoodCart::Release()
	{
		mAnimator->Release();
	}

}