#include "stdafx_u.h"
#include "CameraMeshComponent.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

void ButiEngine::CameraMeshComponent::OnUpdate()
{
	alpha -= 0.06f;
	if (alpha < 0)
	{
		alpha = 0;
	}

	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent>();
	auto lightBuff = meshDraw->GetCBuffer<LightVariable>("LightBuffer");
	lightBuff->Get().lightDir.w = alpha;
}

void ButiEngine::CameraMeshComponent::OnSet()
{
}

void ButiEngine::CameraMeshComponent::Start()
{
	alpha = 0.0f;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::CameraMeshComponent::Clone()
{
	return ObjectFactory::Create<CameraMeshComponent>();
}

void ButiEngine::CameraMeshComponent::OnShowUI()
{
}

void ButiEngine::CameraMeshComponent::Flash()
{
	alpha = 1.0f;
}
