#include "stdafx_u.h"
#include "TitleManagerComponent.h"

void ButiEngine::TitleManagerComponent::OnUpdate()
{
	if (GameDevice::GetInput()->GetAnyButtonTrigger() || GameDevice::GetInput()->TriggerKey(Keys::Space))
	{
		auto sceneManager = gameObject.lock()->GetApplication().lock()->GetSceneManager();
		sceneManager->LoadScene("StageSelectScene");
		sceneManager->ChangeScene("StageSelectScene");
	}
}

void ButiEngine::TitleManagerComponent::OnSet()
{
}

void ButiEngine::TitleManagerComponent::Start()
{
	gameObject.lock()->GetApplication().lock()->GetGraphicDevice()->SetClearColor(Vector4(0.025f, 0.025f, 0.025f, 1.0f));
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::TitleManagerComponent::Clone()
{
	return ObjectFactory::Create<TitleManagerComponent>();
}

void ButiEngine::TitleManagerComponent::OnShowUI()
{
}
