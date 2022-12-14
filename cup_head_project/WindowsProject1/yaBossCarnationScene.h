#pragma once
#include "yaScene.h"
#include "yaBgImageObject.h"

namespace ya
{
	class Player;
	class CameraBlur;
	class BossCarnationScene : public Scene
	{
	public:
		BossCarnationScene();
		~BossCarnationScene();


		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void ResumeClickEvent();
		void RetryClickEvent();
		void ExitClickEvent();

		virtual void Enter() override;
		virtual void Exit() override;

		UINT GetPhase() { return mPhase; }
		void BGMOff();
		void SetPhase(UINT phase) { mPhase = phase, mbPhaseChanged = true; }
		Player* GetScenePlayer() { return mPlayer; }

		void Release();
	private:
		BgImageObject* mBGI;
		Sound* mBGM;
		Player* mPlayer;

		bool mbInitialized;

		UINT mPhase;
		bool mbPhaseChanged;
		float mPhaseTimeChecker;

		CameraBlur* mCameraBlur;
		bool mbUIOn;
	};
}
