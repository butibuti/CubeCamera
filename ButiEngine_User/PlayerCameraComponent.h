#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class PlayerCameraComponent :public GameComponent
	{
	public:
		PlayerCameraComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "PlayerCameraComponent";
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
BUTI_REGIST_GAMECOMPONENT(ButiEngine::PlayerCameraComponent)