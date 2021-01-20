#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {


	class MapEditorComponent :public GameComponent
	{
	public:
		MapEditorComponent() {}

		void OnUpdate()override{}
		void OnSet()override{}
		void Start()override{}
		std::string GetGameComponentName()override {
			return "MapEditorComponent";
		}
		std::shared_ptr<GameComponent> Clone()override {
			return nullptr;
		}
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI(){}

	private:
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::MapEditorComponent)