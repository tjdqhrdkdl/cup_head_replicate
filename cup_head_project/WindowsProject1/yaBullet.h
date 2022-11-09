#pragma once
#include "yaGameObject.h"
namespace ya {

	class Bullet : public GameObject
	{
	public:
		Bullet();
		~Bullet();

		void SetDir(Vector2 vec) { mDir = vec; }
		Vector2 GetDir() { return mDir; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;
	private:
		Vector2 mDir;
	};
}
