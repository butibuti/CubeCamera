#include "stdafx_u.h"
#include "GoalAuraComponent.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

void ButiEngine::GoalAuraComponent::OnUpdate()
{
	if (progressFrame > life)
	{
		gameObject.lock()->SetIsRemove(true);
		return;
	}

	progressFrame++;
	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent>();
	auto lightBuff = meshDraw->GetCBuffer<LightVariable>("LightBuffer");
	lightBuff->Get().lightDir.w = 1.0f - Easing::EaseOutExpo(float(progressFrame) / life);
}

void ButiEngine::GoalAuraComponent::OnSet()
{
}

void ButiEngine::GoalAuraComponent::Start()
{
	progressFrame = 0;
	life = 60;
	AnimInitialize();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::GoalAuraComponent::Clone()
{
	return ObjectFactory::Create<GoalAuraComponent>();
}

void ButiEngine::GoalAuraComponent::OnShowUI()
{
}

void ButiEngine::GoalAuraComponent::AnimInitialize()
{
	auto t = gameObject.lock()->transform;

	
	auto anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
	anim->SetSpeed(1.0f / life);
	anim->SetTargetTransform(t->Clone());
	anim->GetTargetTransform()->SetLocalScale(3.0f);
	anim->GetTargetTransform()->RollLocalRotationX_Degrees(0.1f);

	anim->SetEaseType(Easing::EasingType::EaseOutQuart);
	
}
