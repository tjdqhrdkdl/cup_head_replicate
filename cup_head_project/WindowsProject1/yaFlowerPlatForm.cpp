#include "yaFlowerPlatForm.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaObjectManager.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaInput.h"
namespace ya
{
	FlowerPlatForm::FlowerPlatForm()
	{

		SetName(L"FlowerPlatForm");
		SetScale({ 180,80 });
		mCollider = new Collider();
		mCollider->SetHitBox(false);
		AddComponent(mCollider);
		mPropellerAnimator = new Animator();

		AddComponent(mPropellerAnimator);
		mPropellerAnimator->CreateAnimation(L"PropellerIdle", L"..\\Resources\\Image\\Cagney Carnation\\Platform\\Platform_Propellor_", 10, 0.04f, false, false, { 5,20 });
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cagney Carnation\\Platform\\Platform_A_", 4, 0.08f, false, false);

		mAnimator->Play(L"Idle", true);
		mPropellerAnimator->Play(L"PropellerIdle", true);
	}

	FlowerPlatForm::~FlowerPlatForm()
	{
	}

	void FlowerPlatForm::Tick()
	{
		GameObject::Tick();		
		Vector2 pos = GetPos();
		if (mOnPlayer.size() == 0)
		{
			if (mbUp)
			{
				pos.y -= 10 * Time::DeltaTime();
				if (pos.y < 530)
					mbUp = false;
			}
			else
			{
				pos.y += 10 * Time::DeltaTime();
				if (pos.y > 560)
					mbUp = true;
			}
		}
		else if (mOnPlayer.size() > 0)
		{
			if (pos.y < 560)
				pos.y += 200 * Time::DeltaTime();
		}
		SetPos(pos);

	}

	void FlowerPlatForm::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void FlowerPlatForm::OnCollisonEnter(Collider* other, Collider* my)
	{
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
	}

	void FlowerPlatForm::OnCollisonStay(Collider* other, Collider* my)
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

	void FlowerPlatForm::OnCollisonExit(Collider* other, Collider* my)
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
				if (mOnPlayer.size() == 0)
					mbUp = true;
			}
		}
	}

	void FlowerPlatForm::Release()
	{
		mAnimator->Release();
	}

}