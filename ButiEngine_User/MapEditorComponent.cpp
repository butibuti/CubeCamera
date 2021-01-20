#include "stdafx_u.h"
#include "MapEditorComponent.h"
#include "MapComponent.h"

void ButiEngine::MapEditorComponent::OnUpdate()
{
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
