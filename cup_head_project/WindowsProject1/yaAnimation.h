#pragma once
#include "yaEntity.h"
#include "yaPicture.h"

namespace ya
{
	class Animator;
	class Animation: public Entity
	{
	public:
		Animation();
		~Animation();

		void Tick();
		void Render(HDC hdc);
		void Reset();

		void Create(const std::wstring& key, const std::wstring& path
			, UINT imageNum, float duration, bool imageReversed, bool fromZero, Vector2 fixPos = Vector2::Zero, bool bAffectedCamera = true, bool haveAlpha = false, UINT imageDegree = 0);

		bool isComplete() { return mComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

		void SetHaveAlpha(bool data) { mbHaveAlpha = data; }
		void SetLightenAnimation(Animation* lightenAnim) { mLightenAnimation = lightenAnim; }

		bool haveCompleted() { return mbHaveCompleted; }
		void SetHaveCompleted(bool c) { mbHaveCompleted = c; }
	private:
		Animator* mAnimator;
		std::vector<Picture*> mPictures;	
		UINT mPictureIndex;
		float mPictureDuration;
		float mTime;

		bool mStart;
		bool mComplete;
		bool mEnd;
		bool mAffectedCamera;

		bool mbHaveAlpha;
		bool mbHaveCompleted;
		Vector2 mFixPos;

		Animation* mLightenAnimation;
	};
}
