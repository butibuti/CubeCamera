#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {
	class StageSelectManagerComponent :public GameComponent
	{
	public:
		StageSelectManagerComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "StageSelectManagerComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();

		static std::string GetNextSceneName();

	private:
		std::shared_ptr<RelativeTimer> animTimer;

		void RestartTimer();
		void OnPushRight();
		void OnPushLeft();

		static int stageNum;
		static int maxStageNum;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::StageSelectManagerComponent)