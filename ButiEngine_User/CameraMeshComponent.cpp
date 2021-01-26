#include "stdafx_u.h"
#include "CameraMeshComponent.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

void ButiEngine::CameraMeshComponent::OnUpdate()
{
}

void ButiEngine::CameraMeshComponent::OnSet()
{
}

void ButiEngine::CameraMeshComponent::Start()
{
	isShutter = false;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::CameraMeshComponent::Clone()
{
	return ObjectFactory::Create<CameraMeshComponent>();
}

void ButiEngine::CameraMeshComponent::OnShowUI()
{
}

void ButiEngine::CameraMeshComponent::Shutter()
{
	isShutter = true;
	scale = Vector3(1, 1, 1);
	gameObject.lock()->transform->SetLocalScale(scale);
}

void ButiEngine::CameraMeshComponent::Shrink()
{
	if (!isShutter)
	{
		return;
	}

	scale.x -= 0.18f;
	if (scale.x < 0.0f)
	{
		scale.x = 0.0f;
	}

	scale.y -= 0.18f;
	if (scale.y < 0.0f)
	{
		scale.y = 0.0f;
	}

	scale.z -= 0.06f;
	if (scale.z < 0.0f)
	{
		scale.z = 0.0f;
	}

	if (scale.GetLengthSqr() == 0.0f)
	{
		isShutter = false;
	}

	gameObject.lock()->transform->SetLocalScale(scale);
}
