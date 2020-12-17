#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {

	struct MapData
	{
		MapData();
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
		MapData GetCurrentMapData() { return currentMapData; }
		Vector3 GetPlayerPos() { return playerPos; }
	private:
		std::vector<MapData> vec_mapData;
		MapData currentMapData;
		Vector3 playerPos;
		int currentStageNum;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::MapComponent)