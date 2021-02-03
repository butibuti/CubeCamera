#include "stdafx_u.h"
#include "InvisibleBlockComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"PlayerCameraComponent.h"
#include"PlayerBehavior.h"
#include"MapComponent.h"
#include"GameSettings.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"


void ButiEngine::InvisibleBlockComponent::OnUpdate()
{
}

void ButiEngine::InvisibleBlockComponent::OnSet()
{
}

void ButiEngine::InvisibleBlockComponent::Start()
{
	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	meshDraw->UnRegist();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::InvisibleBlockComponent::Clone()
{
	return ObjectFactory::Create<InvisibleBlockComponent>();
}

void ButiEngine::InvisibleBlockComponent::OnShowUI()
{
}

void ButiEngine::InvisibleBlockComponent::Active()
{
	if (active)
	{
		return;
	}

	auto t = gameObject.lock()->transform;


	auto anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
	anim->SetSpeed(1.0f / 10);
	anim->SetTargetTransform(t->Clone());
	anim->GetTargetTransform()->SetLocalScale(1.1f);
	anim->GetTargetTransform()->RollLocalRotationX_Degrees(0.1f);

	anim->SetEaseType(Easing::EasingType::Parabola);

	auto mapComp = GetManager().lock()->GetGameObject("Map").lock()->GetGameComponent<MapComponent>();
	mapComp->ChangeBlock(mapPos, GameSettings::block);
	active = true;
	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	meshDraw->Regist();

	auto seTag = gameObject.lock()->GetResourceContainer()->GetSoundTag("Sound/inv_Discover.wav");

	gameObject.lock()->GetGameObjectManager().lock()->GetScene().lock()->GetSoundManager()->Play(seTag, 0.003f);
}

void ButiEngine::InvisibleBlockComponent::UnActive()
{
	if (!active)
	{
		return;
	}

	auto mapComp = GetManager().lock()->GetGameObject("Map").lock()->GetGameComponent<MapComponent>();
	mapComp->ChangeBlock(mapPos, GameSettings::invisibleBlock + id);
	active = false;
	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	meshDraw->UnRegist();
	auto seTag = gameObject.lock()->GetResourceContainer()->GetSoundTag("Sound/inv_Cover.wav");

	gameObject.lock()->GetGameObjectManager().lock()->GetScene().lock()->GetSoundManager()->Play(seTag, 0.003f);
}

void ButiEngine::InvisibleBlockComponent::Seen()
{
	seen = true;
}
