#include "stdafx_u.h"
#include "PlayerBehavior.h"
#include"MapComponent.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"
#include"EasyGoalComponent.h"
#include"DefaultGoalComponent.h"
#include"PlayerCameraComponent.h"
#include"InvisibleBlockManagerComponent.h"
#include"GameSettings.h"
#include"RippleComponent.h"
#include"CameraMeshComponent.h"
#include"StartPlayerDirectingComponent.h"

void ButiEngine::PlayerBehavior::OnUpdate()
{
#ifdef DEBUG
	GUI::Begin("player");
	GUI::Text(mapPos);
	if (goal)
	{
		GUI::Text("Clear");
		GUI::End();
		return; 
	}
	GUI::End();
#endif
	if (!gameObject.lock()->GetGameComponent<StartPlayerDirectingComponent>()->IsStart())
	{
		return;
	}
	if (timer->Update())
	{
		timer->Stop();
		shp_invisibleBlockManager->Check();
		Expansion();

		//”g–ä
		auto pos = gameObject.lock()->transform->GetWorldPosition();
		pos.y -= 0.3f;
		GetManager().lock()->AddObjectFromCereal("Ripple", ObjectFactory::Create<Transform>(pos, Vector3(90, 0, 0), 0.0f));

		//ƒtƒ‰ƒbƒVƒ…
		GetManager().lock()->GetGameObject("CameraMesh").lock()->GetGameComponent<CameraMeshComponent>()->Flash();
	}
	Shrink();
	Contoroll();
	CheckExistUnderBlock(mapPos);
	Fall();
}

void ButiEngine::PlayerBehavior::OnSet()
{
}

void ButiEngine::PlayerBehavior::Start()
{
	gameObject.lock()->SetObjectName("Player");
	goal = false;
	fall = false;
	afterFallPos = Vector3::Zero;
	length = 1.0f;
	shp_map = gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Map").lock()->GetGameComponent<MapComponent>();
	shp_playerCamera = gameObject.lock()->GetGameComponent<PlayerCameraComponent>();
	shp_playerCamera->SetTimer(0);
	mapPos = shp_map->GetPlayerPos();
	offset =mapPos-gameObject.lock()->transform->GetWorldPosition();
	timer = ObjectFactory::Create<RelativeTimer>(9);
	shp_invisibleBlockManager= gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
}

std::shared_ptr<ButiEngine::Behavior> ButiEngine::PlayerBehavior::Clone()
{
	return ObjectFactory::Create<PlayerBehavior>();
}

void ButiEngine::PlayerBehavior::OnCollisionEnter(std::weak_ptr<GameObject> arg_other)
{
	GameObjectTag tag = arg_other.lock()->GetGameObjectTag();
	std::string tagStr = GetTagManager()->GetTagName(tag);
	if (tagStr != "Goal")
	{
		return;
	}

	std::vector<std::vector<std::vector<int>>>& mapData = shp_map->GetCurrentMapData()->mapData;
	int mapNum = mapData[mapPos.y][mapPos.z][mapPos.x];
	int mapNum_tenthSpace = (mapNum - GameSettings::playerAndGoal) / 10;
	if (mapNum_tenthSpace == GameSettings::tutorialGoal)
	{
		goal = true;
	}
	else if (mapNum_tenthSpace == GameSettings::easyGoal && arg_other.lock()->GetGameComponent<EasyGoalComponent>()->IsActive())
	{
		goal = true;
	}
	else if (mapNum_tenthSpace == GameSettings::defaultGoal && arg_other.lock()->GetGameComponent<DefaultGoalComponent>()->IsActive())
	{
		goal = true;
	}
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

bool ButiEngine::PlayerBehavior::IsRollFinish()
{
	return !timer->IsOn();
}

void ButiEngine::PlayerBehavior::Contoroll()
{
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (anim) { return; }
	if (GameSettings::CheckRight())
	{
		OnPushRight();
		auto cubeAnim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
		if (cubeAnim) {
			nextMapPos = cubeAnim->GetTargetTransform()->GetWorldPosition().Ceil();
			nextMapPos += offset;
		}
	}
	if (GameSettings::CheckLeft())
	{
		OnPushLeft();
		auto cubeAnim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
		if (cubeAnim) {
			nextMapPos = cubeAnim->GetTargetTransform()->GetWorldPosition().Ceil();
			nextMapPos += offset;
		}
	}
	if (GameSettings::CheckFront())
	{
		OnPushFront();
		auto cubeAnim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
		if (cubeAnim) {
			nextMapPos = cubeAnim->GetTargetTransform()->GetWorldPosition().Ceil();
			nextMapPos += offset;
		}
	}
	if (GameSettings::CheckBack())
	{
		OnPushBack();
		auto cubeAnim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
		if (cubeAnim) {
			nextMapPos = cubeAnim->GetTargetTransform()->GetWorldPosition().Ceil();
			nextMapPos += offset;
		}
	}
	
}

void ButiEngine::PlayerBehavior::OnPushRight()
{
	if (fall)
	{
		RotationRight();
		return;
	}

	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x + 1, mapPos.y, mapPos.z));
	if (dir == MoveDirection::Up) { MoveRightUp(); }
	else if (dir == MoveDirection::Normal) { MoveRight(); }
	else if (dir == MoveDirection::Down) { MoveRightDown(); }
	else if (dir == MoveDirection::Fall) { MoveRightDown(); }
}

