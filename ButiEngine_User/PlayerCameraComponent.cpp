#include "stdafx_u.h"
#include "PlayerCameraComponent.h"

void ButiEngine::PlayerCameraComponent::OnUpdate()
{
}

void ButiEngine::PlayerCameraComponent::OnSet()
{
}

void ButiEngine::PlayerCameraComponent::Start()
{
	auto camera = GetCamera("playerCamera");
	//camera.lock()->SetActive(false);
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::PlayerCameraComponent::Clone()
{
	return ObjectFactory::Create<PlayerCameraComponent>();
}

void ButiEngine::PlayerCameraComponent::OnShowUI()
{
}
