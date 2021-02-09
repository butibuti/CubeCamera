#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class MapData;
	class MapComponent;
	class MapEditorComponent :public GameComponent
	{
	public:
		MapEditorComponent() {}

		void OnUpdate()override;
		void ShowGUI()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "MapEditorComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();

	private:
		std::shared_ptr< MapData > shp_currentMapData;
		MapData*p_mapdata;

		std::shared_ptr<GameObject> Replace(const Vector3& arg_pos,const std::string& arg_blockName,const int blockNum);

		std::vector<std::vector<std::vector<std::shared_ptr<GameObject>>>>* p_mapObjectData;
		Vector3 offset;
		std::shared_ptr< MapComponent > shp_mapComponent;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::MapEditorComponent)