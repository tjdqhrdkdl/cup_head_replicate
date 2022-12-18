#include "yaSwingPlatform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaObjectManager.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaInput.h"
namespace ya
{
	SwingPlatForm::SwingPlatForm(bool isStart)
	{
		mbStart = isStart;
		
		SetName(L"BeppiSwing");
		SetPos({ -50,400 });
		SetScale({ 150,60 });
		mCollider = new Collider();
		mCollider->SetHitBox(false);
		AddComponent(mCollider);
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Swing\\Swing_Rope_", 3, 0.08f, true, false, {100,30});

		mAnimator->Play(L"Idle", true);
	}

	SwingPlatForm::~SwingPlatForm()
	{
	}

	void SwingPlatForm::Tick()
	{
		GameObject::Tick();
		Vector2 pos = GetPos();
		pos.x += 400 * Time::DeltaTime();
		for (size_t i = 0; i < mOnPlayer.size(); i++)
		{
			if (mOnPlayer[i] != nullptr)
			{
				Vector2 plPos = mOnPlayer[i]->GetPos();
				plPos.x += 400 * Time::DeltaTime();
				mOnPlayer[i]->SetPos(plPos);
			}
		}
		if (pos.y < 400)
		{
			pos.y += 200 * Time::DeltaTime();
		}
		else if (pos.x < 800)
		{
			if (pos.y <  0.125*pos.x + 400)
				pos.y += 100 * Time::DeltaTime();

			else
				pos.y = 0.125*pos.x + 400;
		}
		else if(pos.x < 1300)
		{
			if (pos.y < 500)
				pos.y += 100 * Time::DeltaTime();
			else
				pos.y = 500;
		}
		else
		{
			if (pos.y < -(0.16666666666667 * pos.x) + 717)
				pos.y += 100 * Time::DeltaTime();

			if (pos.y > -(0.16666666666667 * pos.x) + 717)
				pos.y = -(0.16666666666667 * pos.x) + 717;
		}

		if (pos.x > 1800)
			ObjectManager::Destroy(this);

		SetPos(pos);
	}

	void SwingPlatForm::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SwingPlatForm::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			Rigidbody* plRbody = dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody));
			if (player->GetJumpCollider() == other
				&&	plRbody->GetVelocity().y > 0)
			{	
				plRbody->SetGround(true);
				plPos.y = GetPos().y - GetScale().y +1;
				player->SetPos(plPos);
				mOnPlayer.push_back(player);
			}
		}
	}

	void SwingPlatForm::OnCollisonStay(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Rigidbody* plRbody = dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody));
			Vector2 plPos = player->GetPos();
			if (player->GetJumpCollider() == other
				&& plRbody->isGround())
			{
				bool go = false;
				for (size_t i = 0; i < mOnPlayer.size(); i++)
				{
					if (mOnPlayer[i] == player)
						go = true;
				}
				if (go)
				{
					plPos.y = GetPos().y - GetScale().y + 1;
					player->SetPos(plPos);
				}
			}
		}

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

	void SwingPlatForm::OnCollisonExit(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player->GetJumpCollider() == other)
			{
				for (size_t i = 0; i < mOnPlayer.size(); i++)
				{
					if (mOnPlayer[i] == player)
						mOnPlayer.erase(mOnPlayer.begin() + i);
				}
				dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(false);
			}
		}
	}

	void SwingPlatForm::Release()
	{
		mAnimator->Release();
	}

}