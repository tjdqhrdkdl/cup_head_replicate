#pragma once
#include "Common.h"
#include "yaUiBase.h"


namespace ya
{
	/// <summary>
	/// �÷��̾��� ���ۿ� ������ ���� ���� (��ġ ũ����)
	/// ��ü ȭ�� UI
	/// �⺻ UI 
	/// HUD �̹����� ������ �մ� UI
	/// ��ư
	/// �� UI �� �ڽı����� �������� �ٸ� ui���� �����ؼ�
	/// ���� �����̴� �ϳ��� ū UI �� �ɼ� �ֵ�.
	/// </summary>
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(eUIType type);
		static void Tick();
		static void Render(HDC hdc);
		static void OnComplete(UiBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

		template <typename T>
		static T* GetUiInstant(eUIType type)
		{
			return dynamic_cast<T*>(mUIs[type]);
		}



	private:
		static std::unordered_map<eUIType, UiBase*> mUIs;
		static std::queue<eUIType> mRequestUIQueue;
		static std::stack<UiBase*> mUIBases;
		static UiBase* mCurrentData;
	};
}
