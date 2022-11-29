#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaSceneManager.h"

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

		for (std::map<std::wstring, Events*>::iterator iter = mEvents.begin();iter != mEvents.end();iter++)
		{
			if (iter->second == nullptr)
				continue;
			delete iter->second;
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Tick()
	{
		if (mPlayAnimation != nullptr && mbStop ==false)
		{
			mPlayAnimation->Tick();
			if (mbLoop && mPlayAnimation->isComplete())
			{
				Animator::Events* events
					= FindEvents(mPlayAnimation->GetName());
				events->mCompleteEvent();
				mPlayAnimation->Reset();
			}
			else if (!mbLoop && mPlayAnimation->isComplete())
			{
				if (!(mPlayAnimation->haveCompleted()))
				{
					Animator::Events* events
						= FindEvents(mPlayAnimation->GetName());

					mPlayAnimation->SetHaveCompleted(true);
					events->mCompleteEvent();
				}
			}
			if (mBaseAnimation != nullptr && (mbLoop == false) && mPlayAnimation->isComplete())
			{
				if (mPlayAnimation->GetName() == L"Intro" && SceneManager::GetCurScene()->isIntro())
					;
				else if (mPlayAnimation->GetName() == L"Intro")
				{
					mPlayAnimation = mBaseAnimation;
					mPlayAnimation->Reset();
					mbLoop = true;
				}
				else
				{
					;
				}
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

	Animation* Animator::CreateAnimation(const std::wstring& name, const std::wstring& path
		, UINT imageNum, float duration, bool fromZero, bool imageReversed, Vector2 fixPos, bool bAffectedCamera ,bool haveAlpha, UINT imageDegree )
	{
		if (FindAnimation(name) != nullptr)
		{
			MessageBox(nullptr, L"중복 키 애니메이션 생성", L"애니메이션 생성 실패!", MB_OK);
			return nullptr;
		}
		std::wstring objName = GetOwner()->GetName();
		Animation* animation = new Animation();
		animation->Create(objName+L"_"+name, path
			, imageNum, duration, imageReversed, fromZero,fixPos, bAffectedCamera, haveAlpha, imageDegree);
		animation->SetAnimator(this);
		animation->SetName(name);			

		mAnimations.insert(std::make_pair(name, animation));
		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
		return animation;
	}	

	void Animator::Play(const std::wstring& name, bool bLoop)
	{
		
		Animation* prevAnimation = mPlayAnimation;

		mPlayAnimation = FindAnimation(name);

		Animator::Events* events = FindEvents(name);
		if (events != nullptr)
			events->mStartEvent();


		mPlayAnimation->Reset();
		mbLoop = bLoop;
		if (prevAnimation != nullptr)
		{
			Animator::Events* prevEvents = FindEvents(prevAnimation->GetName());
			if (prevAnimation != mPlayAnimation)
			{
				if (prevEvents != nullptr)
					prevEvents->mEndEvent();
			}
		}
	}
	Animator::Events* Animator::FindEvents(const std::wstring key)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(key);
		if (iter == mEvents.end())
			return nullptr;
		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);
		return events->mStartEvent.mEvent;

	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);
		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);
		return events->mEndEvent.mEvent;
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
	void Animator::SetMatrixToTransparent(float transparency)
	{
		mColorMatrix = {

		 1.0f,    0.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    1.0f,    0.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    1.0f,    0.0f,    0.0f,

		 0.0f,    0.0f,    0.0f,    1.0f-transparency,    0.0f,

		 0.0f,    0.0f,    0.0f,    0.0f,    1.0f

		};

		mPlayAnimation->SetHaveAlpha(true);
	}
}