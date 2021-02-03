#include "stdafx_u.h"
#include "EasyGoalComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"PlayerBehavior.h"
#include"MapComponent.h"
#include"CameraController.h"
#include"BackGround.h"

void ButiEngine::EasyGoalComponent::OnUpdate()
{
	shp_AABB->Update();
}

void ButiEngine::EasyGoalComponent::OnSet()
{
}

void ButiEngine::EasyGoalComponent::Start()
{
	active = false;

	//当たり判定用AABBを作る
	//Collision::CollisionPrimitive_Box_AABB(const Vector3& size,std::shared_ptr<Transform> arg_transform)
	//第一引数: 各軸の辺の長さ
	//第二引数: 計算する姿勢
	shp_AABB = ObjectFactory::Create<Collision::CollisionPrimitive_Box_AABB>(Vector3(1, 1, 1), gameObject.lock()->transform);
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::EasyGoalComponent::Clone()
{
	return ObjectFactory::Create<EasyGoalComponent>();
}

void ButiEngine::EasyGoalComponent::OnShowUI()
{
}

void ButiEngine::EasyGoalComponent::Seen()
{
	if (active)
	{
		return;
	}

	//マテリアル変更
	auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	meshDraw->SetMaterialTag(gameObject.lock()->GetResourceContainer()->GetMaterialTag("goalMaterial"));
	meshDraw->ReRegist();
	active = true;

	auto t = gameObject.lock()->transform;
	auto pos = t->GetWorldPosition();
	auto rot = t->GetWorldRotation();
	auto scale = t->GetLocalScale();

	GetManager().lock()->AddObjectFromCereal("GoalAura", ObjectFactory::Create<Transform>(pos, rot, scale));
	auto map = GetManager().lock()->GetGameObject("Map");
	auto mapComponent = map.lock()->GetGameComponent< MapComponent>(); 
	mapComponent->SetMapEndColor(Vector4(1.0f, 1.0f, 0.5f, 1.0f));
	mapComponent->SetMapStartColor(Vector4(0.7f, 0.5f, 0.0f, 1.0f));
	mapComponent->ShakeStart(0.01f);



	auto seTag = gameObject.lock()->GetResourceContainer()->GetSoundTag("Sound/potion.wav");

	gameObject.lock()->GetGameObjectManager().lock()->GetScene().lock()->GetSoundManager()->Play(seTag, 0.1f);

	GetManager().lock()->GetGameObject("MainCamera").lock()->GetGameComponent<CameraController>()->ZoomInOut();
	auto backGround = GetManager().lock()->GetGameObject("BackGroundController").lock()->GetGameComponent<BackGround>();
	backGround->SetEndColor(Vector4(1.0f, 1.0f, 0.5f, 1.0f));
	backGround->SetStartColor(Vector4(0.7f, 0.5f, 0.0f, 1.0f));
	backGround->SetIsClear(true);
}
