#include "yaRollerCoaster.h"
#include "yaTime.h"
#include "yaObjectManager.h"
#include "yaSceneManager.h"
#include "yaCollider.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
namespace ya
{
	RollerCoaster::RollerCoaster(UINT coasterLength)
		:mSpeed(400)
		,mAliveTime(13.0f)
		,mAliveTimeChecker(0)
		,mTrailLength(coasterLength)
	{
		//���� ����
		mTail = ObjectManager::Instantiate<RollerCoasterTail>(SceneManager::GetCurScene(), eColliderLayer::FrontMonster);
		mTail->SetPos({ 4570,700 });

		//�� cart ����
		UINT withPassengersCount = 0;
		bool isBlue = false;
		bool withPassengers = false;
		for (size_t i = 0; i < mTrailLength; i++)
		{
			if (isBlue)
				isBlue = false;
			else
				isBlue = true;
			
			if (withPassengersCount == 3)
			{
				withPassengers = true;
				withPassengersCount = 0;
			}
			else
			{
				withPassengers = false;
				++withPassengersCount;
			}
			RollerCoasterTrail* trail = new RollerCoasterTrail(isBlue, withPassengers);
			mTrails.push_back(trail);
			trail->SetPos({ 1900+float(270 * i), 700 });
			trail->Initialize();
			SceneManager::GetCurScene()->AddGameObject(trail, eColliderLayer::FrontMonster);
		}
		//�Ӹ� ����
		mHead = ObjectManager::Instantiate<RollerCoasterHead>(SceneManager::GetCurScene(), eColliderLayer::FrontMonster);
		mHead->SetPos({ 1570,750 });


		//�����̴� ��
		mGroundCollider = new Collider();
		mGroundCollider->SetScale({ 2900, 50 });
		mGroundCollider->SetAddPos({ 3000, 705 });
		AddComponent(mGroundCollider);
		mGroundCollider->Tick();


	}

	RollerCoaster::~RollerCoaster()
	{
		for (size_t i = 0; i < mTrailLength; i++)
		{
			ObjectManager::Destroy(mTrails[i]);
		}
		ObjectManager::Destroy(mHead);
		ObjectManager::Destroy(mTail);

	}

	void RollerCoaster::Tick()
	{
		//���� ��Ŀ����
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
			for (size_t i = 0; i < mTrails.size(); i++)
			{
				ObjectManager::Destroy(mTrails[i]);
			}
			ObjectManager::Destroy(mHead);
			ObjectManager::Destroy(mTail);
			if(mHead->GetNose()!= nullptr)
				ObjectManager::Destroy(mHead->GetNose());

		}

		//��ü �� �� �̵�
		Vector2 pos = GetPos();
		pos.x -= mSpeed * Time::DeltaTime();
		SetPos(pos);

		//Ʈ���� �̵�
		for (size_t i = 0; i < mTrails.size(); i++)
		{
			Vector2 trailPos = mTrails[i]->GetPos();
			trailPos.x -= mSpeed * Time::DeltaTime();
			mTrails[i]->SetPos(trailPos);
		}

		//�Ӹ� �� ���� �̵�
		Vector2 headPos = mHead->GetPos();
		headPos.x -= mSpeed * Time::DeltaTime();
		mHead->SetPos(headPos);

		Vector2 tailPos = mTail->GetPos();
		tailPos.x -= mSpeed * Time::DeltaTime();
		mTail->SetPos(tailPos);


		GameObject::Tick();
	}

	void RollerCoaster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RollerCoaster::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			dynamic_cast<Rigidbody*>(player->GetComponent(eComponentType::Rigidbody))->SetGround(true);
			plPos.y = 680;
			player->SetPos(plPos);

		}
	}

	void RollerCoaster::OnCollisonStay(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			Vector2 plPos = player->GetPos();
			plPos.x -= mSpeed * Time::DeltaTime();
			player->SetPos(plPos);
		}
	}

	void RollerCoaster::OnCollisonExit(Collider* other, Collider* my)
	{
	}


}