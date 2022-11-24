#include "yaTime.h"
#include <iostream>
LARGE_INTEGER ya::Time::mCpuFrequency;
LARGE_INTEGER ya::Time::mPrevFrequency;
LARGE_INTEGER ya::Time::mCurFrequency;
float ya::Time::mDeltaTime = 0.0f;
bool ya::Time::mSlowDown = false;

void ya::Time::Initialize()
{
	QueryPerformanceFrequency(&mCpuFrequency);

	QueryPerformanceCounter(& mPrevFrequency);

}

void ya::Time::Tick()
{
	QueryPerformanceCounter(&mCurFrequency);
	float dif = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
	//delta time은 곱해주는 수?
	mDeltaTime = dif / static_cast<float>(mCpuFrequency.QuadPart);


	mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
}

void ya::Time::Render(HDC hdc)
{
	wchar_t szFloat[50] = {};

	//1초에 몇번 도는지를 계산하면 그게 내 프레임!
	int fps = static_cast<int>(1.0f / mDeltaTime);

	swprintf_s(szFloat, 50, L"fps : %d", fps);
	int strLen = wcsnlen_s(szFloat, 50);
	TextOut(hdc, 10, 10, szFloat, strLen);
}

float ya::Time::DeltaTime()
{
	if (mSlowDown)
		return mDeltaTime * 0.001f;
	else
		return mDeltaTime;
}
