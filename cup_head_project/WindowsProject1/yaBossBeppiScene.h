#pragma once
#include "yaScene.h"
#include "yaBgImageObject.h"

namespace ya 
{
	class Player;
	class BossBeppiScene : public Scene
	{
	public:
		BossBeppiScene();
		~BossBeppiScene();


		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void Enter() override;
		virtual void Exit() override;

		UINT GetPhase() { return mPhase; }
		void SetPhase(UINT phase) { mPhase = phase, mbPhaseChanged = true; }
		Player* GetScenePlayer() { return mPlayer; }

		void Release();
	private:
		BgImageObject* mBGI;
		Player* mPlayer;
		
		bool mbInitialized;
		float mTime;

		UINT mPhase;
		bool mbPhaseChanged;
		float mPhaseTimeChecker;
	};
}
