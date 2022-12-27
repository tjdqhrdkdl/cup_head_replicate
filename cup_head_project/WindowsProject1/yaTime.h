#pragma once
#include "Common.h"
namespace ya {

	class Time
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);
		static float DeltaTime();
		static void SlowDown(bool slow) { mSlowDown = slow; }
		static bool isSlow() { return mSlowDown; }
		static void Stop(bool stop) { mStop = stop; }
		static bool isStop() { return mStop; }
	private:
		//cpu�� ���� �������� ���ؼ� �ð��� ����� �� �ִ�. 1�ʿ� ����? �׷� ���������ϸ� 1�� �����ž�.
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		static float mDeltaTime;
		static bool mSlowDown;
		static bool mStop;
		//���� ������ - ���� ������ �� ���� �������� ������, �󸶳� �������� �� �� �ִ�.

	};
}
