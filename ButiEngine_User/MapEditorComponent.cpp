#include "stdafx_u.h"
#include "MapEditorComponent.h"
#include "MapComponent.h"
#include"GameSettings.h"
#include"InvisibleBlockComponent.h"
#include"InvisibleBlockManagerComponent.h"

void ButiEngine::MapEditorComponent::OnUpdate()
{
#ifdef DEBUG


    static int blockPos[3];
    static int blockPos_edgeOne[3];
    static int blockPos_edgeTwo[3];
    static int invisibleID;
    gameObject.lock()->transform->SetLocalPosition(Vector3(blockPos[0], blockPos[1], blockPos[2])-offset);

    GUI::Begin("Editor");

    GUI::BulletText("New Block Position");
    auto size = p_mapdata->GetSize();
    if (GUI::DragInt3("##position", blockPos, 1.0, 0, 300)) {

        blockPos[0] = min(blockPos[0], size.x - 1);
        blockPos[1] = min(blockPos[1], size.y - 1);
        blockPos[2] = min(blockPos[2], size.z - 1);
    }
    GUI::BulletText("InvisibleBlock's ID");
    GUI::DragInt("##invisibleID", invisibleID, 1.0, 0, 300);
    invisibleID = min(invisibleID, 31);

    if (GUI::Button("Replace Block")) {
        Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), "Block", GameSettings::block);
    }
    if (GUI::Button("Replace Goal")) {
        Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), "DefaultGoal", GameSettings::defaultGoal);
    }
    if (GUI::Button("Replace InvisibleBlock")) {
        
        auto gameObject= Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), "InvisibleBlock", GameSettings::invisibleBlock+invisibleID);


        gameObject->GetGameComponent<InvisibleBlockComponent>()->SetID(invisibleID);
        gameObject->GetGameComponent<InvisibleBlockComponent>()->SetMapPos(Vector3(blockPos[0], blockPos[1], blockPos[2]));


        auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
        invisibleBlockManager->ClearBlocks();

        invisibleBlockManager->RegistBlocks();
        invisibleBlockManager->Check();
    }

    if (GUI::Button("Change PlayerInitPosition")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {
            for (int j = 0; j < p_mapdata->mapData[0].size(); j++) {
                for (int k = 0; k < p_mapdata->mapData[0][0].size(); k++) {

                    if (p_mapdata->mapData[i][j][k]== GameSettings::player) {
                        p_mapdata->mapData[i][j][k] = 0;
                        shp_currentMapData->mapData[i][j][k] = 0;
                    }
                }
            }
        }

        p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = GameSettings::player;
        shp_currentMapData->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = GameSettings::player;
    }

    if (GUI::Button("Remove")) {
        if ((*p_mapObjectData)[blockPos[1]][blockPos[2]][blockPos[0]]) {


            p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = 0;
            shp_currentMapData->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = 0;

            (*p_mapObjectData)[blockPos[1]][blockPos[2]][blockPos[0]]->SetIsRemove(true);
            (*p_mapObjectData)[blockPos[1]][blockPos[2]][blockPos[0]] = nullptr;

            auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
            invisibleBlockManager->ClearBlocks();

            invisibleBlockManager->RegistBlocks();
            invisibleBlockManager->Check();
        }

    }


    GUI::BulletText("New BlockRange");
    if (GUI::DragInt3("##position_edgeOne", blockPos_edgeOne, 1.0, 0, 300)) {

        blockPos_edgeOne[0] = min(blockPos_edgeOne[0], size.x - 1);
        blockPos_edgeOne[1] = min(blockPos_edgeOne[1], size.y - 1);
        blockPos_edgeOne[2] = min(blockPos_edgeOne[2], size.z - 1);
    }
    if(GUI::DragInt3("##position_edgeTwo", blockPos_edgeTwo, 1.0, 0, 300) ){

        blockPos_edgeTwo[0] = min(blockPos_edgeTwo[0], size.x - 1);
        blockPos_edgeTwo[1] = min(blockPos_edgeTwo[1], size.y - 1);
        blockPos_edgeTwo[2] = min(blockPos_edgeTwo[2], size.z - 1);
    }



    if (GUI::Button("Replace Block_range")) {

        Vector3 min = Vector3(blockPos_edgeOne[0], blockPos_edgeOne[1], blockPos_edgeOne[2]).Min(Vector3(blockPos_edgeTwo[0], blockPos_edgeTwo[1], blockPos_edgeTwo[2]));
        Vector3 max = Vector3(blockPos_edgeOne[0], blockPos_edgeOne[1], blockPos_edgeOne[2]).Max(Vector3(blockPos_edgeTwo[0], blockPos_edgeTwo[1], blockPos_edgeTwo[2]));

        for (int y = min.y; y <= max.y; y++) {
            for (int z = min.z; z <= max.z; z++) {

                for (int x = min.x; x <= max.x; x++) {
                    auto pos = Vector3(y, z, x);
                    Replace(pos, "Block", GameSettings::block);
                }
            }
        }

    }
    if (GUI::Button("Replace InvisibleBlock_range")) {

        Vector3 min = Vector3(blockPos_edgeOne[0], blockPos_edgeOne[1], blockPos_edgeOne[2]).Min(Vector3(blockPos_edgeTwo[0], blockPos_edgeTwo[1], blockPos_edgeTwo[2]));
        Vector3 max = Vector3(blockPos_edgeOne[0], blockPos_edgeOne[1], blockPos_edgeOne[2]).Max(Vector3(blockPos_edgeTwo[0], blockPos_edgeTwo[1], blockPos_edgeTwo[2]));

        for (int y = min.y; y <= max.y; y++) {
            for (int z = min.z; z <= max.z; z++) {

                for (int x = min.x; x <= max.x; x++) {
                    auto pos = Vector3(y, z, x);
                    auto gameObject = Replace(pos, "InvisibleBlock", GameSettings::invisibleBlock + invisibleID);

                    gameObject->GetGameComponent<InvisibleBlockComponent>()->SetID(invisibleID);
                    gameObject->GetGameComponent<InvisibleBlockComponent>()->SetMapPos(Vector3(x, y, z));

                }
            }
        }

        auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
        invisibleBlockManager->ClearBlocks();

        invisibleBlockManager->RegistBlocks();
        invisibleBlockManager->Check();
    }


    if (GUI::Button("Remove_range")) {

        Vector3 min = Vector3(blockPos_edgeOne[0], blockPos_edgeOne[1], blockPos_edgeOne[2]).Min(Vector3(blockPos_edgeTwo[0], blockPos_edgeTwo[1], blockPos_edgeTwo[2]));
        Vector3 max = Vector3(blockPos_edgeOne[0], blockPos_edgeOne[1], blockPos_edgeOne[2]).Max(Vector3(blockPos_edgeTwo[0], blockPos_edgeTwo[1], blockPos_edgeTwo[2]));

        for (int y = min.y; y <= max.y; y++) {
            for (int z = min.z; z <= max.z; z++) {

                for (int x = min.x; x <= max.x; x++) {

                    if (!(*p_mapObjectData)[y][z][x]) {
                        continue;
                    }

                    p_mapdata->mapData[y][z][x] = 0;
                    shp_currentMapData->mapData[y][z][x] = 0;

                    (*p_mapObjectData)[y][z][x]->SetIsRemove(true);
                    (*p_mapObjectData)[y][z][x] = nullptr;
                }
            }
        }

        auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
        invisibleBlockManager->ClearBlocks();

        invisibleBlockManager->RegistBlocks();
        invisibleBlockManager->Check();
    }


    GUI::BulletText("Stage Size");
    GUI::Text(size);

    if (GUI::Button("Add X")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {
            for (int j = 0; j < p_mapdata->mapData[0].size(); j++) {

                p_mapdata->mapData[i][j].push_back(0);
                shp_currentMapData->mapData[i][j].push_back(0);
                (*p_mapObjectData)[i][j].push_back(nullptr);
            }
        }
    }
    GUI::SameLine();
    if (GUI::Button("Add Y")) {

        auto zsize = p_mapdata->mapData[0].size();
        auto xsize = p_mapdata->mapData[0][0].size();
        p_mapdata->mapData.push_back(std::vector<std::vector<int>>());
        shp_currentMapData->mapData.push_back(std::vector<std::vector<int>>());
        (*p_mapObjectData).push_back(std::vector<std::vector<std::shared_ptr<GameObject>>>());

        (p_mapdata->mapData.end() - 1)->resize(zsize);
        (shp_currentMapData->mapData.end() - 1)->resize(zsize);
        ((*p_mapObjectData).end() - 1)->resize(zsize); 
        for (int i = 0; i < p_mapdata->mapData[0].size();i++) {

            (p_mapdata->mapData[p_mapdata->mapData.size() - 1][i]).resize(xsize);
            (shp_currentMapData->mapData[p_mapdata->mapData.size() - 1][i]).resize(xsize);
            ((*p_mapObjectData)[p_mapdata->mapData.size() - 1][i]).resize(xsize);
        }
       
    }
    GUI::SameLine();
    if (GUI::Button("Add Z")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {

            auto xsize = p_mapdata->mapData[0][0].size();
            p_mapdata->mapData[i].push_back(std::vector<int>());
            shp_currentMapData->mapData[i].push_back(std::vector<int>());
            (*p_mapObjectData)[i].push_back(std::vector<std::shared_ptr<GameObject>>());
            (p_mapdata->mapData[i].end() - 1)->resize(xsize);
            (shp_currentMapData->mapData[i].end() - 1)->resize(xsize);
            ((*p_mapObjectData)[i].end() - 1)->resize(xsize);
            
        }
    }

    if (GUI::Button("Remove X")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {
            for (int j = 0; j < p_mapdata->mapData[0].size(); j++) {

                p_mapdata->mapData[i][j].pop_back();
                shp_currentMapData->mapData[i][j].pop_back();
                if ((*((*p_mapObjectData)[i][j].end() - 1))) {
                    (*((*p_mapObjectData)[i][j].end() - 1))->SetIsRemove(true);
                }

                (*p_mapObjectData)[i][j].pop_back();
                
            }
        }

        auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
        invisibleBlockManager->ClearBlocks();

        invisibleBlockManager->RegistBlocks();
        invisibleBlockManager->Check();
    }
    GUI::SameLine();
    if (GUI::Button("Remove Y")) {
        p_mapdata->mapData.pop_back();
        shp_currentMapData->mapData.pop_back();

        for (int i = p_mapdata->mapData.size(); i < p_mapdata->mapData.size()+1; i++) {
            for (int j = 0; j < p_mapdata->mapData[0].size(); j++) {

                for (int k = 0; k < p_mapdata->mapData[0][0].size(); k++) {
                    if((*p_mapObjectData)[i][j][k])
                    (*p_mapObjectData)[i][j][k]->SetIsRemove(true);
                }
            }
        }
        (*p_mapObjectData).pop_back();

        auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
        invisibleBlockManager->ClearBlocks();

        invisibleBlockManager->RegistBlocks();
        invisibleBlockManager->Check();
    }
    GUI::SameLine();
    if (GUI::Button("Remove Z")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {

            p_mapdata->mapData[i].pop_back();
            shp_currentMapData->mapData[i].pop_back();
            for (int j = p_mapdata->mapData[i].size(); j < p_mapdata->mapData[i].size()+1; j++) {

                for (int k = 0; k < p_mapdata->mapData[i][0].size(); k++) {
                    if ((*p_mapObjectData)[i][j][k])
                    (*p_mapObjectData)[i][j][k]->SetIsRemove(true);
                }
            }
            (*p_mapObjectData)[i].pop_back();
        }

        auto invisibleBlockManager = GetManager().lock()->GetGameObject("InvisibleBlockManager").lock()->GetGameComponent<InvisibleBlockManagerComponent>();
        invisibleBlockManager->ClearBlocks();

        invisibleBlockManager->RegistBlocks();
        invisibleBlockManager->Check();
    }
    if (GUI::Button("MapReload")) {
        shp_mapComponent->PutBlock(0);
        offset = shp_currentMapData->GetSize() / 2;
        offset.Floor();
    }

    if (GUI::Button("Save")) {
        auto output = std::make_shared<MapData>();
        output->mapData = p_mapdata->mapData;
        std::string path = "Scene/" + GetManager().lock()->GetScene().lock()->GetSceneInformation()->GetSceneName() + "/mapInfo.map";
        OutputCereal(output,path);
    }

    GUI::End();

