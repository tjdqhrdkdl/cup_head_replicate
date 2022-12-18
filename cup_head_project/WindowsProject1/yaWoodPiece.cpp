#include "yaWoodPiece.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaGround.h"

namespace ya
{
	WoodPiece::WoodPiece()
	{
		SetName(L"WoodPiece");
		SetScale({ 100	,100 });

		mCollider = new Collider();
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"IdleA", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wood Piece\\A\\cat_wood_piece_a_00", 9, 0.05f, false, false);
		mAnimator->CreateAnimation(L"IdleB", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wood Piece\\B\\cat_wood_piece_b_00", 9, 0.05f, false, false);
		mAnimator->CreateAnimation(L"IdleC", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wood Piece\\C\\cat_wood_piece_c_00", 9, 0.05f, false, false);
		mAnimator->CreateAnimation(L"DeathA", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wood Piece\\A\\Death\\cat_wood_piece_death_a_00", 7, 0.05f, false, false);
		mAnimator->CreateAnimation(L"DeathB", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wood Piece\\B\\Death\\cat_wood_piece_death_b_00", 7, 0.05f, false, false);
		mAnimator->CreateAnimation(L"DeathC", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wood Piece\\C\\Death\\cat_wood_piece_death_c_00", 6, 0.05f, false, false);


		mAnimator->GetCompleteEvent(L"DeathA") = std::bind(&WoodPiece::DeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DeathB") = std::bind(&WoodPiece::DeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DeathC") = std::bind(&WoodPiece::DeathCompleteEvent, this);
		switch (rand()%3)
		{
		case 0:
			mAnimator->Play(L"IdleA", true);
			break;
		case 1:
			mAnimator->Play(L"IdleB", true);
			break;
		case 2:
			mAnimator->Play(L"IdleC", true);
			break;
		}
	}

	WoodPiece::~WoodPiece()
	{
	}

	void WoodPiece::Tick()
	{
		GameObject::Tick();
		if (mAnimator->GetPlayAnimation()->GetName() == L"IdleA"
			|| mAnimator->GetPlayAnimation()->GetName() == L"IdleB"
			|| mAnimator->GetPlayAnimation()->GetName() == L"IdleC")
		{
			Vector2 pos = GetPos();
			pos.y += Time::DeltaTime() * 400;
			SetPos(pos);
		}
	}

	void WoodPiece::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void WoodPiece::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::FrontObject
			&& dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			if (mAnimator->GetPlayAnimation()->GetName() == L"IdleA")
				mAnimator->Play(L"DeathA", false);
			if (mAnimator->GetPlayAnimation()->GetName() == L"IdleB")
				mAnimator->Play(L"DeathB", false);
			if (mAnimator->GetPlayAnimation()->GetName() == L"IdleC")
				mAnimator->Play(L"DeathC", false);
			GetComponent<Collider>()->SetOff(true);
		}
	}

	void WoodPiece::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void WoodPiece::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void WoodPiece::DeathCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void WoodPiece::Release()
	{
	}

}