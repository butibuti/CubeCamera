#include "stdafx_u.h"
#include "RippleComponent.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"

void ButiEngine::RippleComponent::OnUpdate()
{
	auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
	if (!anim)
	{
		gameObject.lock()->SetIsRemove(true);
	}
}

void ButiEngine::RippleComponent::OnSet()
{
}

void ButiEngine::RippleComponent::Start()
{
	AnimInitialize();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::RippleComponent::Clone()
{
	return ObjectFactory::Create<RippleComponent>();
}

void ButiEngine::RippleComponent::OnShowUI()
{
}

void ButiEngine::RippleComponent::AnimInitialize()
{
	auto t = gameObject.lock()->transform;


	auto anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
	anim->SetSpeed(1.0f / 30);
	anim->SetTargetTransform(t->Clone());
	anim->GetTargetTransform()->SetLocalScale(5.0f);
	anim->GetTargetTransform()->RollLocalRotationX_Degrees(0.1f);

	anim->SetEaseType(Easing::EasingType::EaseOutExpo);
}
