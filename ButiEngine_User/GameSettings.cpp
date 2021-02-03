#include "stdafx_u.h"
#include "GameSettings.h"

using namespace ButiEngine;

float GameSettings::BlockSize = 1.0f;

bool GameSettings::IsBlock(int i)
{
	if (i == block) { return true; }
	if (i == tutorialGoal) { return true; }
	if (i == easyGoal) { return true; }
	if (i == defaultGoal) { return true; }
	if (i >= invisibleBlock) { return true; }
	return false;
}

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
