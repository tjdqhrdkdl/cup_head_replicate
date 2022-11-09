#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaResources.h"


namespace ya
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		, mPlayAnimation(nullptr)
		, mbLoop(false)
	{
		mColorMatrix = {

		 1.0f,    0.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    1.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    1.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    0.0f,    1.0f,    0.0f,

		 0.0f,    0.0f,    0.0f,    0.0f,    1.0f

		};
	}

	Animator::~Animator()
	{
		for (std::map<std::wstring, Animation*>::iterator iter = mAnimations.begin();iter != mAnimations.end();iter++ )
		{
			if (iter->second == nullptr)
				continue;
			delete iter->second;
		}
	}

	void Animator::Tick()
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();
			if (mbLoop && mPlayAnimation->isComplete())
			{
				mCompleteEvent();
				mPlayAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Render(hdc);
		}
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(name);

		if(iter != mAnimations.end())
			return (*iter).second;

		return nullptr;
	}

	void Animator::CreateAnimation(const std::wstring& name, const std::wstring& path
		, UINT imageNum, float duration, bool fromZero, bool imageReversed, Vector2 fixPos, bool bAffectedCamera ,bool haveAlpha, UINT imageDegree )
	{
		if (FindAnimation(name) != nullptr)
		{
			MessageBox(nullptr, L"중복 키 애니메이션 생성", L"애니메이션 생성 실패!", MB_OK);
			return;
		}
		std::wstring objName = GetOwner()->GetName();
		Animation* animation = new Animation();
		animation->Create(objName+L"_"+name, path
			, imageNum, duration, imageReversed, fromZero,fixPos, bAffectedCamera, haveAlpha, imageDegree);
		animation->SetAnimator(this);
		animation->SetName(name);

		mAnimations.insert(std::make_pair(name, animation));
	}	

	void Animator::Play(const std::wstring& name, bool bLoop)
	{
		Animation* prevAnimation = mPlayAnimation;
		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = bLoop;
	}
	void Animator::SetMatrixToLighten()
	{
		mColorMatrix = {

		 1.0f,    0.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    1.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    1.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    0.0f,    1.0f,    0.0f,

		 0.2f,    0.2f,    0.2f,    0.0f,    1.0f

		};
		mPlayAnimation->SetHaveAlpha(true);
	}
	void Animator::SetMatrixToBase()
	{
		mColorMatrix = {

		 1.0f,    0.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    1.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    1.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    0.0f,    1.0f,    0.0f,

		 0.0f,    0.0f,    0.0f,    0.0f,    1.0f

		};

		mPlayAnimation->SetHaveAlpha(false);
	}
}