void ButiEngine::PlayerBehavior::OnPushLeft()
{
	if (fall)
	{
		RotationLeft();
		return;
	}
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x - 1, mapPos.y, mapPos.z));
	if (dir == MoveDirection::Up) { MoveLeftUp(); }
	else if (dir == MoveDirection::Normal) { MoveLeft(); }
	else if (dir == MoveDirection::Down) { MoveLeftDown(); }
	else if (dir == MoveDirection::Fall) { MoveLeftDown(); }
}

void ButiEngine::PlayerBehavior::OnPushFront()
{
	if (fall)
	{
		RotationFront();
		return;
	}
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x, mapPos.y, mapPos.z + 1));
	if (dir == MoveDirection::Up) { MoveUpFront(); }
	else if (dir == MoveDirection::Normal) { MoveFront(); }
	else if (dir == MoveDirection::Down) { MoveDownFront(); }
	else if (dir == MoveDirection::Fall) { MoveDownFront(); }
}

void ButiEngine::PlayerBehavior::OnPushBack()
{
	if (fall)
	{
		RotationBack();
		return;
	}
	MoveDirection dir = CheckMoveDirection(Vector3(mapPos.x, mapPos.y, mapPos.z - 1));
	if (dir == MoveDirection::Up) { MoveUpBack(); }
	else if (dir == MoveDirection::Normal) { MoveBack(); }
	else if (dir == MoveDirection::Down) { MoveDownBack(); }
	else if (dir == MoveDirection::Fall) { MoveDownBack(); }
}

void ButiEngine::PlayerBehavior::Expansion()
{
	scale = 1.5f;
	gameObject.lock()->transform->SetLocalScale(scale);
}

void ButiEngine::PlayerBehavior::Shrink()
{
	if (scale <= 1.0f)
	{
		return;
	}
	scale -= 0.1f;
	if (scale < 1.0f)
	{
		scale = 1.0f;
	}
	gameObject.lock()->transform->SetLocalScale(scale);
}

void ButiEngine::PlayerBehavior::MoveRightUp()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(length, length, 0));//

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(-179.99f);//
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(length, -length, 0));

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(-179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetXEaseType(Easing::EasingType::CubeRotate180);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);

		if (fall) { return; }
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(-length, -length, 0));

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetXEaseType(Easing::EasingType::CubeRotateMin180);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);

		if (fall) { return; }
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(0, -length, length));

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);
		anim->SetZEaseType(Easing::EasingType::CubeRotate180);

		if (fall) { return; }
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
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
		timer->Reset();
		timer->Start();
		shp_playerCamera->SetTimer(10);
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->Translate(Vector3(0, -length, -length));

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(-179.99f);
		anim->SetEaseType(Easing::EasingType::Liner);
		anim->SetYEaseType(Easing::EasingType::CubeRotate180);
		anim->SetZEaseType(Easing::EasingType::CubeRotateMin180);

		if (fall) { return; }
		mapPos.y--;
		mapPos.z--;
	}
}

void ButiEngine::PlayerBehavior::RotationRight()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateY(-10 * 0.05f);
		if (anim->GetTargetTransform()->GetWorldPosition().y < afterFallPos.y)
		{
			anim->GetTargetTransform()->SetWorldPosition(afterFallPos);
		}

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(-90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
	}
}

