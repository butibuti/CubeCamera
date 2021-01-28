#pragma once

class GameSettings
{
public:
	~GameSettings(){}
	static float BlockSize;
	static int player;
	static int block;
	static int tutorialGoal;
	static int easyGoal;
	static int defaultGoal;
	static int invisibleBlock;

	static bool CheckRight();
	static bool CheckLeft();
	static bool CheckFront();
	static bool CheckBack();

private:
	GameSettings(){}
};

