#include "stdafx_u.h"
#include "PlayerCameraComponent.h"
#include"CameraMeshComponent.h"

void ButiEngine::PlayerCameraComponent::OnUpdate()
{
	auto cameraMesh = GetManager().lock()->GetGameObject("CameraMesh").lock()->GetGameComponent<CameraMeshComponent>();
	if (isShutter)
	{
		isShutter = false;
		auto camera = GetCamera("playerCamera");
		TextureTag tag = gameObject.lock()->GetResourceContainer()->GetTextureTag(":/movie/162/114");
		camera.lock()->SetProjectionTexture(tag);
		cameraMesh->Shutter();
	}
	cameraMesh->Shrink();
	if (shp_timer && shp_timer->Update())
	{
		shp_timer->Stop();
	}
	else if(shp_timer && !shp_timer->IsOn())
	{
		isShutter = true;
		shp_timer = nullptr;
		auto camera = GetCamera("playerCamera");
		TextureTag tag = gameObject.lock()->GetResourceContainer()->GetTextureTag(":/playerCamera/1280/360");
		camera.lock()->SetProjectionTexture(tag);
	}
}

void ButiEngine::PlayerCameraComponent::OnSet()
{
}

void ButiEngine::PlayerCameraComponent::Start()
{
	isShutter = false;
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::PlayerCameraComponent::Clone()
{
	return ObjectFactory::Create<PlayerCameraComponent>();
}

void ButiEngine::PlayerCameraComponent::OnShowUI()
{
}

void ButiEngine::PlayerCameraComponent::SetTimer(const unsigned int frame)
{
	shp_timer = ObjectFactory::Create<RelativeTimer>(frame);
	shp_timer->Start();
}
