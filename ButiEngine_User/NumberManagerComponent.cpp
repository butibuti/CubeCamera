#include "stdafx_u.h"
#include "NumberManagerComponent.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent.h"

void ButiEngine::NumberManagerComponent::OnUpdate()
{
}

void ButiEngine::NumberManagerComponent::OnSet()
{
}

void ButiEngine::NumberManagerComponent::Start()
{
	number1 = GetManager().lock()->AddObjectFromCereal("Number1", ObjectFactory::Create<Transform>(Vector3(0, 0, 9), Vector3::Zero, Vector3(500, 500, 1)));
	number10 = GetManager().lock()->AddObjectFromCereal("Number10", ObjectFactory::Create<Transform>(Vector3(-150, 0, 10), Vector3::Zero, Vector3(500, 500, 1)));
	SetNumber(0);
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::NumberManagerComponent::Clone()
{
	return ObjectFactory::Create<NumberManagerComponent>();
}

void ButiEngine::NumberManagerComponent::OnShowUI()
{
}

void ButiEngine::NumberManagerComponent::SetNumber(int arg_number)
{
	number = arg_number + 1;

	int one = number % 10;
	int ten = number / 10;

	auto meshDraw1 = number1.lock()->GetGameComponent<MeshDrawComponent>();
	auto meshDraw10 = number10.lock()->GetGameComponent<MeshDrawComponent>();

	if (number < 10)
	{
		number1.lock()->transform->SetWorldPosition(Vector3(0, 0, 9));
		number10.lock()->GetGameComponent<MeshDrawComponent>()->UnRegist();
	}
	else
	{
		number1.lock()->transform->SetWorldPosition(Vector3(150, 0, 9));
		number10.lock()->GetGameComponent<MeshDrawComponent>()->Regist();
		std::string name10 = "number_" + std::to_string(ten);
		meshDraw10->SetMaterialTag(gameObject.lock()->GetResourceContainer()->GetMaterialTag(name10));
		meshDraw10->ReRegist();
	}

	std::string name1 = "number_" + std::to_string(one);
	meshDraw1->SetMaterialTag(gameObject.lock()->GetResourceContainer()->GetMaterialTag(name1));
	meshDraw1->ReRegist();
}
