#include "stdafx_u.h"
#include "BackGround.h"
#include"Header/GameObjects/DefaultGameComponent/MeshDrawComponent_Static.h"

void ButiEngine::BackGround::OnUpdate()
{
    auto endItr = vec_blockData.end();
    int i = 0;
    for (auto itr = vec_blockData.begin(); itr != endItr; itr++,i++) {
        itr->time += pase * itr->direction;
        itr->moveTime += itr->movePase*itr->moveDir;

        if (itr->time > 1.0f) {
            itr->time = 1.0f;
            itr->direction = -1;
        }
        else if (itr->time < 0.0f) {
            itr->time = 0.0f;
            itr->direction = 1;
        }
        if (itr->moveTime > 1.0f) {
            itr->moveTime = 1.0f;
            itr->moveDir = -1;
        }
        else if (itr->moveTime < 0.0f) {
            itr->moveTime = 0.0f;
            itr->moveDir = 1;
        }

        vec_shp_lightBuffer[i]->Get().lightDir = startColor * itr->time + endColor * (1-itr->time);
        vec_shp_transform[i]->SetWorldPosition(itr->initPos + Vector3::YAxis * (Easing::EaseInOut( itr->moveTime )- 0.5)*itr->moveMax);
        vec_shp_transform[i]->RollLocalRotationY_Degrees(itr->movePase*100);
    }
}

void ButiEngine::BackGround::OnSet()
{
}

void ButiEngine::BackGround::Start()
{
    auto floatBlockTag = gameObject.lock()->GetApplication().lock()->GetGameObjectTagManager()->GetObjectTag("FloatBlock");
    auto floatBlocks = GetManager().lock()->GetGameObjects(floatBlockTag);

    auto endItr = floatBlocks.end();

    for (auto itr = floatBlocks.begin(); itr != endItr; itr++) {
        vec_shp_transform.push_back((*itr)->transform);
        vec_shp_lightBuffer.push_back((*itr)->GetGameComponent<MeshDrawComponent_Static>()->GetCBuffer<LightVariable>("LightBuffer"));

        Vector3 pos = (*itr)->transform->GetWorldPosition();
        float current = (sin(MathHelper::Dot(Vector2(pos.x, pos.z), Vector2(1.9898 + pos.y, 8.233))) * 437.645);
        current -= (int)current;

        FloatBlockData data;
        data.time = current;
        data.initPos = pos;
        data.moveTime = (sin(MathHelper::Dot(Vector2(pos.x, pos.z), Vector2(3.1 + pos.y, 1.234))) * 851.645);
        data.moveTime -= (int)data.moveTime;
        data.direction = ButiRandom::GetRandom(0, 1, 1);
        data.movePase= ButiRandom::GetRandom(1.0f, 5.0f, 5)*0.001f;
        data.moveMax = ButiRandom::GetRandom(1.0f,2.0f,10)*0.2;
        data.moveDir = ButiRandom::GetRandom(0, 1,1);

        if (data.moveDir == 0) {
            data.moveDir = -1;
        }
        if (data.direction == 0) {
            data.direction = -1;
        }



        vec_blockData.push_back(data);

    }

}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::BackGround::Clone()
{
    return ObjectFactory::Create<BackGround>();
}

void ButiEngine::BackGround::OnShowUI()
{
    GUI::BulletText("StartColor");

    GUI::DragFloat4("##startcolor", startColor, 0.01f, 0, 1);
    GUI::BulletText("EndColor");

    GUI::DragFloat4("##Endcolor", endColor, 0.01f, 0, 1);
    GUI::BulletText("Pase");

    GUI::DragFloat("##pase", pase, 0.01f, 0, 1);
}
