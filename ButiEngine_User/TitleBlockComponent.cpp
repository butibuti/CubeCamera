#include "stdafx_u.h"
#include "TitleBlockComponent.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"

void ButiEngine::TitleBlockComponent::OnUpdate()
{
	angle += 0.05f;
	theta += 0.05f;
	Vector3 pos = gameObject.lock()->transform->GetWorldPosition();
	pos.y = std::sinf(theta) * 0.05f + defaultY;
	gameObject.lock()->transform->RollLocalRotationY_Degrees(0.5f);
	gameObject.lock()->transform->SetWorldPosition(pos);
}

void ButiEngine::TitleBlockComponent::OnSet()
{
	/*auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	if (meshDraw) {
		auto mesh = gameObject.lock()->GetResourceContainer()->GetModelTag("Model/Cubes/NormalBlock.b3m");
		meshDraw->SetModelTag(mesh);
		meshDraw->ReRegist();
	}*/
}

void ButiEngine::TitleBlockComponent::Start()
{
	defaultY = gameObject.lock()->transform->GetWorldPosition().y;
	angle = ButiRandom::GetRandom(0.0f, 360.0f, 100);
	theta = ButiRandom::GetRandom(0.0f, 360.0f, 100);
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::TitleBlockComponent::Clone()
{
	return ObjectFactory::Create<TitleBlockComponent>();
}

void ButiEngine::TitleBlockComponent::OnShowUI()
{
}
