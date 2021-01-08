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

		void SetTimer(const unsigned int frame);
	private:
		std::shared_ptr<RelativeTimer> shp_timer = nullptr;
		bool isShutter;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::PlayerCameraComponent)