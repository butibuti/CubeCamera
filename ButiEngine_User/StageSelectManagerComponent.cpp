#include "stdafx_u.h"
#include "StageSelectManagerComponent.h"
#include"GameSettings.h"
#include"NumberManagerComponent.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

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

		auto obj_stageNumber = GetManager().lock()->GetGameObject("StageNumber");
		if (endTimer < 55)
		{
			float alpha = 1.0f - Easing::Liner(per);
			if (alpha < 0.0f)
			{
				alpha = 0.0f;
			}

			auto rArrow = GetManager().lock()->GetGameObject("RightArrow");
			auto lArrow = GetManager().lock()->GetGameObject("LeftArrow");

			auto rMeshDraw = rArrow.lock()->GetGameComponent<MeshDrawComponent>();
			auto lMeshDraw = lArrow.lock()->GetGameComponent<MeshDrawComponent>();

			auto rLightBuff = rMeshDraw->GetCBuffer<LightVariable>("LightBuffer");
			auto lLightBuff = lMeshDraw->GetCBuffer<LightVariable>("LightBuffer");

			rLightBuff->Get().lightDir.w = alpha;
			lLightBuff->Get().lightDir.w = alpha;
		}
		if (endTimer >= 55)
		{
			player.lock()->SetIsRemove(true);
			obj_stageNumber.lock()->GetGameComponent<NumberManagerComponent>()->Remove();
			obj_stageNumber.lock()->SetIsRemove(true);
			auto sceneManager = gameObject.lock()->GetApplication().lock()->GetSceneManager();
			std::string sceneName = "Stage" + std::to_string(stageNum) + "Scene";
			sceneManager->RemoveScene(sceneName);
			sceneManager->LoadScene(sceneName);
			sceneManager->ChangeScene(sceneName);
		}
		else if (endTimer >= 7)
		{
			stageNumberObjectScale += 50;
			auto numManager = obj_stageNumber.lock()->GetGameComponent<NumberManagerComponent>();
			numManager->SetScale(Vector3(500.0f, stageNumberObjectScale, 1.0f));
			numManager->TranslateY(50.0f);
		}
		else if (endTimer >= 0)
		{
			stageNumberObjectScale -= 60;
			auto numManager = obj_stageNumber.lock()->GetGameComponent<NumberManagerComponent>();
			numManager->SetScale(Vector3(500.0f, stageNumberObjectScale, 1.0f));
			numManager->TranslateY(20.0f);
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
	obj_stageNumber = GetManager().lock()->AddObjectFromCereal("StageNumber");
	animTimer = ObjectFactory::Create<RelativeTimer>(15);
	
	end = false;
	endTimer = 0;
	stageNumberObjectScale = 500.0f;
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
	obj_stageNumber.lock()->GetGameComponent<NumberManagerComponent>()->SetNumber(stageNum);

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
	obj_stageNumber.lock()->GetGameComponent<NumberManagerComponent>()->SetNumber(stageNum);

	GetManager().lock()->AddObjectFromCereal("ArrowEffect", ObjectFactory::Create<Transform>(Vector3(-500, 0, 9 - pushCount), Vector3(0, 0, 180), Vector3(500, 500, 1)));

	pushCount++;
	if (pushCount > 5)
	{
		pushCount = 0;
	}

	RestartAnimTimer();
}
