#include "stdafx_u.h"
#include "InvisibleBlockComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"
#include"PlayerCameraComponent.h"
#include"PlayerBehavior.h"
#include"MapComponent.h"
#include"GameSettings.h"

void ButiEngine::InvisibleBlockComponent::OnUpdate()
{
	auto camera = GetCamera("playerCamera");

	auto player = GetManager().lock()->GetGameObject("Player");
	if (player.lock() && player.lock()->GetBehavior<PlayerBehavior>()->IsRollFinish())
	{
		seen = false;
		hitPlayer = false;
		auto anim = player.lock()->GetGameComponent<CubeTransformAnimation>();
		auto currenCameraTransform = camera.lock()->shp_transform;
		if (anim)
		{
			auto target = anim->GetTargetTransform();
			camera.lock()->shp_transform = target;
		}
		int i = camera.lock()->IsContaineVisibility(shp_AABB);
		if (i == 0)
		{
			seen = true; 
		}
		camera.lock()->shp_transform = currenCameraTransform;
		if (player.lock()->GetBehavior<PlayerBehavior>()->GetMapPos() == mapPos) 
		{ 
			hitPlayer = true; 
		}
	}
}

void ButiEngine::InvisibleBlockComponent::OnSet()
{
	gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->UnRegist();
}

void ButiEngine::InvisibleBlockComponent::Start()
{
	active = false;
	seen = false;
	shp_map = gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Map").lock()->GetGameComponent<MapComponent>();
	shp_AABB = ObjectFactory::Create<Collision::CollisionPrimitive_Box_AABB>(Vector3(1, 1, 1), gameObject.lock()->transform);
	shp_AABB->Update();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::InvisibleBlockComponent::Clone()
{
	return ObjectFactory::Create<InvisibleBlockComponent>();
}

void ButiEngine::InvisibleBlockComponent::OnShowUI()
{
}

void ButiEngine::InvisibleBlockComponent::SetActive(bool active)
{
	if (this->active == active) 
	{
		return; 
	}

	if (!this->active)
	{
		gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->Regist();
		shp_map->ChangeBlock(mapPos, GameSettings::block);
	}
	else
	{
		gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->UnRegist();
		shp_map->ChangeBlock(mapPos, GameSettings::invisibleBlock + id);
	}
	this->active = active;
}
