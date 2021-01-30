#include "stdafx_u.h"
#include "MapComponent.h"
#include"GameSettings.h"
#include"PlayerBehavior.h"
#include"InvisibleBlockComponent.h"
#include"InvisibleBlockManagerComponent.h"
#include "..\..\Header\Common\CerealUtill.h"
#include"StageSelectManagerComponent.h"

void ButiEngine::MapComponent::OnUpdate()
{
	auto player = GetManager().lock()->GetGameObject("Player").lock();
	if (player && player->GetBehavior<PlayerBehavior>()->GetGoal())
	{
		DestoroyMapChip();
		auto sceneManager = gameObject.lock()->GetApplication().lock()->GetSceneManager();
		std::string sceneName = StageSelectManagerComponent::GetNextSceneName();
		sceneManager->LoadScene(sceneName);
		sceneManager->ChangeScene(sceneName);
		//if (GameDevice::GetInput()->TriggerKey(Keys::N))
		//{
		//	currentStageNum++;
		//	if (currentStageNum >= vec_mapData.size())
		//	{
		//		currentStageNum--; 
		//		return;
		//	}
		//	PutBlock(currentStageNum);
		//}
	}

	auto tag = GetTagManager()->GetObjectTag("MapChip");
	auto manager = GetManager().lock();
	std::vector<std::shared_ptr<GameObject>> gameObjects = manager->GetGameObjects(tag);
}

void ButiEngine::MapComponent::OnSet()
{
	currentMapData = std::make_shared<MapData>();
}

void ButiEngine::MapComponent::Start()
{
	vec_mapData.clear();
	auto mapFilePath = "Scene/" + GetManager().lock()->GetScene().lock()->GetSceneInformation()->GetSceneName() + "/mapInfo.map";
	if (Util::IsFileExistence(GlobalSettings::GetResourceDirectory()+ mapFilePath)) {

		auto input = std::make_shared<MapData>();
		InputCereal(input, mapFilePath);
		vec_mapData.push_back(*input);
	}
	else {
		vec_mapData.push_back(MapData(0));
	}

	playerPos = Vector3::Zero;
	currentStageNum = 0;
	auto invManager= GetManager().lock()->AddObjectFromCereal("InvisibleBlockManager");
	PutBlock(currentStageNum);

}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::MapComponent::Clone()
{
	auto output = ObjectFactory::Create<MapComponent>();
	output->vec_mapData = vec_mapData;

	return output;
}

void ButiEngine::MapComponent::OnShowUI()
{
}

void ButiEngine::MapComponent::PutBlock(int stageNum)
{
	auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
	invisibleBlockManager->ClearBlocks();
	DestoroyMapChip();

	*currentMapData = vec_mapData[stageNum];

	mapObjectData.clear();
	auto mapSize = currentMapData->GetSize();
	mapObjectData.resize(mapSize.y);
	for (int i = 0; i < mapSize.y; i++) {
		mapObjectData[i].resize(mapSize.z);
		for (int j = 0; j < mapSize.z; j++) {
			mapObjectData[i][j].resize(mapSize.x);
		}
	}

	std::vector<std::vector<std::vector<int>>> mapData = currentMapData->mapData;
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
				std::weak_ptr<GameObject> gameObject=std::shared_ptr<GameObject>();
				int mapNum = mapData[y][z][x];
				if (mapNum == 0) {
					mapObjectData[y][z][x] = gameObject.lock();
					continue;
				}
				else if (mapNum == GameSettings::block)
				{
					gameObject = GetManager().lock()->AddObjectFromCereal("Block", ObjectFactory::Create<Transform>(position, Vector3::Zero, scale));
				}
				else if (mapNum == GameSettings::tutorialGoal)
				{
					gameObject = GetManager().lock()->AddObjectFromCereal("TutorialGoal");
					gameObject.lock()->transform->SetWorldPosition(position);
				}
				else if (mapNum == GameSettings::easyGoal)
				{
					gameObject = GetManager().lock()->AddObjectFromCereal("EasyGoal");
					gameObject.lock()->transform->SetWorldPosition(position);
				}
				else if (mapNum == GameSettings::defaultGoal)
				{
					gameObject = GetManager().lock()->AddObjectFromCereal("DefaultGoal");
					gameObject.lock()->transform->SetWorldPosition(position);
				}
				else if (mapNum >= GameSettings::invisibleBlock&&mapNum<GameSettings::playerAndGoal)
				{
					gameObject = GetManager().lock()->AddObjectFromCereal("InvisibleBlock");
					gameObject.lock()->transform->SetWorldPosition(position);
					int id = mapNum - GameSettings::invisibleBlock;
					gameObject.lock()->GetGameComponent<InvisibleBlockComponent>()->SetID(id);
					gameObject.lock()->GetGameComponent<InvisibleBlockComponent>()->SetMapPos(Vector3(x, y, z));
				}
				else
				if (mapNum == GameSettings::player || (mapNum >= GameSettings::playerRotate_90 && mapNum <= GameSettings::playerRotate_min90)|| mapNum > GameSettings::playerAndGoal)
				{
					playerPos = Vector3(x, y, z);
					gameObject = GetManager().lock()->AddObjectFromCereal("Player", ObjectFactory::Create<Transform>(position, Vector3::Zero, scale));
					auto cameraMesh = GetManager().lock()->AddObjectFromCereal("CameraMesh", ObjectFactory::Create<Transform>(Vector3(0, 0, -0.1f), Vector3::Zero, scale));
					auto camera = GetCamera("playerCamera");
					camera.lock()->shp_transform->SetLocalPosition().z = 0.3f;
					camera.lock()->shp_transform->SetBaseTransform(gameObject.lock()->transform, true);
					cameraMesh.lock()->transform->SetBaseTransform(gameObject.lock()->transform, true);
					if (mapNum >= GameSettings::playerRotate_90 && mapNum <= GameSettings::playerRotate_min90) {
						auto rotation = (mapNum - GameSettings::playerRotate_90 +1)*90;
						gameObject.lock()->transform->RollLocalRotationY_Degrees(rotation);

						//gameObject = std::weak_ptr<GameObject>();
					}else
					if (mapNum >= GameSettings::playerAndGoal) {

						int mapNum_tenthSpace = (mapNum - GameSettings::playerAndGoal) / 10;
						int mapNum_onceSpace=(mapNum-GameSettings::playerAndGoal)%10;


						auto rotation = mapNum_onceSpace * 90;
						gameObject.lock()->transform->RollLocalRotationY_Degrees(rotation);

						if (mapNum_tenthSpace == GameSettings::tutorialGoal)
						{
							gameObject = GetManager().lock()->AddObjectFromCereal("TutorialGoal");
							gameObject.lock()->transform->SetWorldPosition(position);
						}
						else if (mapNum_tenthSpace == GameSettings::easyGoal)
						{
							gameObject = GetManager().lock()->AddObjectFromCereal("EasyGoal");
							gameObject.lock()->transform->SetWorldPosition(position);
						}
						else if (mapNum_tenthSpace == GameSettings::defaultGoal)
						{
							gameObject = GetManager().lock()->AddObjectFromCereal("DefaultGoal");
							gameObject.lock()->transform->SetWorldPosition(position);
						}
					}
				}

				mapObjectData[y][z][x] = gameObject.lock();
			}
		}
	}
	
	invisibleBlockManager->RegistBlocks();
	invisibleBlockManager->Check();
}

