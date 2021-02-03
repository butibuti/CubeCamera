#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {

	struct FloatBlockData {
		float time;
		int direction=1;
		int moveDir=1;
		float movePase = 1.0;
		float moveTime = 0.0;
		float moveMax;
		Vector3 initPos;
	};

	class BackGround :public GameComponent
	{
	public:
		BackGround() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "BackGround";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
			archive(pase);
			archive(endColor);
			archive(startColor);
		}
		void OnShowUI();

	private:
		Vector3 center;
		float pase;
		Vector4 endColor;
		Vector4 startColor;
		
		std::vector<std::shared_ptr<Transform>> vec_shp_transform;
		std::vector<FloatBlockData> vec_blockData;
		std::vector<std::shared_ptr<CBuffer<LightVariable>>>vec_shp_lightBuffer;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::BackGround)