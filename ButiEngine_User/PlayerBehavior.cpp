#include "stdafx_u.h"
#include "PlayerBehavior.h"
#include"MapComponent.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"
#include"EasyGoalComponent.h"
#include"DefaultGoalComponent.h"

void ButiEngine::PlayerBehavior::OnUpdate()
{
	if (goal)
	{//a
		GUI::Begin("player");
		GUI::Text("Clear");
		GUI::End();
		return; 
	}
	Contoroll();
	if (!gameObject.lock()->GetGameComponent<CubeTransformAnimation>())
	{
		CheckGoal();
	}
}

void ButiEngine::PlayerBehavior::OnSet()
{
}

void ButiEngine::PlayerBehavior::Start()
{
	length = 1.0f;
	shp_map = gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Map").lock()->GetGameComponent<MapComponent>();
	mapPos = shp_map->GetPlayerPos();
}

std::shared_ptr<ButiEngine::Behavior> ButiEngine::PlayerBehavior::Clone()
{
	return ObjectFactory::Create<PlayerBehavior>();
}

void ButiEngine::PlayerBehavior::OnCollisionEnter(std::weak_ptr<GameObject> arg_other)
{
}

void ButiEngine::PlayerBehavior::OnCollision(std::weak_ptr<GameObject> arg_other)
{
}

void ButiEngine::PlayerBehavior::OnCollisionEnd(std::weak_ptr<GameObject> arg_other)
{
}

void ButiEngine::PlayerBehavior::OnShowUI()
{
}

void ButiEngine::PlayerBehavior::Contoroll()
{
	if (GameDevice::GetInput()->TriggerKey(Keys::D))
	{
		PushD();
	}
	if (GameDevice::GetInput()->TriggerKey(Keys::A))
	{
		PushA();
	}
	if (GameDevice::GetInput()->TriggerKey(Keys::W))
	{
		PushW();
	}
	if (GameDevice::GetInput()->TriggerKey(Keys::S))
	{
		PushS();
	}
	
}

void ButiEngine::PlayerBehavior::PushD()
{
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x + 1, mapPos.y, mapPos.z));
	if (dir == MoveDirection::Up)
	{
		MoveRightUp();
	}
	else if (dir == MoveDirection::Normal)
	{
		MoveRight();
	}
	else if (dir == MoveDirection::Down)
	{
		MoveRightDown();
	}
}

void ButiEngine::PlayerBehavior::PushA()
{
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x - 1, mapPos.y, mapPos.z));
	if (dir == MoveDirection::Up)
	{
		MoveLeftUp();
	}
	else if (dir == MoveDirection::Normal)
	{
		MoveLeft();
	}
	else if (dir == MoveDirection::Down)
	{
		MoveLeftDown();
	}
}

void ButiEngine::PlayerBehavior::PushW()
{
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x, mapPos.y, mapPos.z + 1));
	if (dir == MoveDirection::Up)
	{
		MoveUpFront();
	}
	else if (dir == MoveDirection::Normal)
	{
		MoveFront();
	}
	else if (dir == MoveDirection::Down)
	{
		MoveDownFront();
	}
}

void ButiEngine::PlayerBehavior::PushS()
{
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x, mapPos.y, mapPos.z - 1));
	if (dir == MoveDirection::Up)
	{
		MoveUpBack();
	}
	else if (dir == MoveDirection::Normal)
	{
		MoveBack();
	}
	else if (dir == MoveDirection::Down)
	{
		MoveDownBack();
	}
}

void ButiEngine::PlayerBehavior::MoveRightUp()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(length, length, 0));

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(-179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetXEaseType(Easing::EasingType::CubeRotateMin180);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);

		mapPos.x++;
		mapPos.y++;
	}
}

void ButiEngine::PlayerBehavior::MoveRight()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateX(length);

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(-90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate90);

		mapPos.x++;
	}
}

void ButiEngine::PlayerBehavior::MoveRightDown()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(length, -length, 0));

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(-179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetXEaseType(Easing::EasingType::CubeRotate180);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);

		mapPos.x++;
		mapPos.y--;
	}
}