void ButiEngine::MapComponent::ChangeBlock(Vector3 mapPos, int mapChipNum)
{
	if (mapPos.x < 0 || mapPos.x >= currentMapData->mapData[0][0].size() ||
		mapPos.y < 0 || mapPos.y >= currentMapData->mapData.size() ||
		mapPos.z < 0 || mapPos.z >= currentMapData->mapData[0].size())
	{
		return;
	}
	currentMapData->mapData[mapPos.y][mapPos.z][mapPos.x] = mapChipNum;
}

void ButiEngine::MapComponent::DestoroyMapChip()
{
	{
		auto tag = GetTagManager()->GetObjectTag("MapChip");
		auto manager = GetManager().lock();
		std::vector<std::shared_ptr<GameObject>> gameObjects = manager->GetGameObjects(tag);

		for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
		{
			(*itr)->SetIsRemove(true);
		}
	}

	{
		auto tag = GetTagManager()->GetObjectTag("InvisibleBlock");
		auto manager = GetManager().lock();
		std::vector<std::shared_ptr<GameObject>> gameObjects = manager->GetGameObjects(tag);

		for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
		{
			(*itr)->SetIsRemove(true);
		}
	}

	{
		auto tag = GetTagManager()->GetObjectTag("Goal");
		auto manager = GetManager().lock();
		std::vector<std::shared_ptr<GameObject>> gameObjects = manager->GetGameObjects(tag);

		for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
		{
			(*itr)->SetIsRemove(true);
		}
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
				{0,0,0,0,0,0,100,0,0,0,0},
				{0,0,0,0,0,2,0,0,0,0,0},
				{0,0,2,2,0,0,0,0,101,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,1,4,0,0,0,0},
				{0,0,101,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0},
				{0,0,101,0,0,2,2,2,2,2,0},
				{0,0,0,0,0,100,100,100,0,0,0},
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

void ButiEngine::OutputCereal(const std::shared_ptr<MapData>& v, const std::string& path)
{

	std::stringstream stream;


	cereal::BinaryOutputArchive binOutArchive(stream);
	binOutArchive(v);

	std::ofstream outputFile(GlobalSettings::GetResourceDirectory() + path, std::ios::binary);

	outputFile << stream.str();

	outputFile.close();
	stream.clear();
}

void ButiEngine::InputCereal(std::shared_ptr<MapData>& v, const std::string& path)
{
	std::stringstream stream;

	std::ifstream inputFile(GlobalSettings::GetResourceDirectory() + path, std::ios::binary);

	stream << inputFile.rdbuf();

	cereal::BinaryInputArchive binInputArchive(stream);


	binInputArchive(v);
}
