#include "stdafx_u.h"
#include "StageSelectManagerComponent.h"

void ButiEngine::StageSelectManagerComponent::OnUpdate()
{
}

void ButiEngine::StageSelectManagerComponent::OnSet()
{
}

void ButiEngine::StageSelectManagerComponent::Start()
{
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::StageSelectManagerComponent::Clone()
{
	return ObjectFactory::Create<StageSelectManagerComponent>();
}

void ButiEngine::StageSelectManagerComponent::OnShowUI()
{
}
