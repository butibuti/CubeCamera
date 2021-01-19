#include"Header/GameComponentHeader.h"

#ifndef TransformAnim_H
#define TransformAnim_H


namespace ButiEngine {



	class TransformAnimation :public GameComponent
	{
	public:
		std::string GetGameComponentName()override {
			return "TransformAnimation";
		}
		void OnUpdate()override;
		std::shared_ptr<Transform> GetInitTransform();
		std::shared_ptr<Transform> GetTargetTransform();
		virtual void SetInitTransform(std::shared_ptr<Transform> arg_shp_InitTransform);
		void SetEaseType(const Easing::EasingType type);
		void SetSpeed(const float arg_speed);
		void SetTime(const float arg_time);
		void SetReverse(const bool isReverse);
		std::shared_ptr<GameComponent> Clone()override;

		virtual void _cdecl SetTargetTransform(std::shared_ptr<Transform> arg_shp_targetTransform);
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
			archive(speed);
			archive(t);
			archive(shp_targetTransform);
			archive(shp_initTransform);
			archive(easeType);
			archive(isReverse);
		}
		void OnShowUI()override;
		virtual void PositionSet();
		void OnSet()override;
	protected:
		int direction = 1;
		float t = 0;
		std::shared_ptr<Transform> shp_targetTransform;
		Quat initRotate;
		Quat targetRotate;
		std::shared_ptr<Transform> shp_initTransform;
		float speed = 0.002f;;
		Easing::EasingType easeType = Easing::EasingType::EaseIn;
		bool isReverse = false;
	};

}

BUTI_REGIST_GAMECOMPONENT(ButiEngine::TransformAnimation)


#endif // !TransformAnim_H