#endif // DEBUG
}

void ButiEngine::MapEditorComponent::OnSet()
{
}

void ButiEngine::MapEditorComponent::Start()
{
    auto map = GetManager().lock()->GetGameObject("Map");
    shp_mapComponent = map.lock()->GetGameComponent< MapComponent>();
    shp_currentMapData = shp_mapComponent->GetCurrentMapData();
    p_mapdata =& shp_mapComponent->GetMapData(0);
    p_mapObjectData = &shp_mapComponent->GetMapObjectData();
    offset = shp_currentMapData->GetSize() / 2;
    offset.Floor();
}

std::shared_ptr<ButiEngine::GameComponent> ButiEngine::MapEditorComponent::Clone()
{
    return ObjectFactory::Create<MapEditorComponent>();
}

void ButiEngine::MapEditorComponent::OnShowUI()
{
}

std::shared_ptr<ButiEngine::GameObject> ButiEngine::MapEditorComponent::Replace(const Vector3& arg_pos, const std::string& arg_blockName, const int blockNum)
{
    Vector3 position = Vector3(arg_pos.z,arg_pos.x,arg_pos.y);
    Vector3 scale(GameSettings::BlockSize, GameSettings::BlockSize, GameSettings::BlockSize);
    position -= offset;
    position *= GameSettings::BlockSize;
    p_mapdata->mapData[arg_pos.x][arg_pos.y][arg_pos.z] =blockNum;
    shp_currentMapData->mapData[arg_pos.x][arg_pos.y][arg_pos.z] = blockNum;
    auto gameObject = GetManager().lock()->AddObjectFromCereal(arg_blockName);
    gameObject.lock()->transform->SetWorldPosition(position);

    if ((*p_mapObjectData)[arg_pos.x][arg_pos.y][arg_pos.z]) {

        (*p_mapObjectData)[arg_pos.x][arg_pos.y][arg_pos.z]->SetIsRemove(true);
    }

    (*p_mapObjectData)[arg_pos.x][arg_pos.y][arg_pos.z] = gameObject.lock();

    return gameObject.lock();
}
