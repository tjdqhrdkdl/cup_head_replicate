#pragma once
#include "Common.h"


namespace ya
{
	class Picture;
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		static void SetTarget(GameObject* gameObj) { mTarget = gameObj; }
		static void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }

		static void PositionInit(){mTarget = nullptr, mLookPosition = (mResolution / 2.0f) , mDistance = { 0,0 };}
	private:
		Camera() = default;
		~Camera() = default;

	private:
		static Vector2 mResolution; // 화면 해상도
		static Vector2 mLookPosition;
		static Vector2 mDistance; // 해상도 중ㅇ심좌표와 현제 카메라의 간격차
		static GameObject* mTarget;

		static eCameraEffect mEffect;
		static Picture* mCutton;    //검정색 이미지
		static float mAlphaTime;
		static float mCuttonAlpha;
		static float mEndTime;
	};


}