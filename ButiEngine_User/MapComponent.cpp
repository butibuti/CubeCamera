#include "stdafx_u.h"
#include "MapComponent.h"
#include"GameSettings.h"
#include"PlayerBehavior.h"

void ButiEngine::MapComponent::OnUpdate()
{
	auto player = GetManager().lock()->GetGameObject("Player").lock();
	if (player && player->GetBehavior<PlayerBehavior>()->GetGoal())
	{
		if (GameDevice::GetInput()->TriggerKey(Keys::N))
		{
			currentStageNum++;
			if (currentStageNum >= vec_mapData.size())
			{
				currentStageNum--; 
				return;
			}
			PutBlock(currentStageNum);
		}
	}
}

void ButiEngine::MapComponent::OnSet()
{
}

void ButiEngine::MapComponent::Start()
{
	currentMapData.mapData.clear();
	playerPos = Vector3::Zero;
	vec_mapData.push_back(MapData(0));
	vec_mapData.push_back(MapData(1));
	currentStageNum = 0;
	PutBlock(currentStageNum);
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::MapComponent::Clone()
{
	auto output = ObjectFactory::Create<MapComponent>();
	output->currentMapData = currentMapData;
	output->vec_mapData = vec_mapData;

	return output;
}

void ButiEngine::MapComponent::OnShowUI()
{
}

void ButiEngine::MapComponent::PutBlock(int stageNum)
{
	DestoroyMapChip();

	currentMapData = vec_mapData[stageNum];

	std::vector<std::vector<std::vector<int>>> mapData = currentMapData.mapData;
	Vector3 scale(GameSettings::BlockSize, GameSettings::BlockSize, GameSettings::BlockSize);
	Vector3 offset(mapData[0][0].size() / 2, mapData.size() / 2, mapData[0].size() / 2);

	for (unsigned int y = 0; y < mapData.size(); y++)
	{
		for (unsigned int z = 0; z < mapData[y].size(); z++)
		{
			for (unsigned int x = 0; x < mapData[y][z].size(); x++)
			{
				Vector3 position(x, y, z);
				position -= offset;
				position *= GameSettings::BlockSize;

				switch (mapData[y][z][x])
				{
				case 0://なんもない
					break;
				case 1://プレイヤー開始地点
				{
					playerPos = Vector3(x, y, z);
					auto gameObject = GetManager().lock()->AddObjectFromCereal("Player", ObjectFactory::Create<Transform>(position, Vector3::Zero, scale));
					auto cameraMesh = GetManager().lock()->AddObjectFromCereal("CameraMesh", ObjectFactory::Create<Transform>(Vector3::Zero, Vector3::Zero, scale));
					auto camera = GetCamera("playerCamera");
					camera.lock()->shp_transform->SetBaseTransform(gameObject.lock()->transform, true);
					cameraMesh.lock()->transform->SetBaseTransform(gameObject.lock()->transform, true);

				break;
				}
				case 2://ブロック
				{
					auto gameObject = GetManager().lock()->AddObjectFromCereal("Block", ObjectFactory::Create<Transform>(position, Vector3::Zero, scale));
					break;
				}
				case 3://ゴール
				{
					auto gameObject = GetManager().lock()->AddObjectFromCereal("TutorialGoal");
					gameObject.lock()->transform->SetWorldPosition(position);
					break;
				}
				case 4://ゴール
				{
					auto gameObject = GetManager().lock()->AddObjectFromCereal("EasyGoal");
					gameObject.lock()->transform->SetWorldPosition(position);
					break;
				}
				case 5://見たら出現するゴール
				{
					auto gameObject = GetManager().lock()->AddObjectFromCereal("DefaultGoal");
					gameObject.lock()->transform->SetWorldPosition(position);
					break;
				}
				default:
					break;
				};
			}
		}
	}
}

void ButiEngine::MapComponent::DestoroyMapChip()
{
	auto tag = GetTagManager()->GetObjectTag("MapChip");
	auto manager = GetManager().lock();
	std::vector<std::shared_ptr<GameObject>> gameObjects = manager->GetGameObjects(tag);

	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
	{
		(*itr)->SetIsRemove(true);
	}
}

ButiEngine::MapData::MapData(int stageNum)
{
	if (stageNum == 0)
	{
		mapData =
		{
			{
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,0,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2,2,2,2},
			},
			{
				{3,0,0,0,0,0,0,0,0,0,4},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,2,0,0,0,0,0},
				{0,0,2,2,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,1,4,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,2,2,2,2,2,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,5},
			},
			{
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,2,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,2,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
			},
			{
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,2,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
			},
		};
	}
	else if (stageNum == 1)
	{
		mapData =
		{
			{
				{2,2,2},
				{2,2,2},
				{2,2,2},
			},
			{
				{0,0,0},
				{0,1,0},
				{0,2,0},
			},
			{
				{0,0,0},
				{0,0,0},
				{0,0,2},
			},
			{
				{0,0,0},
				{0,0,2},
				{0,0,0},
			},
			{
				{0,0,2},
				{0,0,0},
				{0,0,0},
			},
		};
	}
}
