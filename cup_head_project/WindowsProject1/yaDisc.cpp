#include "yaDisc.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"

namespace ya
{
	Disc::Disc(bool right)
		:mbIntro(true)
	{
		mbRight = right;
		SetName(L"Mouse_Disc");
		SetScale({ 120,120 });

		Collider* col = new Collider();
		col->SetBulletPassing(true);
		AddComponent(col);

		mAnimator = new Animator();
		mStickAnimator = new Animator();
		if (mbRight)
			mStickAnimator->SetAddPos({ -330,-40 });
		else
			mStickAnimator->SetAddPos({ 330,-40 });

		AddComponent(mStickAnimator);
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"DiscA", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Bottlecap\\A\\mouse_bottlecap_a_00", 7, 0.08f, false, false);
		mAnimator->CreateAnimation(L"DiscB", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Bottlecap\\B\\mouse_bottlecap_b_00", 7, 0.06f, false, false);
		mAnimator->CreateAnimation(L"DiscC", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Bottlecap\\C\\mouse_bottlecap_c_00", 7, 0.07f, false, false);
		mAnimator->CreateAnimation(L"DiscD", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Bottlecap\\D\\mouse_bottlecap_d_00", 7, 0.09f, false, false);
		mAnimator->CreateAnimation(L"DiscE", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Bottlecap\\E\\mouse_bottlecap_e_00", 7, 0.075f, false, false);
		mAnimator->CreateAnimation(L"DiscF", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Bottlecap\\F\\mouse_bottlecap_f_00", 7, 0.055f, false, false);

		mStickAnimator->CreateAnimation(L"StickA", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Stick\\A\\mouse_bottlecap_stick_a_00", 4, 0.04f, false, false);
		mStickAnimator->CreateAnimation(L"StickB", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Stick\\B\\mouse_bottlecap_stick_b_00", 4, 0.04f, false, false);
		mStickAnimator->CreateAnimation(L"StickC", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Stick\\C\\mouse_bottlecap_stick_c_00", 4, 0.04f, false, false);
		mStickAnimator->CreateAnimation(L"StickD", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Stick\\D\\mouse_bottlecap_stick_d_00", 4, 0.04f, false, false);
		mStickAnimator->CreateAnimation(L"StickE", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Stick\\E\\mouse_bottlecap_stick_e_00", 4, 0.04f, false, false);
		mStickAnimator->CreateAnimation(L"StickF", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Sides\\Stick\\F\\mouse_bottlecap_stick_f_00", 4, 0.04f, false, false);

		switch (rand() % 6)
		{
			case 0:
				mAnimator->Play(L"DiscA", true);
				break;
			case 1:
				mAnimator->Play(L"DiscB", true);
				break;
			case 2:
				mAnimator->Play(L"DiscC", true);
				break;
			case 3:
				mAnimator->Play(L"DiscD", true);
				break;
			case 4:
				mAnimator->Play(L"DiscE", true);
				break;
			case 5:
				mAnimator->Play(L"DiscF", true);
				break;
		}
		switch (rand() % 6)
		{
		case 0:
			mStickAnimator->Play(L"StickA", true);
			break;
		case 1:
			mStickAnimator->Play(L"StickB", true);
			break;
		case 2:
			mStickAnimator->Play(L"StickC", true);
			break;
		case 3:
			mStickAnimator->Play(L"StickD", true);
			break;
		case 4:
			mStickAnimator->Play(L"StickE", true);
			break;
		case 5:
			mStickAnimator->Play(L"StickF", true);
			break;
		}
	}

	Disc::~Disc()
	{
	}

	void Disc::Tick()
	{
		Vector2 pos = GetPos();
		GameObject::Tick();
		if (!mbFin)
		{
			if (mbIntro)
			{
				if (mbRight)
				{
					pos.x += Time::DeltaTime() * 100;
					if (pos.x > 100)
					{
						pos.x = 100;
						mbIntro = false;
					}
				}
				else
				{
					pos.x -= Time::DeltaTime() * 100;
					if (pos.x < 1500)
					{
						pos.x = 1500;
						mbIntro = false;
					}
				}
			}
			else
			{
				if (mbGoBack)
				{
					if (mbRight)
					{
						pos.x -= Time::DeltaTime() * 100;
						if (pos.x < 0)
						{
							mbGoBack = false;
							mbGoFront = true;
							mSpeed = 300;
						}
					}
					else
					{
						pos.x += Time::DeltaTime() * 100;
						if (pos.x > 1600)
						{
							mbGoBack = false;
							mbGoFront = true;
							mSpeed = 300;
						}
					}
				}

				else if (mbGoFront)
				{
					if (!mbSpeedDown)
						mSpeed += Time::DeltaTime() * 200;
					else
						mSpeed -= Time::DeltaTime() * 400;
					if (mSpeed > 450)
						mbSpeedDown = true;

					if (mbRight)
						pos.x += mSpeed * Time::DeltaTime();
					else
						pos.x -= mSpeed * Time::DeltaTime();
					if (mbRight && mbSpeedDown)
					{
						if (pos.x < 100)
						{
							pos.x = 100;
							mbGoFront = false;
							mbSpeedDown = false;
							mbMoving = false;
						}

					}
					else if (!mbRight && mbSpeedDown)
					{
						if (pos.x > 1500)
						{
							pos.x = 1500;
							mbGoFront = false;
							mbSpeedDown = false;
							mbMoving = false;
						}
					}

				}
			}
		}
		else
		{
			mSpeed -= Time::DeltaTime() * 400;
			if (mbRight)
			{
				pos.x += mSpeed * Time::DeltaTime();
				if (pos.x < -200)
					ObjectManager::Destroy(this);
			}
			else
			{
				pos.x -= mSpeed * Time::DeltaTime();
				if (pos.x > 1800)
					ObjectManager::Destroy(this);
			}
		}
			SetPos(pos);
	}

	void Disc::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Disc::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void Disc::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Disc::OnCollisonExit(Collider* other, Collider* my)
	{
	}


	void Disc::Release()
	{
	}

}