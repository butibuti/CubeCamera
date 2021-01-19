#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class InvisibleBlockComponent;
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
		void Check();
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();
		void RegistBlocks();
	private:
		std::vector<std::shared_ptr<InvisibleBlockComponent>> vec_invBlocks;
		std::vector< std::vector<std::shared_ptr<InvisibleBlockComponent>> >vec_vec_invBlocks;
		void SetActive(std::vector<std::shared_ptr<GameObject>> invBlocks, int id, bool flag);
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::InvisibleBlockManagerComponent)