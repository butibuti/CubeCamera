#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {

	struct MapData
	{
		MapData(){}
		MapData(int stageNum);
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(mapData);
		}
		std::vector<std::vector<std::vector<int>>> mapData;
	};

	class MapComponent :public GameComponent
	{
	public:
		MapComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "MapComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
			archive(vec_mapData);
		}
		void OnShowUI();

		void PutBlock(int stageNum);
		std::shared_ptr< MapData >GetCurrentMapData() { return currentMapData; }
		Vector3 GetPlayerPos() { return playerPos; }
		void ChangeBlock(Vector3 mapPos, int mapChipNum);
	private:
		std::vector<MapData> vec_mapData;
		std::shared_ptr< MapData > currentMapData;
		Vector3 playerPos;
		int currentStageNum;

		void DestoroyMapChip();
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::MapComponent)