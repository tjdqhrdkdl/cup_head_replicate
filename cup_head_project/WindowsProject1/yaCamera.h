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
		static void SetShake(bool shake) { mbShake = shake; }
		static void Shake();

		static void PositionInit(){mTarget = nullptr, mLookPosition = (mResolution / 2.0f) , mDistance = { 0,0 };}
	private:
		Camera() = default;
		~Camera() = default;

	private:
		static Vector2 mResolution; // ȭ�� �ػ�
		static Vector2 mLookPosition;
		static Vector2 mDistance; // �ػ� �ߤ�����ǥ�� ���� ī�޶��� ������
		static GameObject* mTarget;

		static eCameraEffect mEffect;
		static Picture* mCutton;    //������ �̹���
		static float mAlphaTime;
		static float mCuttonAlpha;
		static float mEndTime;

		static float mShakeTime;
		static bool mbShake;
		static bool mbVerticalShake;
	};


}