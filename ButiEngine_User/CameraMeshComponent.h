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

		void Shutter();
		void Shrink();
	private:
		Vector3 scale;
		bool isShutter;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::CameraMeshComponent)