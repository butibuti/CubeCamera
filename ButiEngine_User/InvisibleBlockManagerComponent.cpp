#include "stdafx_u.h"
#include "InvisibleBlockManagerComponent.h"
#include"InvisibleBlockComponent.h"
#include"PlayerCameraComponent.h"

void ButiEngine::InvisibleBlockManagerComponent::OnUpdate()
{
	std::vector<int> vec_seenInvBlockIDs;
	std::vector<int> vec_hitPlayerBlockIDs;

	auto tag = gameObject.lock()->GetApplication().lock()->GetGameObjectTagManager()->GetObjectTag("InvisibleBlock");
	auto vec_invBlocks = GetManager().lock()->GetGameObjects(tag);
	{
		auto end = vec_invBlocks.end();
		for (auto itr = vec_invBlocks.begin(); itr != end; ++itr)
		{
			(*itr)->GetGameComponent<InvisibleBlockComponent>()->SetActive(false);
		}

		for (auto itr = vec_invBlocks.begin(); itr != end; ++itr)
		{
			auto inv = (*itr)->GetGameComponent<InvisibleBlockComponent>();
			if (inv->IsSeen())
			{
				vec_seenInvBlockIDs.push_back(inv->GetID());
			}
		}

		for (auto itr = vec_invBlocks.begin(); itr != end; ++itr)
		{
			auto inv = (*itr)->GetGameComponent<InvisibleBlockComponent>();
			if (inv->IsHitPlayer())
			{
				vec_hitPlayerBlockIDs.push_back(inv->GetID());
			}
		}
	}

	{
		auto end = vec_seenInvBlockIDs.end();
		for (auto itr = vec_seenInvBlockIDs.begin(); itr != end; ++itr)
		{
			SetActive(vec_invBlocks, *itr, true);
		}
	}

	{
		auto end = vec_hitPlayerBlockIDs.end();
		for (auto itr = vec_hitPlayerBlockIDs.begin(); itr != end; ++itr)
		{
			SetActive(vec_invBlocks, *itr, false);
		}
	}
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

void ButiEngine::InvisibleBlockManagerComponent::SetActive(std::vector<std::shared_ptr<GameObject>> invBlocks, int id, bool flag)
{
	auto end = invBlocks.end();
	for (auto itr = invBlocks.begin(); itr != end; ++itr)
	{
		auto inv = (*itr)->GetGameComponent<InvisibleBlockComponent>();
		if (inv->GetID() == id)
		{
			inv->SetActive(flag);
		}
	}
}
