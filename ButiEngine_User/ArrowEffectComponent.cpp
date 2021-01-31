#include "stdafx_u.h"
#include "ArrowEffectComponent.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

void ButiEngine::ArroweffectComponent::OnUpdate()
{
	progressFrame++;
	if (progressFrame > life)
	{
		gameObject.lock()->SetIsRemove(true);
		return;
	}

	auto t = gameObject.lock()->transform;
	float per = float(progressFrame) / life;
	float scale = 500.0f + Easing::Liner(per) * 1500.0f;;
	t->SetLocalScale(Vector3(scale, scale, 1));

	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent>();
	auto lightBuff = meshDraw->GetCBuffer<LightVariable>("LightBuffer");
	float alpha = 1.0f - Easing::Liner(per);
	lightBuff->Get().lightDir.w = alpha;
}

void ButiEngine::ArroweffectComponent::OnSet()
{
}

void ButiEngine::ArroweffectComponent::Start()
{
	life = 30;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::ArroweffectComponent::Clone()
{
	return ObjectFactory::Create<ArroweffectComponent>();
}

void ButiEngine::ArroweffectComponent::OnShowUI()
{
}
