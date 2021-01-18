#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class InvisibleBlockManagerComponent :public GameComponent
	{
	public:
		InvisibleBlockManagerComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "InvisibleBlockManagerComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();
	private:
		void SetActive(std::vector<std::shared_ptr<GameObject>> invBlocks, int id, bool flag);
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::InvisibleBlockManagerComponent)