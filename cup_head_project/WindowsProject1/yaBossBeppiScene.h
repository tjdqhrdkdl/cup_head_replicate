#pragma once
#include "yaScene.h"
#include "yaBgImageObject.h"

namespace ya 
{
	class Player;
	class CameraBlur;
	class BossBeppiScene : public Scene
	{
	public:
		BossBeppiScene();
		~BossBeppiScene();


		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void ResumeClickEvent();
		void RetryClickEvent();
		void ExitClickEvent();
		void BGMOff();
		virtual void Enter() override;
		virtual void Exit() override;

		UINT GetPhase() { return mPhase; }
		void SetPhase(UINT phase) { mPhase = phase, mbPhaseChanged = true; }
		Player* GetScenePlayer() { return mPlayer; }

		void Release();
	private:
		Sound* mBGM;

		BgImageObject* mBGI;
		Player* mPlayer;
		
		bool mbInitialized;

		UINT mPhase;
		bool mbPhaseChanged;
		float mPhaseTimeChecker;

		CameraBlur* mCameraBlur;
		bool mbUIOn;
	};
}
