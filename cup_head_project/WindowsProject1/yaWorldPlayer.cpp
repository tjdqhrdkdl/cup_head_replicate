#include "yaWorldPlayer.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaSceneManager.h"
#include "yaCamera.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaCollider.h"
#define STATE_HAVE(STATE) (mCurState & STATE) == STATE
namespace ya
{
	WorldPlayer::WorldPlayer()
		:mSpeed(250)
	{
		SetName(L"WorldPlayer");
		SetPos({ 2800,1200 });
		SetScale({ 50.0f,30.0f });
		mAnimator = new Animator();
		AddComponent(mAnimator);
		AddComponent(new Collider());

		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cuphead OverWorld\\Idle\\tile0", 9, 0.07f, true, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveDown", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\Down\\tile0", 13, 0.05f, true, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveDownRight", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\DownRight\\tile0", 13, 0.05f, true, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveDownLeft", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\DownRight\\tile0", 13, 0.05f, true, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveRight", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\Right\\tile0", 12, 0.05f, true, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveLeft", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\Right\\tile0", 12, 0.05f, true, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveUp", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\Up\\tile0", 13, 0.05f, true, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveUpRight", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\UpRight\\tile0", 12, 0.05f, true, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"MoveUpLeft", L"..\\Resources\\Image\\Cuphead OverWorld\\Move\\UpRight\\tile0", 12, 0.05f, true, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"Complete", L"..\\Resources\\Image\\Cuphead OverWorld\\Complete\\tile0", 10, 0.07f, true, false, { 0, 0 }, true, true);

		mBoxPicture = Resources::Load<Picture>(L"EnterBox", L"..\\Resources\\Image\\Cuphead OverWorld\\BossEnterBox.png");

		mAnimator->Play(L"Idle", true);
		mAnimator->SetAddPos({ -3,15 });
		mBeforePos = { 800,900 };
	}

	WorldPlayer::~WorldPlayer()
	{
	}

	void WorldPlayer::Tick()
	{
		GameObject::Tick();
		KeyInput();
		SetAnimation();
		Move();

	}

	void WorldPlayer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		if (mbEnter)
		{
			Vector2 pos = GetPos() - Vector2(GetScale().x/2, 150);
			Vector2 finalPos = pos;

			finalPos = Camera::CalculatePos(finalPos);
			Vector2 rect;
			rect.x = mBoxPicture->GetWidth();
			rect.y = mBoxPicture->GetHeight();

			TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
					, mBoxPicture->GetDC(), 0, 0, mBoxPicture->GetWidth(), mBoxPicture->GetHeight()
					, RGB(255, 0, 255));

		}
	}

	void WorldPlayer::KeyInput()
	{
		if (KEY_PRESSED(eKeyCode::UP))
		{
			mCurState |= WordPlayerState_Input_Up;
		}
		if (KEY_PRESSED(eKeyCode::DOWN))
		{
			mCurState |= WordPlayerState_Input_Down;
		}
		if (KEY_PRESSED(eKeyCode::LEFT))
		{
			mCurState |= WordPlayerState_Input_Left;
		}
		if (KEY_PRESSED(eKeyCode::RIGHT))
		{
			mCurState |= WordPlayerState_Input_Right;
		}

		// 키 누르는 순간
		// 중복키

		//키 떼는 순간
		if (KEY_UP(eKeyCode::UP))
		{
			mCurState &= ~WordPlayerState_Input_Up;
		}
		if (KEY_UP(eKeyCode::DOWN))
		{
			mCurState &= ~WordPlayerState_Input_Down;
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mCurState &= ~WordPlayerState_Input_Left;
		}
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mCurState &= ~WordPlayerState_Input_Right;
		}
	}

	void WorldPlayer::SetAnimation()
	{
		std::wstring playAnimationName = L"";
		bool loop = true;
		if(mCurState == WordPlayerState_None)
			playAnimationName = L"Idle";

		else if(STATE_HAVE(WordPlayerState_Input_Up))		
		{
			if (STATE_HAVE(WordPlayerState_Input_Right))
			{
				playAnimationName = L"MoveUpRight";
			}
			else if (STATE_HAVE(WordPlayerState_Input_Left))
			{
				playAnimationName = L"MoveUpLeft";
			}
			else
			{
				playAnimationName = L"MoveUp";
			}
		}

		else if (STATE_HAVE(WordPlayerState_Input_Down))
		{
			if (STATE_HAVE(WordPlayerState_Input_Right))
			{
				playAnimationName = L"MoveDownRight";
			}
			else if (STATE_HAVE(WordPlayerState_Input_Left))
			{
				playAnimationName = L"MoveDownLeft";
			}
			else
			{
				playAnimationName = L"MoveDown";
			}
		}
		else if (STATE_HAVE(WordPlayerState_Input_Right))
		{
			playAnimationName = L"MoveRight";
		}
		else if (STATE_HAVE(WordPlayerState_Input_Left))
		{
			playAnimationName = L"MoveLeft";
		}
			


		if (playAnimationName != L""
			&& mAnimator->GetPlayAnimation() != mAnimator->FindAnimation(playAnimationName)
			)
		{
			mAnimator->Play(playAnimationName, loop);
		}
	}

	void WorldPlayer::Move()
	{
		Vector2 pos = GetPos();

		if (mAnimator->GetPlayAnimation()->GetName() == L"MoveRight")
		{
			pos.x += Time::DeltaTime() * mSpeed;
		}

		else if(mAnimator->GetPlayAnimation()->GetName() == L"MoveLeft")
		{
			pos.x -= Time::DeltaTime() * mSpeed;
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"MoveUpLeft")
		{
			pos.x -= Time::DeltaTime() * mSpeed * 0.75;
			pos.y -= Time::DeltaTime() * mSpeed * 0.75;
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"MoveDownLeft")
		{
			pos.x -= Time::DeltaTime() * mSpeed * 0.75;
			pos.y += Time::DeltaTime() * mSpeed * 0.75;
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"MoveUpRight")
		{
			pos.x += Time::DeltaTime() * mSpeed * 0.75;
			pos.y -= Time::DeltaTime() * mSpeed * 0.75;
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"MoveDownRight")
		{
			pos.x += Time::DeltaTime() * mSpeed * 0.75;
			pos.y += Time::DeltaTime() * mSpeed * 0.75;
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"MoveDown")
		{
			pos.y += Time::DeltaTime() * mSpeed;
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"MoveUp")
		{
			pos.y -= Time::DeltaTime() * mSpeed;
		}

		SetPos(pos);
	}


	void WorldPlayer::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::FrontObject)
		{
			mbEnter = true;
			mEnterBossObject = other->GetOwner();
		}
	}

	void WorldPlayer::OnCollisonStay(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::FrontObject)
		{
			mbEnter = true;
			mEnterBossObject = other->GetOwner();
		}
	}

	void WorldPlayer::OnCollisonExit(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::FrontObject)
		{
			mbEnter = false;
			mEnterBossObject = nullptr;
		}
	}

	void WorldPlayer::Release()
	{
	}

}