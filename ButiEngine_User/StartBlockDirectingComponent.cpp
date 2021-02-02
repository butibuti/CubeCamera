#include "stdafx_u.h"
#include "StartBlockDirectingComponent.h"

void ButiEngine::StartBlockDirectingComponent::OnUpdate()
{
}

void ButiEngine::StartBlockDirectingComponent::OnSet()
{
}

void ButiEngine::StartBlockDirectingComponent::Start()
{
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::StartBlockDirectingComponent::Clone()
{
	return ObjectFactory::Create<StartBlockDirectingComponent>();
}

void ButiEngine::StartBlockDirectingComponent::OnShowUI()
{
}
