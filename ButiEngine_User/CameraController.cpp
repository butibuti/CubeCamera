#include "stdafx_u.h"
#include "CameraController.h"
#include"Header/GameObjects/DefaultGameComponent/TransformAnimation.h"

void ButiEngine::CameraController::OnUpdate()
{
    auto selfRotate = gameObject.lock()->transform->GetLocalRotation().GetEulerOneValue_local().ToDegrees();
    selfRotate.y = 0;
    gameObject.lock()->transform->SetLocalRotation((selfRotate));
    if (GameDevice::GetInput()->TriggerKey(Keys::Z)) {
        auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
        if (!anim &&gameObject.lock()->transform->GetLocalPosition().z>-30) {
            anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
            anim->SetTargetTransform(gameObject.lock()->transform->Clone());
            anim->GetTargetTransform()->SetWorldPosition(gameObject.lock()->transform->GetWorldPosition()- gameObject.lock()->transform->GetFront()*5);
            anim->SetSpeed(1.0f / 10.0f);
        }
    }
    if (GameDevice::GetInput()->TriggerKey(Keys::X)) {
        auto anim = gameObject.lock()->GetGameComponent<TransformAnimation>();
        if (!anim&& gameObject.lock()->transform->GetLocalPosition().z < -10) {
            anim = gameObject.lock()->AddGameComponent<TransformAnimation>();
            anim->SetTargetTransform(gameObject.lock()->transform->Clone());
            anim->GetTargetTransform()->SetWorldPosition(gameObject.lock()->transform->GetWorldPosition() + gameObject.lock()->transform->GetFront() * 5);
            anim->SetSpeed(1.0f / 10.0f);
        }
    }
    if (GameDevice::GetInput()->TriggerKey(Keys::E)) {
        auto anim = shp_cameraAxis->GetGameComponent<TransformAnimation>();
        if (!anim) {
            anim= shp_cameraAxis->AddGameComponent<TransformAnimation>();
            anim->SetTargetTransform(shp_cameraAxis->transform->Clone());
            //anim->GetTargetTransform()->TranslateX(-1.0);
            anim->GetTargetTransform()->RollLocalRotationY_Degrees(90);
            anim->SetSpeed(1.0f / 10.0f);
        }
    }
    if (GameDevice::GetInput()->TriggerKey(Keys::Q)) {
        auto anim = shp_cameraAxis->GetGameComponent<TransformAnimation>();
        if (!anim) {
            anim = shp_cameraAxis->AddGameComponent<TransformAnimation>();
            anim->SetTargetTransform(shp_cameraAxis->transform->Clone());
            anim->GetTargetTransform()->RollLocalRotationY_Degrees(-90);
            anim->SetSpeed(1.0f / 10.0f);
        }
    }
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
