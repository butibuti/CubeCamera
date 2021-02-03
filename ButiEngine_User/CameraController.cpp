#include "stdafx_u.h"
#include "CameraController.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"

void ButiEngine::CameraController::OnUpdate()
{
    auto selfRotate = gameObject.lock()->transform->GetLocalRotation().GetEulerOneValue_local().ToDegrees();
    selfRotate.y = 0;
    gameObject.lock()->transform->SetLocalRotation((selfRotate));
}

void ButiEngine::CameraController::OnSet()
{
}

void ButiEngine::CameraController::Start()
{
    shp_cameraAxis = gameObject.lock()->GetGameObjectManager().lock()->AddObjectFromCereal("cameraAxis").lock();
    gameObject.lock()->transform->SetBaseTransform(shp_cameraAxis->transform, true);
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::CameraController::Clone()
{
    auto output = ObjectFactory::Create<CameraController>();;

    output->pase = pase;
    return output;

}

void ButiEngine::CameraController::OnShowUI()
{
}

void ButiEngine::CameraController::ZoomInOut()
{
    auto t = gameObject.lock()->transform;

    auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
    if (!anim)
    {
        anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
        anim->SetTargetTransform(t->Clone());
        anim->GetTargetTransform()->SetWorldPosition(t->GetWorldPosition() - t->GetFront() * 2.5f);
        anim->SetSpeed(1.0f / 50.0f);
        //anim->SetReverse(true);
        anim->SetEaseType(Easing::EasingType::EaseOutBack);
    }
}

void ButiEngine::CameraController::ZoomIn()
{
    auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
    if (!anim && gameObject.lock()->transform->GetLocalPosition().z < -10) {
        anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
        anim->SetTargetTransform(gameObject.lock()->transform->Clone());
        anim->GetTargetTransform()->SetWorldPosition(gameObject.lock()->transform->GetWorldPosition() + gameObject.lock()->transform->GetFront() * 5);
        anim->SetSpeed(1.0f / 39.0f);
        anim->SetEaseType(Easing::EasingType::EaseOutBack);
    }
}

void ButiEngine::CameraController::ZoomOut()
{
    auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
    if (!anim && gameObject.lock()->transform->GetLocalPosition().z > -30) {
        anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
        anim->SetTargetTransform(gameObject.lock()->transform->Clone());
        anim->GetTargetTransform()->SetWorldPosition(gameObject.lock()->transform->GetWorldPosition() - gameObject.lock()->transform->GetFront() * 30);
        anim->SetSpeed(1.0f / 20.0f);
        anim->SetEaseType(Easing::EasingType::EaseInExpo);
    }
}
