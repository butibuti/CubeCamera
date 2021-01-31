#include "stdafx_u.h"
#include "StageSelectManagerComponent.h"
#include"GameSettings.h"

int ButiEngine::StageSelectManagerComponent::stageNum = 0;
int ButiEngine::StageSelectManagerComponent::maxStageNum = 0;

void ButiEngine::StageSelectManagerComponent::OnUpdate()
{
	GUI::Begin("StageSelect");
	GUI::Text(stageNum);
	GUI::End();
	if (!animTimer->IsOn() && !end)
	{
		if (GameSettings::CheckRight())
		{
			OnPushRight();
		}
		else if (GameSettings::CheckLeft())
		{
			OnPushLeft();
		}
		else if (GameDevice::GetInput()->TriggerKey(Keys::Space))
		{
			end = true;
		}
	}

	if (end)
	{
		endTimer++;

		auto player = GetManager().lock()->GetGameObject("PlayerModel");
		float per = float(endTimer) / 30;
		float playerX = per;
		float playerY = Easing::Parabola(per) + (-1.6f);
		float playerZ = -per + 3.0f;
		player.lock()->transform->SetWorldPosition(Vector3(playerX, playerY, playerZ));

		player.lock()->transform->RollLocalRotationX_Degrees(-5.0f);

		if (endTimer >= 55)
		{
			player.lock()->SetIsRemove(true);
			auto sceneManager = gameObject.lock()->GetApplication().lock()->GetSceneManager();
			std::string sceneName = "Stage" + std::to_string(stageNum) + "Scene";
			sceneManager->LoadScene(sceneName);
			sceneManager->ChangeScene(sceneName);
		}
	}

	if (animTimer->Update())
	{
		animTimer->Stop();
	}
}

void ButiEngine::StageSelectManagerComponent::OnSet()
{
}

void ButiEngine::StageSelectManagerComponent::Start()
{
	GetManager().lock()->AddObjectFromCereal("PlayerModel");
	animTimer = ObjectFactory::Create<RelativeTimer>(10);
	
	end = false;
	endTimer = 0;
	pushCount = 0;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::StageSelectManagerComponent::Clone()
{
	return ObjectFactory::Create<StageSelectManagerComponent>();
}

void ButiEngine::StageSelectManagerComponent::OnShowUI()
{
}

std::string ButiEngine::StageSelectManagerComponent::GetNextSceneName()
{
	stageNum++;
	if (stageNum > maxStageNum)
	{
		stageNum--;
		return "StageSelectScene";
	}

	std::string nextSceneName = "Stage" + std::to_string(stageNum) + "Scene";
	return nextSceneName;
}

void ButiEngine::StageSelectManagerComponent::RestartAnimTimer()
{
	animTimer->Reset();
	animTimer->Start();
}

void ButiEngine::StageSelectManagerComponent::OnPushRight()
{
	stageNum++;
	if (stageNum > maxStageNum)
	{
		stageNum = 0;
	}

	GetManager().lock()->AddObjectFromCereal("ArrowEffect", ObjectFactory::Create<Transform>(Vector3(500, 0, 9 - pushCount), 0.0f, Vector3(500, 500, 1)));

	pushCount++;
	if (pushCount > 5)
	{
		pushCount = 0;
	}

	RestartAnimTimer();
}

void ButiEngine::StageSelectManagerComponent::OnPushLeft()
{
	stageNum--;
	if (stageNum < 0)
	{
		stageNum = maxStageNum;
	}

	GetManager().lock()->AddObjectFromCereal("ArrowEffect", ObjectFactory::Create<Transform>(Vector3(-500, 0, 9 - pushCount), Vector3(0, 0, 180), Vector3(500, 500, 1)));

	pushCount++;
	if (pushCount > 5)
	{
		pushCount = 0;
	}

	RestartAnimTimer();
}
