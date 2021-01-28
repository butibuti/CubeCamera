#include "stdafx_u.h"
#include "GameSettings.h"

using namespace ButiEngine;

float GameSettings::BlockSize = 1.0f;
int GameSettings::player = 1;
int GameSettings::block = 2;
int GameSettings::tutorialGoal = 3;
int GameSettings::easyGoal = 4;
int GameSettings::defaultGoal = 5;
int GameSettings::invisibleBlock = 100;

bool GameSettings::CheckRight()
{
	bool dKey = GameDevice::GetInput()->CheckKey(Keys::D);
	bool rightButton = GameDevice::GetInput()->GetPadButton(PadButtons::XBOX_RIGHT);
	Vector2 leftStickVector = GameDevice::GetInput()->GetLeftStick();
	bool stickRight = leftStickVector.x > 0.3f;

	return (dKey || rightButton || stickRight);
}

bool GameSettings::CheckLeft()
{
	bool aKey = GameDevice::GetInput()->CheckKey(Keys::A);
	bool leftButton = GameDevice::GetInput()->GetPadButton(PadButtons::XBOX_LEFT);
	Vector2 leftStickVector = GameDevice::GetInput()->GetLeftStick();
	bool stickLeft = leftStickVector.x < -0.3f;

	return (aKey || leftButton || stickLeft);
}

bool GameSettings::CheckFront()
{
	bool wKey = GameDevice::GetInput()->CheckKey(Keys::W);
	bool upButton = GameDevice::GetInput()->GetPadButton(PadButtons::XBOX_UP);
	Vector2 leftStickVector = GameDevice::GetInput()->GetLeftStick();
	bool stickUp = leftStickVector.y > 0.3f;

	return (wKey || upButton || stickUp);
}

bool GameSettings::CheckBack()
{
	bool sKey = GameDevice::GetInput()->CheckKey(Keys::S);
	bool downButton = GameDevice::GetInput()->GetPadButton(PadButtons::XBOX_DOWN);
	Vector2 leftStickVector = GameDevice::GetInput()->GetLeftStick();
	bool stickDown = leftStickVector.y < -0.3f;

	return (sKey || downButton || stickDown);
}
