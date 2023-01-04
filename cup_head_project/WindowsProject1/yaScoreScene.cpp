#include "yaScoreScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaObjectManager.h"
#include "yaCollisionManager.h"
#include "yaTime.h"
#include "yaSound.h"
#include "yaNumber.h"
#include "yaAnimator.h"
#include "yaWinObjects.h"
namespace ya
{
	ScoreScene::ScoreScene()
		:mMaxHp(3)
		,mMaxParry(6)
		,mMaxSuper(6)
	{



	}

	ScoreScene::~ScoreScene()
	{
	}

	void ScoreScene::Initialize()
	{
		mScorePhase = 0;
		mbSceneChanging = false;
		mBGI = new	BgImageObject();
		AddGameObject(mBGI, eColliderLayer::BackGround);

		mBGI->SetImage(L"WinScreenBGI", L"WinScreen\\BG\\winscreen_bg.png", RGB(255, 0, 255), true);
		mBGM = Resources::Load<Sound>(L"WinScreenBGM", L"..\\Resources\\Sound\\Win\\MUS_VictoryScreen.wav");

		ObjectManager::Instantiate<WinObjects>(this, eColliderLayer::FrontMonster)->SetPos({800,900});

		for (size_t i = 0; i < 4; i++)
		{
			mTimeNumber[i] = ObjectManager::Instantiate<Number>(this, eColliderLayer::FrontMonster);
		}
		mTimeNumber[0]->SetPos({ 1185,400 });
		mTimeNumber[1]->SetPos({ 1210,400 });
		mTimeNumber[2]->SetPos({ 1245,400 });
		mTimeNumber[3]->SetPos({ 1270,400 });
		for (size_t i = 0; i < 2; i++)
		{
			mHPNumber[i] = ObjectManager::Instantiate<Number>(this, eColliderLayer::FrontMonster);
			mParryNumber[i] = ObjectManager::Instantiate<Number>(this, eColliderLayer::FrontMonster);
			mSuperNumber[i] = ObjectManager::Instantiate<Number>(this, eColliderLayer::FrontMonster);
		}
		mHPNumber[0]->SetPos({ 1243,456 });
		mHPNumber[1]->SetPos({ 1278,456 });
		mParryNumber[0]->SetPos({ 1243,510 });
		mParryNumber[1]->SetPos({ 1278,510 });
		mSuperNumber[0]->SetPos({ 1243,567 });
		mSuperNumber[1]->SetPos({ 1278,567 });


		Scene::Initialize();

	}

