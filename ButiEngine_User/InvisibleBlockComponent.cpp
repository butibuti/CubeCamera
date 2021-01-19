#include "stdafx_u.h"
#include "InvisibleBlockComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"PlayerCameraComponent.h"
#include"PlayerBehavior.h"
#include"MapComponent.h"
#include"GameSettings.h"

ButiEngine::Matrix4x4 ButiEngine::InvisibleBlockComponent::cameraInv;

void ButiEngine::InvisibleBlockComponent::OnUpdate()
{
	
}

void ButiEngine::InvisibleBlockComponent::OnSet()
{
	gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->UnRegist();
	shp_AABB = ObjectFactory::Create<Collision::CollisionPrimitive_Box_AABB>(Vector3(1, 1, 1), gameObject.lock()->transform);
	shp_map = gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Map").lock()->GetGameComponent<MapComponent>();
	active = false;
	seen = false;
}

void ButiEngine::InvisibleBlockComponent::Start()
{
	shp_AABB->Update();
}

bool ButiEngine::InvisibleBlockComponent::IsContaineVisibility()
{
	auto camera = GetCamera("playerCamera");

	auto player = GetManager().lock()->GetGameObject("Player");
	if (player.lock() )
	{
		shp_AABB->Update();
		seen = false;
		hitPlayer = false;
		auto playerMapPos = player.lock()->GetBehavior<PlayerBehavior>()->GetNextMapPos();
		int i = camera.lock()->IsContaineVisibility(shp_AABB);

		if ((playerMapPos - mapPos).GetLength()<0.01)
		{
			hitPlayer = true;
		}
		if (((!active &&i == 0)||(active&&i==1))&&!hitPlayer)
		{
			seen = true;
		}
	}
	return seen;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::InvisibleBlockComponent::Clone()
{
	return ObjectFactory::Create<InvisibleBlockComponent>();
}

void ButiEngine::InvisibleBlockComponent::OnShowUI()
{
}

void ButiEngine::InvisibleBlockComponent::SetActive(bool arg_active)
{
	if (this->active == arg_active)
	{
		return; 
	}

	auto player = GetManager().lock()->GetGameObject("Player");
	hitPlayer = false;
	auto playerMapPos = player.lock()->GetBehavior<PlayerBehavior>()->GetNextMapPos();

	if ((playerMapPos - mapPos).GetLength() < 0.01)
	{
		hitPlayer = true;
	}

	if (!this->active)
	{
		if (!hitPlayer) {

			gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->Regist();
			shp_map->ChangeBlock(mapPos, GameSettings::block);
			this->active = arg_active;
		}
	}
	else
	{
		gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->UnRegist();
		shp_map->ChangeBlock(mapPos, GameSettings::invisibleBlock + id);
		this->active = arg_active;
	}
}

ButiEngine::Vector3 ButiEngine::InvisibleBlockComponent::GetCameraLocalPos() const
{
	return mapPos* InvisibleBlockComponent::cameraInv;
}
