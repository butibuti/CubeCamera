#include "stdafx_u.h"
#include "BurstManagerComponent.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"

void ButiEngine::BurstManagerComponent::OnUpdate()
{
}

void ButiEngine::BurstManagerComponent::OnSet()
{
}

void ButiEngine::BurstManagerComponent::Start()
{
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::BurstManagerComponent::Clone()
{
	return ObjectFactory::Create<BurstManagerComponent>();
}

void ButiEngine::BurstManagerComponent::OnShowUI()
{
}

void ButiEngine::BurstManagerComponent::Burst()
{
	auto objects = GetManager().lock()->GetGameObjects(GetTagManager()->GetObjectTag("MapChip"));
	auto goals = GetManager().lock()->GetGameObjects(GetTagManager()->GetObjectTag("Goal"));
	auto invBlocks = GetManager().lock()->GetGameObjects(GetTagManager()->GetObjectTag("InvisibleBlock"));
	objects.insert(objects.end(), goals.begin(), goals.end());
	objects.insert(objects.end(), invBlocks.begin(), invBlocks.end());

	auto mapChipEnd = objects.end();
	for (auto itr = objects.begin(); itr != mapChipEnd; ++itr)
	{
		Vector3 dir = (*itr)->transform->GetWorldPosition() - Vector3::Zero;
		dir.Normalize();
		if (dir.GetLengthSqr() == 0)
		{
			dir.x = 1;
			dir.y = 1;
			dir.z = -1;
			dir.Normalize();
		}

		auto t = (*itr)->transform;
		auto anim = (*itr)->AddGameComponent<TransformAnimation>();

		anim->SetSpeed(1.0f / 60);
		anim->SetTargetTransform(t->Clone());
		anim->GetTargetTransform()->SetLocalScale(0.0f);
		anim->GetTargetTransform()->SetWorldPosition(dir * 100.0f);

		anim->SetEaseType(Easing::EasingType::EaseOutExpo);
	}
}