void ButiEngine::PlayerBehavior::MoveLeftUp()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(-length, length, 0));

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetXEaseType(Easing::EasingType::CubeRotate180);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);

		mapPos.x--;
		mapPos.y++;
	}
}

void ButiEngine::PlayerBehavior::MoveLeft()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim) 
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateX(-length);

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate90);

		mapPos.x--;
	}
}

void ButiEngine::PlayerBehavior::MoveLeftDown()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(-length, -length, 0));

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetXEaseType(Easing::EasingType::CubeRotateMin180);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);

		mapPos.x--;
		mapPos.y--;
	}
}

void ButiEngine::PlayerBehavior::MoveUpFront()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(0, length, length));

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);
		anim->SetZEaseType(Easing::EasingType::CubeRotateMin180);

		mapPos.y++;
		mapPos.z++;
	}
}

void ButiEngine::PlayerBehavior::MoveFront()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateZ(length);

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate90);

		mapPos.z++;
	}
}

void ButiEngine::PlayerBehavior::MoveDownFront()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(0, -length, length));

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);
		anim->SetZEaseType(Easing::EasingType::CubeRotate180);

		mapPos.y--;
		mapPos.z++;
	}
}

void ButiEngine::PlayerBehavior::MoveUpBack()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(0, length, -length));

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(-179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);
		anim->SetZEaseType(Easing::EasingType::CubeRotate180);

		mapPos.y++;
		mapPos.z--;
	}
}

void ButiEngine::PlayerBehavior::MoveBack()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateZ(-length);

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(-90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate90);

		mapPos.z--;
	}
}

void ButiEngine::PlayerBehavior::MoveDownBack()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(0, -length, -length));

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(-179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);
		anim->SetZEaseType(Easing::EasingType::CubeRotateMin180);

		mapPos.y--;
		mapPos.z--;
	}
}

ButiEngine::MoveDirection ButiEngine::PlayerBehavior::CheckMoveDirection(Vector3 movePos)
{
	MoveDirection output;
	std::vector<std::vector<std::vector<int>>> mapData = shp_map->GetCurrentMapData().mapData;

	if(movePos.x >= mapData[0][0].size() || movePos.y >= mapData.size() || movePos.z >= mapData[0].size() ||
		movePos.x < 0 || movePos.y < 0 || movePos.z < 0)
	{
		output = MoveDirection::No;
		return output;
	}

	int block = 2;
	if (mapData[movePos.y][movePos.z][movePos.x] == block)
	{
		if (movePos.y + 1 >= mapData.size() || mapData[movePos.y + 1][movePos.z][movePos.x] == block)
		{
			output = MoveDirection::No;
		}
		else
		{
			output = MoveDirection::Up;
		}
	}
	else if (mapData[movePos.y - 1][movePos.z][movePos.x] == block)
	{
		output = MoveDirection::Normal;
	}
	else if (movePos.y - 2 >= 0 && mapData[movePos.y - 2][movePos.z][movePos.x] == block)
	{
		output = MoveDirection::Down;
	}
	else
	{
		output = MoveDirection::No;
	}

	return output;
}

void ButiEngine::PlayerBehavior::CheckGoal()
{
	std::vector<std::vector<std::vector<int>>> mapData = shp_map->GetCurrentMapData().mapData;
	int mapNum = mapData[mapPos.y][mapPos.z][mapPos.x];
	int tutorialGoal = 3;
	int easyGoal = 4;
	int defaultGoal = 5;
	if (mapNum == tutorialGoal)
	{
		goal = true;
	}
	else if (mapNum == easyGoal && GetManager().lock()->GetGameObject("EasyGoal").lock()->GetGameComponent<EasyGoalComponent>()->GetActive())
	{
		goal = true;
	}
	else if (mapNum == defaultGoal && GetManager().lock()->GetGameObject("DefaultGoal").lock()->GetGameComponent<DefaultGoalComponent>()->GetActive())
	{
		goal = true;
	}
}
