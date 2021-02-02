#include "stdafx_u.h"
#include "ShakeComponent.h"

void ButiEngine::ShakeComponent::OnUpdate()
{
	if (!start)
	{
		return;
	}

	float x = ButiRandom::GetRandom(-amplitude, amplitude, 100);
	float y = ButiRandom::GetRandom(-amplitude, amplitude, 100);
	float z = ButiRandom::GetRandom(-amplitude, amplitude, 100);

	Vector3 newPos = defaultPos + Vector3(x, y, z);

	gameObject.lock()->transform->SetWorldPosition(newPos);
}

void ButiEngine::ShakeComponent::OnSet()
{
}

void ButiEngine::ShakeComponent::Start()
{
	start = false;
	amplitude = 0.0f;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::ShakeComponent::Clone()
{
	return ObjectFactory::Create<ShakeComponent>();
}

void ButiEngine::ShakeComponent::OnShowUI()
{
}

void ButiEngine::ShakeComponent::Start(float arg_amplitude)
{
	amplitude = arg_amplitude;
	start = true;
}

void ButiEngine::ShakeComponent::Stop()
{
	gameObject.lock()->transform->SetWorldPosition(defaultPos);
	amplitude = 0.0f;
	start = false;
}
