#pragma once
#include "Common.h"
#include "yaScene.h"
namespace ya 
{
	class ScoreScene;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);
	   
		static void Release();
		static Scene* GetCurScene() { return mCurScene; }
		static void SetCurScene(eSceneType type) { mCurScene = mScenes[(UINT)type]; }
		static ScoreScene* GetScoreScene(); 

		static void DetroyGameObject();
		static void ChangeScene(eSceneType type);


	private:
		static Scene* mScenes[(UINT)eSceneType::Max];
		static Scene* mCurScene;
		static ScoreScene* mScoreScene;
	};
}

