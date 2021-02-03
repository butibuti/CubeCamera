#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class ArroweffectComponent :public GameComponent
	{
	public:
		ArroweffectComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "ArroweffectComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();
	private:
		int life;
		int progressFrame;
	};
}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::ArroweffectComponent)