void ButiEngine::PlayerBehavior::RotationLeft()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateY(-10 * 0.05f);
		if (anim->GetTargetTransform()->GetWorldPosition().y < afterFallPos.y)
		{
			anim->GetTargetTransform()->SetWorldPosition(afterFallPos);
		}

		anim->GetTargetTransform()->RollWorldRotationZ_Degrees(90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
	}
}

void ButiEngine::PlayerBehavior::RotationFront()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateY(-10 * 0.05f);
		if (anim->GetTargetTransform()->GetWorldPosition().y < afterFallPos.y)
		{
			anim->GetTargetTransform()->SetWorldPosition(afterFallPos);
		}

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
	}
}

void ButiEngine::PlayerBehavior::RotationBack()
{
	auto t = gameObject.lock()->transform;
	auto anim = gameObject.lock()->GetGameComponent<CubeTransformAnimation>();
	if (!anim)
	{
		anim = gameObject.lock()->AddGameComponent<CubeTransformAnimation>();
		anim->SetSpeed(1.0f / 10);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->TranslateY(-10 * 0.05f);
		if (anim->GetTargetTransform()->GetWorldPosition().y < afterFallPos.y)
		{
			anim->GetTargetTransform()->SetWorldPosition(afterFallPos);
		}

		anim->GetTargetTransform()->RollWorldRotationX_Degrees(-90.0f);
		anim->SetEaseType(Easing::EasingType::Liner);
	}
}

void ButiEngine::PlayerBehavior::Fall()
{
	if (fall)
	{
		gameObject.lock()->transform->TranslateY(-0.05f);
		if (gameObject.lock()->transform->GetWorldPosition().y <= afterFallPos.y)
		{
			shp_playerCamera->SetTimer(0);
			gameObject.lock()->transform->SetWorldPosition(afterFallPos);
			fall = false;
		}
	}
}

ButiEngine::MoveDirection ButiEngine::PlayerBehavior::CheckMoveDirection(Vector3 movePos)
{
	MoveDirection output;
	std::vector<std::vector<std::vector<int>>> &mapData = shp_map->GetCurrentMapData()->mapData;

	if( movePos.x >= mapData[0][0].size() ||
		movePos.y >= mapData.size() ||
		movePos.z >= mapData[0].size() ||
		movePos.x < 0 || movePos.y < 0 || movePos.z < 0)
	{
		output = MoveDirection::No;
		return output;
	}

	if (mapData[movePos.y][movePos.z][movePos.x] == GameSettings::block)
	{
		if (movePos.y + 1 >= mapData.size() || 
			mapData[movePos.y + 1][movePos.z][movePos.x] == GameSettings::block ||
			mapData[mapPos.y + 1][mapPos.z][mapPos.x] == GameSettings::block)
		{
			output = MoveDirection::No;
		}
		else
		{
			output = MoveDirection::Up;
		}
	}
	else if (mapData[movePos.y - 1][movePos.z][movePos.x] == GameSettings::block)
	{
		output = MoveDirection::Normal;
	}
	else if (movePos.y - 2 >= 0 && mapData[movePos.y - 2][movePos.z][movePos.x] == GameSettings::block)
	{
		output = MoveDirection::Down;
	}
	else if(CheckExistUnderBlock(movePos))
	{
		output = MoveDirection::Fall;
	}
	else
	{
		output = MoveDirection::No;
	}

	return output;
}

bool ButiEngine::PlayerBehavior::CheckExistUnderBlock(Vector3 movePos)
{
	if (movePos.y - 2 < 0)
	{
		return false; 
	}
	std::vector<std::vector<std::vector<int>>>& mapData = shp_map->GetCurrentMapData()->mapData;
	if (mapData[movePos.y - 1][movePos.z][movePos.x] == GameSettings::block)
	{
		return false; 
	}
	//Vector3 offset(mapData[0][0].size() / 2, mapData.size() / 2, mapData[0].size() / 2);

	for (int y = movePos.y - 2; y >= 0; y--)
	{
		if (mapData[y][movePos.z][movePos.x] == GameSettings::block)
		{
			mapPos = Vector3(movePos.x, y + 1, movePos.z);
			afterFallPos = (mapPos - offset) * GameSettings::BlockSize;
			fall = true;
			return true;
		}
	}
	fall = false;
	return false;
}
