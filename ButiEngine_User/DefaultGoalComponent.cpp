#include "stdafx_u.h"
#include "DefaultGoalComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"
#include"PlayerBehavior.h"

void ButiEngine::DefaultGoalComponent::OnUpdate()
{
	//カメラを検索、保持
//std::weak_ptr<ICamera> GetCamera(std::string arg_cameraName)
//第一引数: 検索するカメラの名前
	auto camera = GetCamera("playerCamera");

	//カメラにAABBを渡して判定
	//bool ICamera::IsContaineVisibility(std::shared_ptr<Geometry::Box_AABB> arg_checkPrimitive)
	//第一引数: 判定に使うAABB
	if (gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Player").lock()->GetBehavior<PlayerBehavior>()->IsRollFinish())
	{
		if (!active && camera.lock()->IsContaineVisibility(shp_AABB) == 0)
		{
			gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->Regist();
			active = true;
		}
	}
	//マテリアル変更
	//auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	//meshDraw->SetMaterialTag(gameObject.lock()->GetResourceContainer()->GetMaterialTag("検索する名前"));
	//meshDraw->ReRegist();
}

void ButiEngine::DefaultGoalComponent::OnSet()
{
	gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->UnRegist();
}

void ButiEngine::DefaultGoalComponent::Start()
{
	active = false;

	//当たり判定用AABBを作る
	//Collision::CollisionPrimitive_Box_AABB(const Vector3& size,std::shared_ptr<Transform> arg_transform)
	//第一引数: 各軸の辺の長さ
	//第二引数: 計算する姿勢
	shp_AABB = ObjectFactory::Create<Collision::CollisionPrimitive_Box_AABB>(Vector3(1, 1, 1), gameObject.lock()->transform);
	shp_AABB->Update();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::DefaultGoalComponent::Clone()
{
	return ObjectFactory::Create<DefaultGoalComponent>();
}

void ButiEngine::DefaultGoalComponent::OnShowUI()
{
}
