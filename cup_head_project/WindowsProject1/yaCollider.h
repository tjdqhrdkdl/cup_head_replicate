#pragma once
#include "Common.h"
#include "yaComponent.h"
namespace ya
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetScale(Vector2 scale) { mScale = scale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetOffset(Vector2 pos) { mOffset = pos; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetOffset() { return mOffset; }
		Vector2 GetScale() { return mScale; }

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

	private:
		Vector2 mPos;
		Vector2 mOffset;
		Vector2 mScale;
		UINT mCollisionCount;
	};
}