	void ScoreScene::Tick()
	{
		if (SceneManager::GetCurScene() == (Scene*)this)
		{
			mBGM->Play(true);
			Scene::Tick();
			if (mTime > 3)
			{
				mNumberChangeTime += Time::DeltaTime();
				if (mScorePhase == 0)
					mTimeNumber[3]->GetAnimator()->SetStop(false);
				else if (mScorePhase == 1)
					mHPNumber[0]->GetAnimator()->SetStop(false);
				else if (mScorePhase == 2)
					mParryNumber[0]->GetAnimator()->SetStop(false);
				else if (mScorePhase == 3)
					mSuperNumber[0]->GetAnimator()->SetStop(false);
			}
			if (mNumberChangeTime > 0.4f)
			{
				if (mScorePhase == 0)
				{
					for (size_t k = 0; k < 4; k++)
					{
						mTimeNumber[k]->GetAnimator()->GetPlayAnimation()->SetIndex(mTimeNumber[k]->GetStopIndex());
						if (mMaxPlayTime >= mPlayTime)
							mTimeNumber[k]->GetAnimator()->SetLighten(true);
						mTimeNumber[k]->GetAnimator()->SetStop(true);
					}
				}
				else if (mScorePhase == 1)
				{
					for (size_t i = 0; i < 2; i++)
					{
						mHPNumber[i]->GetAnimator()->GetPlayAnimation()->SetIndex(mHPNumber[i]->GetStopIndex());
						if (mMaxHp == mHp)
							mHPNumber[i]->GetAnimator()->SetLighten(true);
						mHPNumber[i]->GetAnimator()->SetStop(true);
					}
				}
				else if (mScorePhase == 2)
				{
					for (size_t i = 0; i < 2; i++)
					{
						mParryNumber[i]->GetAnimator()->GetPlayAnimation()->SetIndex(mParryNumber[i]->GetStopIndex());
						if (mMaxParry == mParry)
							mParryNumber[i]->GetAnimator()->SetLighten(true);
						mParryNumber[i]->GetAnimator()->SetStop(true);
					}
				}
				else if (mScorePhase == 3)
				{
					for (size_t i = 0; i < 2; i++)
					{
						mSuperNumber[i]->GetAnimator()->GetPlayAnimation()->SetIndex(mSuperNumber[i]->GetStopIndex());
						if (mMaxSuper == mSuper)
							mSuperNumber[i]->GetAnimator()->SetLighten(true);
						mSuperNumber[i]->GetAnimator()->SetStop(true);
					}
				}
				else if (!mbSceneChanging)
				{
					if (!mbFin)
						SceneManager::ChangeScene(eSceneType::Map);
					else
						SceneManager::ChangeScene(eSceneType::End);
					
					mbSceneChanging = true;
					return;
				}
				mNumberChangeTime = 0;
				mScorePhase += 1;
				mTime = 1;
			}
			if (SceneManager::GetCurScene() == (Scene*)this)
			{
				if (mHPNumber[0]->GetAnimator()->GetPlayAnimation()->GetIndex() == mHPNumber[0]->GetStopIndex())
				{
					if (mScorePhase == 1)
					{
						for (size_t i = 0; i < 2; i++)
						{
							mHPNumber[i]->GetAnimator()->GetPlayAnimation()->SetIndex(mHPNumber[i]->GetStopIndex());
							if (mMaxHp == mHp)
								mHPNumber[i]->GetAnimator()->SetLighten(true);
							mHPNumber[i]->GetAnimator()->SetStop(true);
						}
					}
				}
				if (mParryNumber[0]->GetAnimator()->GetPlayAnimation()->GetIndex() == mParryNumber[0]->GetStopIndex())

				{
					if (mScorePhase == 2)
					{
						for (size_t i = 0; i < 2; i++)
						{
							mParryNumber[i]->GetAnimator()->GetPlayAnimation()->SetIndex(mParryNumber[i]->GetStopIndex());
							if (mMaxParry == mParry)
								mParryNumber[i]->GetAnimator()->SetLighten(true);
							mParryNumber[i]->GetAnimator()->SetStop(true);
						}
					}
				}
				if (mSuperNumber[0]->GetAnimator()->GetPlayAnimation()->GetIndex() == mSuperNumber[0]->GetStopIndex())
				{
					if (mScorePhase == 3)
					{
						for (size_t i = 0; i < 2; i++)
						{
							mSuperNumber[i]->GetAnimator()->GetPlayAnimation()->SetIndex(mSuperNumber[i]->GetStopIndex());
							if (mMaxSuper == mSuper)
								mSuperNumber[i]->GetAnimator()->SetLighten(true);
							mSuperNumber[i]->GetAnimator()->SetStop(true);
						}
					}
				}
			}
		}
	}

	void ScoreScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void ScoreScene::SendInfo(float maxTime, float time, UINT hp, UINT parry, UINT super, bool fin)
	{
		mMaxPlayTime = (UINT)maxTime;
		mPlayTime = (UINT)time;
		mHp = hp;
		mParry = parry;
		mSuper = super;
		int min = mPlayTime / 60;
		int sec = mPlayTime % 60;
		mTimeNumber[0]->SetStopIndex(min / 10);
		mTimeNumber[1]->SetStopIndex(min % 10);
		mTimeNumber[2]->SetStopIndex(sec / 10);
		mTimeNumber[3]->SetStopIndex(sec % 10);
		mHPNumber[0]->SetStopIndex(mHp);
		mHPNumber[1]->SetStopIndex(3);
		mHPNumber[1]->GetAnimator()->GetPlayAnimation()->SetIndex(3);
		mParryNumber[0]->SetStopIndex(mParry);
		mParryNumber[1]->SetStopIndex(6);
		mParryNumber[1]->GetAnimator()->GetPlayAnimation()->SetIndex(6);
		mSuperNumber[0]->SetStopIndex(mSuper);
		mSuperNumber[1]->SetStopIndex(6);
		mSuperNumber[1]->GetAnimator()->GetPlayAnimation()->SetIndex(6);
		mbFin = fin;
	}

	void ScoreScene::Enter()
	{
		Initialize();
		Scene::Enter();
	}

	void ScoreScene::Exit()
	{
		Scene::Exit();
		mBGM->Stop(true);
		Scene::Release();

	}

}