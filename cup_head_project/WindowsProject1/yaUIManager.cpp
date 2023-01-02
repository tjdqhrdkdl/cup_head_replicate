#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaButton.h"
#include "yaPanel.h"
#include "yaHealthUI.h"
#include "yaEXPointUI.h"
#include "yaWeaponUI.h"
namespace ya
{
	std::unordered_map<eUIType, UiBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UiBase*> UIManager::mUIBases;
	UiBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{
		// 여기에서 ui 메모리에 할당하면 된다.
		Button* startButton = new Button(eUIType::TITLEOPTION_START);
		mUIs.insert(std::make_pair(eUIType::TITLEOPTION_START, startButton));
		startButton->SetPos(Vector2(750.0f, 350.0f));
		startButton->ImageLoad(L"START", L"..\\Resources\\Image\\UI\\TitleScene\\START.png");
		startButton->SetClickImage(L"Start_onClick", L"..\\Resources\\Image\\UI\\TitleScene\\START_ON.png");

		Button* optionButton = new Button(eUIType::TITLEOPTION_OPTION);
		mUIs.insert(std::make_pair(eUIType::TITLEOPTION_OPTION, optionButton));
		optionButton->SetPos(Vector2(735.0f, 400.0f));
		optionButton->ImageLoad(L"Options", L"..\\Resources\\Image\\UI\\TitleScene\\OPTIONS.png");
		optionButton->SetClickImage(L"Options_onClick", L"..\\Resources\\Image\\UI\\TitleScene\\OPTIONS_ON.png");

		Button* exitButton = new Button(eUIType::TITLEOPTION_EXIT);
		mUIs.insert(std::make_pair(eUIType::TITLEOPTION_EXIT, exitButton));
		exitButton->SetPos(Vector2(767.5f, 450.0f));
		exitButton->ImageLoad(L"Exit", L"..\\Resources\\Image\\UI\\TitleScene\\EXIT.png");
		exitButton->SetClickImage(L"Exit_onClick", L"..\\Resources\\Image\\UI\\TitleScene\\EXIT_ON.png");

		Button* PlayResumeButton = new Button(eUIType::PLAYOPTION_RESUME);
		mUIs.insert(std::make_pair(eUIType::PLAYOPTION_RESUME, PlayResumeButton));
		PlayResumeButton->SetPos(Vector2(240, 100.0f));
		PlayResumeButton->ImageLoad(L"PlayResume", L"..\\Resources\\Image\\UI\\PlayScene\\RESUME.png");
		PlayResumeButton->SetClickImage(L"PlayResume_onClick", L"..\\Resources\\Image\\UI\\PlayScene\\RESUME_ON.png");

		Button* PlayRetryButton = new Button(eUIType::PLAYOPTION_RETRY);
		mUIs.insert(std::make_pair(eUIType::PLAYOPTION_RETRY, PlayRetryButton));
		PlayRetryButton->SetPos(Vector2(252.5, 170.0f));
		PlayRetryButton->ImageLoad(L"PlayRetry", L"..\\Resources\\Image\\UI\\PlayScene\\RETRY.png");
		PlayRetryButton->SetClickImage(L"PlayRetry_onClick", L"..\\Resources\\Image\\UI\\PlayScene\\RETRY_ON.png");

		Button* PlayExitButton = new Button(eUIType::PLAYOPTION_EXIT);
		mUIs.insert(std::make_pair(eUIType::PLAYOPTION_EXIT, PlayExitButton));
		PlayExitButton->SetPos(Vector2(190, 240.0f));
		PlayExitButton->ImageLoad(L"PlayExit", L"..\\Resources\\Image\\UI\\PlayScene\\EXITTOMAP.png");
		PlayExitButton->SetClickImage(L"PlayExit_onClick", L"..\\Resources\\Image\\UI\\PlayScene\\EXITTOMAP_ON.png");
		

		Panel* panel = new Panel(eUIType::PLAYOPTION_PANEL);
		mUIs.insert(std::make_pair(eUIType::PLAYOPTION_PANEL, panel));
		panel->ImageLoad(L"PlayPanel", L"..\\Resources\\Image\\UI\\PlayScene\\Panel.png");
		panel->SetPos(Vector2(450, 250));
		panel->AddChild(PlayResumeButton);
		panel->AddChild(PlayRetryButton);
		panel->AddChild(PlayExitButton);

		WeaponUI* weaponUI = new WeaponUI(eUIType::Gun);
		mUIs.insert(std::make_pair(eUIType::Gun, weaponUI));


		HealthUI* healthUI = new HealthUI(eUIType::HP);
		mUIs.insert(std::make_pair(eUIType::HP, healthUI));

		EXPointUI* exPointUI = new EXPointUI(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, exPointUI));
		

	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UiBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::Tick()
	{
		std::stack<UiBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			//UI 로드 해줘
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
		std::stack<UiBase*> uiBases = mUIBases;
		std::stack<UiBase*> tempStack;

		// 뒤집어서 렌더링을 해준다.
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			tempStack.push(uiBase);
			uiBases.pop();
		}

		while (!tempStack.empty())
		{
			UiBase* uiBase = tempStack.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
			}
			tempStack.pop();
		}
	}

	void UIManager::OnComplete(UiBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		if (addUI->GetIsFullScreen())
		{
			std::stack<UiBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UiBase* uiBase = uiBases.top();
				uiBases.pop();

				if (uiBase->GetIsFullScreen())
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
	}

	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Release()
	{
		for (auto ui : mUIs)
		{
			delete ui.second;
			ui.second = nullptr;
		}
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UiBase*> tempStack;

		UiBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();
			// pop하는 ui가 전체화면 일경우에,
			// 남은 ui중에 전체화면인 가장 상단의 ui 를 활성화 해주어야한다.
			if (uiBase->GetType() == type)
			{
				if (uiBase->GetIsFullScreen())
				{
					std::stack<UiBase*> uiBases = mUIBases;
					while (!uiBases.empty())
					{
						UiBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->GetIsFullScreen())
						{
							uiBase->Active();
							break;
						}
					}
				}

				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}
		}

		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}

	}

}