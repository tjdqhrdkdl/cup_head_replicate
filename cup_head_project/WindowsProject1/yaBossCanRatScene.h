#pragma once
#include "yaScene.h"
#include "yaBgImageObject.h"
#include "yaPeakingCat.h"
namespace ya
{
	class Player;
	class Disc;
	class BossCanRatScene : public Scene
	{
	public:
		BossCanRatScene();
		~BossCanRatScene();


		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void Enter() override;
		virtual void Exit() override;

		UINT GetPhase() { return mPhase; }
		void SetPhase(UINT phase) { mPhase = phase, mbPhaseChanged = true; }
		Player* GetScenePlayer() { return mPlayer; }
		void SetPhase2Object(GameObject* phase2) { mPhase2Object = phase2; }
		void ChangeBGQue();
		void ChangeLastBGQue();

		void Release();
	private:
		 
		BgImageObject* mBGIHouse;
		BgImageObject* mBGI1;
		BgImageObject* mBGI2;
		BgImageObject* mBGI3_a;
		BgImageObject* mBGI3_b;
		Player* mPlayer;

		PeakingCat* mPeakingCat;
		std::vector<Disc*> mDiscs[2];
		GameObject* mPhase2Object;
		GameObject* mPh2BGChanger;

		bool mbInitialized;
		float mTime;

		UINT mPhase;
		bool mbPhaseChanged;
		float mPhaseTimeChecker;
		float mPeakTimeChecker;
	};
}
