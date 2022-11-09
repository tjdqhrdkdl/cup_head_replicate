#include "yaMeteor.h"
#include "yaTime.h"
#include "yaScenemanager.h"
ya::Meteor::Meteor()
	:mSpeed(1.0f)
	,mPen(nullptr)
	,mBrush(nullptr)
{
	int red, blue, green;
	red = rand() % 256;
	blue = rand() % 256;
	green = rand() % 256;
	mPen = CreatePen(PS_SOLID, 1, RGB(red,blue,green));
	mBrush = CreateSolidBrush(RGB(red, blue, green));

}
void ya::Meteor::Render(HDC hdc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	ya::Pen pen = ya::Pen(hdc, mPen,0);
	ya::Brush brush = ya::Brush(hdc, mBrush,0);
	Ellipse(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);


	GameObject::Render(hdc);

}

void ya::Meteor::Tick()
{
	GameObject::Tick();
	Vector2 pos = GetPos();
	pos.y += 300.0f * Time::DeltaTime();
	pos.x -= 150.0f * Time::DeltaTime();
	SetPos(pos);

	if (pos.OutWindow())
	{
		SceneManager::GetCurScene()->DeleteGameObject(this);
		delete this;
	}
}
