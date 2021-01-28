#include "stdafx_u.h"
#include "DefaultGoalComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"
#include"PlayerBehavior.h"

void ButiEngine::DefaultGoalComponent::OnUpdate()
{
	//�J�����������A�ێ�
//std::weak_ptr<ICamera> GetCamera(std::string arg_cameraName)
//������: ��������J�����̖��O
	auto camera = GetCamera("playerCamera");

	//�J������AABB��n���Ĕ���
	//bool ICamera::IsContaineVisibility(std::shared_ptr<Geometry::Box_AABB> arg_checkPrimitive)
	//������: ����Ɏg��AABB
	auto player = gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Player").lock();
	if (player && player->GetBehavior<PlayerBehavior>()->IsRollFinish())
	{
		if (!active && camera.lock()->IsContaineVisibility(shp_AABB) == 1)
		{
			gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->Regist();
			active = true;
			auto t = gameObject.lock()->transform;
			auto pos = t->GetWorldPosition();
			auto rot = t->GetWorldRotation();
			auto scale = t->GetLocalScale();

			GetManager().lock()->AddObjectFromCereal("GoalAura", ObjectFactory::Create<Transform>(pos, rot, scale));
		}
	}
	//�}�e���A���ύX
	//auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
	//meshDraw->SetMaterialTag(gameObject.lock()->GetResourceContainer()->GetMaterialTag("�������閼�O"));
	//meshDraw->ReRegist();
}

void ButiEngine::DefaultGoalComponent::OnSet()
{
}

void ButiEngine::DefaultGoalComponent::Start()
{
	active = false;

	gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>()->UnRegist();
	//�����蔻��pAABB�����
	//Collision::CollisionPrimitive_Box_AABB(const Vector3& size,std::shared_ptr<Transform> arg_transform)
	//������: �e���̕ӂ̒���
	//������: �v�Z����p��
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
