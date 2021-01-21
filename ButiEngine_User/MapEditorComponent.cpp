#include "stdafx_u.h"
#include "MapEditorComponent.h"
#include "MapComponent.h"
#include"GameSettings.h"

void ButiEngine::MapEditorComponent::OnUpdate()
{
    static int blockPos[3];
    static int invisibleID;

    GUI::Begin("Editor");

    GUI::BulletText("New Block Position");
    GUI::DragInt3("##position", blockPos, 1.0, 0, 300);

    if (GUI::Button("Add Block")) {
        shp_currentMapData->mapData[blockPos[0]][blockPos[1]][blockPos[2]] = GameSettings::block;
    }
    if (GUI::Button("Add Goal")) {
        shp_currentMapData->mapData[blockPos[0]][blockPos[1]][blockPos[2]] = GameSettings::defaultGoal;
    }
    if (GUI::Button("Add InvisibleBlock")) {
        shp_currentMapData->mapData[blockPos[0]][blockPos[1]][blockPos[2]] = GameSettings::block;
    }

    GUI::End();
}

void ButiEngine::MapEditorComponent::OnSet()
{
}

void ButiEngine::MapEditorComponent::Start()
{
    auto map = GetManager().lock()->GetGameObject("Map");
    shp_mapComponent = map.lock()->GetGameComponent< MapComponent>();
    shp_currentMapData = shp_mapComponent->GetCurrentMapData();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::MapEditorComponent::Clone()
{
    return ObjectFactory::Create<MapEditorComponent>();
}

void ButiEngine::MapEditorComponent::OnShowUI()
{
}
