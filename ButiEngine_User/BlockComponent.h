#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class MapComponent;
	class BlockComponent :public GameComponent
	{
	public:
		BlockComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "BlockComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
			archive(pase);
			archive(current);
		}
		void OnShowUI();
	private:
		std::weak_ptr<MapComponent> wkp_mapComponent;
		float pase;
		float current=0.5f;
		std::shared_ptr<CBuffer<LightVariable>> shp_lightBuffer;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::BlockComponent)

