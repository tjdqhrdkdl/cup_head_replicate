#include "yaUIManager.h"
#include "yaHUD.h"
//#include "yaButton.h"
//#include "yaPanel.h"
#include "yaHealthUI.h"
#include "yaEXPointUI.h"

namespace ya
{
	std::unordered_map<eUIType, UiBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UiBase*> UIManager::mUIBases;
	UiBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{
		// ���⿡�� ui �޸𸮿� �Ҵ��ϸ� �ȴ�.
		//Button* button = new Button(eUIType::HP);
		//mUIs.insert(std::make_pair(eUIType::HP, button));
		//button->SetPos(Vector2(0.0f, 0.0f));
		////newUI->SetSize(Vector2(500.0f, 100.0f));
		//button->ImageLoad(L"HPBAR", L"..\\Resources\\Image\\HPBAR.bmp");

		//HUD* hud = new HUD(eUIType::MP);
		//mUIs.insert(std::make_pair(eUIType::MP, hud));
		//hud->SetPos(Vector2(0.0f, 100.0f));
		//hud->ImageLoad(L"HPBAR", L"..\\Resources\\Image\\HPBAR.bmp");

//		Panel* panel = new Panel(eUIType::INVENTORY);
		//mUIs.insert(std::make_pair(eUIType::INVENTORY, panel));
		////newUI->SetIsFullScreen(true);
		//panel->ImageLoad(L"BackPack", L"..\\Resources\\Image\\BackPack.bmp");
		//panel->SetPos(Vector2(100.0f, 100.0f));
		//panel->AddChild(button);
		//panel->AddChild(hud);

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
			//UI �ε� ����
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
		std::stack<UiBase*> uiBases = mUIBases;
		std::stack<UiBase*> tempStack;

		// ����� �������� ���ش�.
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
			// pop�ϴ� ui�� ��üȭ�� �ϰ�쿡,
			// ���� ui�߿� ��üȭ���� ���� ����� ui �� Ȱ��ȭ ���־���Ѵ�.
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