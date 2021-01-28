#include "stdafx_u.h"
#include "GoalAuraComponent.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"

void ButiEngine::GoalAuraComponent::OnUpdate()
{
	auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
	if (!anim)
	{
		gameObject.lock()->SetIsRemove(true);
	}
}

void ButiEngine::GoalAuraComponent::OnSet()
{
}

void ButiEngine::GoalAuraComponent::Start()
{
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
	anim->SetSpeed(1.0f / 30);
	anim->SetTargetTransform(t->Clone());
	anim->GetTargetTransform()->SetLocalScale(3.0f);
	anim->GetTargetTransform()->RollLocalRotationX_Degrees(0.1f);

	anim->SetEaseType(Easing::EasingType::EaseOutQuart);
	
}
