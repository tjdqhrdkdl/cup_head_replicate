#pragma once
#include "yaScene.h"
#include "yaBgImageObject.h"

namespace ya {
	class Number;
	class WinObjects;
	class StarScore;
	class ScoreScene : public Scene
	{
	public:
		ScoreScene();
		~ScoreScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SendInfo(float maxTime, float time, UINT hp, UINT parry, UINT super, bool fin = false);
		virtual void Enter();
		virtual void Exit();

	private:
		BgImageObject* mBGI;
		Sound* mBGM;
		

		UINT mPlayTime;
		UINT mHp;
		UINT mParry;
		UINT mSuper;

		UINT mMaxPlayTime;
		UINT mMaxHp;
		UINT mMaxParry;
		UINT mMaxSuper;
		
		UINT mGrade;

		float mNumberChangeTime;
		bool mbFin;
		UINT mScorePhase;
		WinObjects* mWinObject;
		Number* mTimeNumber[4];
		Number* mHPNumber[2];
		Number* mParryNumber[2];
		Number* mSuperNumber[2];
		Number* mGradeNumber;
		StarScore* mStarScore[3];

	};		 
}
