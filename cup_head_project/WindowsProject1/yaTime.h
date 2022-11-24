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
	
	private:
		//cpu의 고유 진동수를 통해서 시간을 계산할 수 있다. 1초에 만번? 그럼 만번진동하면 1초 지난거야.
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		static float mDeltaTime;
		static bool mSlowDown;
		//현재 진동수 - 이전 진동수 를 고유 진동수로 나누면, 얼마나 지났는지 알 수 있다.

	};
}
