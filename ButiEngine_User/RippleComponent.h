#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class RippleComponent :public GameComponent
	{
	public:
		RippleComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "RippleComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();

		void AnimInitialize();
	private:
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::RippleComponent)