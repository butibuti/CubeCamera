#include "stdafx_u.h"
#include "TestGameComponent.h"
#include"Header/GameObjects/DefaultGameComponent/ChaseComponent.h"

void ButiEngine::TestGameComponent::OnUpdate()
{
	gameObject.lock()->transform->Translate(Vector3(0, 0, -0.1f));
	//gameObject.lock()->transform->SetLocalPosition().x = 1.0f;
	//gameObject.lock()->transform->SetWorldPosition(Vector3(10,10,10));
}

void ButiEngine::TestGameComponent::OnSet()
{
}

void ButiEngine::TestGameComponent::Start()
{
	//auto chase = gameObject.lock()->GetGameComponent<ChaseComponent>();
	auto camera = gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Camera");
	if (camera.lock())
	{
		camera.lock()->transform->SetLocalPosition(Vector3(5, 10, -5));
		camera.lock()->AddGameComponent<ChaseComponent>(gameObject.lock()->transform, 0.01f);
	}
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::TestGameComponent::Clone()
{
	return ObjectFactory::Create<TestGameComponent>();
}

void ButiEngine::TestGameComponent::OnShowUI()
{
}
