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

void ButiEngine::InvisibleBlockManagerComponent::Check()
{
	auto end = vec_vec_invBlocks.end();

	auto camera = GetCamera("playerCamera");

	auto player = GetManager().lock()->GetGameObject("Player");

	auto anim = player.lock()->GetGameComponent<CubeTransformAnimation>();
	auto currenCameraTransform = camera.lock()->shp_transform;
	if (anim)
	{
		auto target = anim->GetTargetTransform();
		camera.lock()->shp_transform = target;
	}

	std::vector<bool> vec_seens ;
	vec_seens.resize(vec_vec_invBlocks.size());

	auto endItr = vec_invBlocks.end();
	InvisibleBlockComponent::SetCameraInv(camera.lock()->shp_transform->ToMatrix().GetInverse());
	std::sort(vec_invBlocks.begin(), endItr, [](const std::shared_ptr<InvisibleBlockComponent> pmX, const std::shared_ptr<InvisibleBlockComponent> pmY) {

		return pmX->GetCameraLocalPos().z < pmX->GetCameraLocalPos().z;
	});


	for (auto itr = vec_invBlocks.begin(); itr != endItr;itr++) {
		if (vec_seens[(*itr)->GetID()]) {
			continue;
		}
		vec_seens[(*itr)->GetID()] = (*itr)->IsContaineVisibility();

	}

	auto seensEnd = vec_seens.size();
	
	for ( int i = 0;i<seensEnd ; i++) {

		auto blockItrEnd = vec_vec_invBlocks[i].end();
		if (vec_seens[i]) {
			for (auto blockItr = vec_vec_invBlocks[i].begin(); blockItr != blockItrEnd; blockItr++) {

				(*blockItr)->SetActive(true);
			}
		}
		else {
			for (auto blockItr = vec_vec_invBlocks[i].begin(); blockItr != blockItrEnd; blockItr++) {

				(*blockItr)->SetActive(false);
			}

		}
	}
	camera.lock()->shp_transform = currenCameraTransform;
}

void ButiEngine::InvisibleBlockManagerComponent::OnShowUI()
{
}

void ButiEngine::InvisibleBlockManagerComponent::RegistBlocks()
{
	GameObjectTag tag = gameObject.lock()->GetApplication().lock()->GetGameObjectTagManager()->GetObjectTag("InvisibleBlock");
	auto invBlocks = GetManager().lock()->GetGameObjects(tag);
	vec_invBlocks.reserve( invBlocks.size());
	for (auto itr = invBlocks.begin(); itr != invBlocks.end();itr++) {
		vec_invBlocks.push_back((*itr)->GetGameComponent<InvisibleBlockComponent>());
	}

	vec_vec_invBlocks.resize(32);
	auto endItr = vec_invBlocks.end();
	for (auto itr = vec_invBlocks.begin(); itr != endItr; itr++) {
		auto component = (*itr);
		if (component) {
			vec_vec_invBlocks.at(component->GetID()).push_back(component);
		}
	}
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
