#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class CameraMeshComponent :public GameComponent
	{
	public:
		CameraMeshComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "CameraMeshComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();

		void Flash();
	private:
		float alpha;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::CameraMeshComponent)