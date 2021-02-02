#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class CameraController :public GameComponent
	{
	public:
		CameraController() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "CameraController";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
			archive(pase);
		}
		void OnShowUI();

		void ZoomInOut();
	private:
		Vector3 offset;
		std::shared_ptr<GameObject> shp_cameraAxis;
		float pase;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::CameraController)