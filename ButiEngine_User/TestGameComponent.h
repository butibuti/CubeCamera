#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class TestGameComponent :public GameComponent
	{
	public:
		TestGameComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "TestGameComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();
	private:
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::TestGameComponent)