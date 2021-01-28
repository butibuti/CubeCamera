#include "stdafx_u.h"
#include "RippleComponent.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

unsigned char ButiEngine::RippleComponent::count = 0;

void ButiEngine::RippleComponent::OnUpdate()
{
	if (progressFrame > life)
	{
		gameObject.lock()->SetIsRemove(true);
		count--;
		return;
	}
	progressFrame++;
	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent>();
	auto lightBuff = meshDraw->GetCBuffer<LightVariable>("LightBuffer");
	lightBuff->Get().lightDir.w = 1.0f - Easing::EaseOutExpo(float(progressFrame) / life);
	scale = Easing::EaseOutExpo(float(progressFrame) / life) * 3.0f;
	gameObject.lock()->transform->SetLocalScale(scale);
	gameObject.lock()->transform->TranslateY(-0.01f);
}

void ButiEngine::RippleComponent::OnSet()
{
}

void ButiEngine::RippleComponent::Start()
{
	count++;
	life = 60;
	scale = 0.0f;
	progressFrame = 0;
	//AnimInitialize();
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
	anim->SetSpeed(1.0f / life);
	anim->SetTargetTransform(t->Clone());
	anim->GetTargetTransform()->SetLocalScale(3.0f);
	anim->GetTargetTransform()->RollLocalRotationX_Degrees(0.1f);

	anim->SetEaseType(Easing::EasingType::EaseOutExpo);
}
