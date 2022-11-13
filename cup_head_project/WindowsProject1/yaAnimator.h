#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"
namespace ya 
{
	class Image;
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};
		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

		Animator();
		~Animator();

		virtual void Tick() override;
		void Render(HDC hdc) override;
		Gdiplus::ColorMatrix GetMatrix() { return mColorMatrix; }
		void SetMatrixToLighten();
		void SetMatrixToBase();
		void SetMatrixToTransparent(float);
		Animation* FindAnimation(const std::wstring& name);
		void CreateAnimation(const std::wstring& name, const std::wstring& path
			, UINT imageNum, float duration, bool fromZero,  bool imageReversed
			, Vector2 fixPos = Vector2::Zero, bool bAffectedCamera = true
			, bool haveAlpha = false, UINT imageDegree = 0);

		void Play(const std::wstring& name, bool bLoop);

		Events* FindEvents(const std::wstring key);
		std::function<void()>& GetStartEvent(const std::wstring key);
		std::function<void()>& GetCompleteEvent(const std::wstring key);
		std::function<void()>& GetEndEvent(const std::wstring key);

		Animation* GetPlayAnimation() { return mPlayAnimation; }




	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mPlayAnimation;
		bool mbLoop;

		Gdiplus::ColorMatrix mColorMatrix;

	};
}
