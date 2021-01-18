#include "stdafx_u.h"
#include "EasyGoalComponent.h"
#include"Header/Common/CollisionPrimitive.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"
#include"Header/GameObjects/DefaultGameComponent/CubeTransformAnimation.h"

void ButiEngine::EasyGoalComponent::OnUpdate()
{
	//�J�����������A�ێ�
//std::weak_ptr<ICamera> GetCamera(std::string arg_cameraName)
//������: ��������J�����̖��O
	auto camera = GetCamera("playerCamera");

	//�J������AABB��n���Ĕ���
	//bool ICamera::IsContaineVisibility(std::shared_ptr<Geometry::Box_AABB> arg_checkPrimitive)
	//������: ����Ɏg��AABB
	if (!gameObject.lock()->GetGameObjectManager().lock()->GetGameObject("Player").lock()->GetGameComponent<CubeTransformAnimation>())
	{
		if (!active && camera.lock()->IsContaineVisibility(shp_AABB) == 1)
		{
			//�}�e���A���ύX
			auto meshDraw = gameObject.lock()->GetGameComponent<MeshDrawComponent_Static>();
			meshDraw->SetMaterialTag(gameObject.lock()->GetResourceContainer()->GetMaterialTag("goalMaterial"));
			meshDraw->ReRegist();
			active = true;
		}
	}
}

void ButiEngine::EasyGoalComponent::OnSet()
{
}

void ButiEngine::EasyGoalComponent::Start()
{
	active = false;

	//�����蔻��pAABB�����
	//Collision::CollisionPrimitive_Box_AABB(const Vector3& size,std::shared_ptr<Transform> arg_transform)
	//������: �e���̕ӂ̒���
	//������: �v�Z����p��
	shp_AABB = ObjectFactory::Create<Collision::CollisionPrimitive_Box_AABB>(Vector3(1, 1, 1), gameObject.lock()->transform);
	shp_AABB->Update();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::EasyGoalComponent::Clone()
{
	return ObjectFactory::Create<EasyGoalComponent>();
}

void ButiEngine::EasyGoalComponent::OnShowUI()
{
}
