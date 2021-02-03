#include "stdafx_u.h"
#include "InvisibleBlockManagerComponent.h"
#include"InvisibleBlockComponent.h"
#include"PlayerCameraComponent.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"

void ButiEngine::InvisibleBlockManagerComponent::OnUpdate()
{
}

void ButiEngine::InvisibleBlockManagerComponent::OnSet()
{
}

void ButiEngine::InvisibleBlockManagerComponent::Start()
{
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::InvisibleBlockManagerComponent::Clone()
{
	return ObjectFactory::Create<InvisibleBlockManagerComponent>();
}

void ButiEngine::InvisibleBlockManagerComponent::OnShowUI()
{
}

void ButiEngine::InvisibleBlockManagerComponent::CheckSeen()
{
	std::vector<int> IDs;
	auto blocks = GetManager().lock()->GetGameObjects(GetTagManager()->GetObjectTag("InvisibleBlock"));
	auto end = blocks.end();
	for (auto itr = blocks.begin(); itr != end; ++itr)
	{
		auto invBlockComp = (*itr)->GetGameComponent<InvisibleBlockComponent>();
		if (invBlockComp->GetSeen())
		{
			int id = invBlockComp->GetID();
			if (std::find(IDs.begin(), IDs.end(), id) == IDs.end())
			{
				IDs.push_back(id);
			}
		}
	}
	auto idEnd = IDs.end();
	for (auto idItr = IDs.begin(); idItr != idEnd; ++idItr)
	{
		for (auto itr = blocks.begin(); itr != end; ++itr)
		{
			auto invBlockComp = (*itr)->GetGameComponent<InvisibleBlockComponent>();

			if (invBlockComp->GetID() == *idItr)
			{
				invBlockComp->Active();
			}
		}
	}
}

void ButiEngine::InvisibleBlockManagerComponent::Reset()
{
	auto blocks = GetManager().lock()->GetGameObjects(GetTagManager()->GetObjectTag("InvisibleBlock"));
	auto end = blocks.end();
	for (auto itr = blocks.begin(); itr != end; ++itr)
	{
		auto invBlockComp = (*itr)->GetGameComponent<InvisibleBlockComponent>();
		invBlockComp->UnActive();
		invBlockComp->SetSeen(false);
	}
}
