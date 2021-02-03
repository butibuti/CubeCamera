#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class BurstManagerComponent :public GameComponent
	{
	public:
		BurstManagerComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "BurstManagerComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();

		void Burst();
	private:
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::BurstManagerComponent)