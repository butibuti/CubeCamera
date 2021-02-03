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
    static int playerDirection = 0;
    static int goalMode = 0;
    gameObject.lock()->transform->SetLocalPosition(Vector3(blockPos[0], blockPos[1], blockPos[2]) - offset);

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
    GUI::BulletText("GoalMode");
    if (GUI::ArrowButton("##min", GUI::GuiDir_::GuiDir_Left)) {
        goalMode--;
        if (goalMode < 0) {
            goalMode = 2;
        }
    }
    GUI::SameLine();
    GUI::SameLine();
    switch (goalMode)
    {
    case 0:
        GUI::Text("Touch Only");
        break;
    case 1:
        GUI::Text("Already Seen");
        break;
    case 2:
        GUI::Text("Hidden");
        break;
    default:
        break;
    }
    GUI::SameLine();
    if (GUI::ArrowButton("##plus", GUI::GuiDir_::GuiDir_Right)) {
        goalMode++;
        if (goalMode > 2) {
            goalMode = 0;
        }
    }

    if (GUI::Button("Replace Goal")) {
        std::string goalObjName;

        switch (goalMode)
        {
        case 0:
            goalObjName = "TutorialGoal";
            break;
        case 1:
            goalObjName = "EasyGoal";
            break;
        case 2:
            goalObjName = "DefaultGoal";
            break;
        default:
            break;
        }
        auto mapNum = p_mapdata->mapData[1][2][0];
        if (mapNum == GameSettings::player) {
            Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), goalObjName, GameSettings::playerAndGoal + (GameSettings::tutorialGoal + goalMode)*10+0);
        }
        else if (mapNum >= GameSettings::playerRotate_90&& mapNum <= GameSettings::playerRotate_min90) {
            Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), goalObjName, GameSettings::playerAndGoal + (GameSettings::tutorialGoal + goalMode) * 10 + (mapNum+1- GameSettings::playerRotate_90));
         }
        else if (mapNum>=GameSettings::playerAndGoal) {
            int dir = (mapNum - GameSettings::playerAndGoal) % 10;
            Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), goalObjName, GameSettings::playerAndGoal + (GameSettings::tutorialGoal + goalMode) * 10 + dir);
        }
        else {
            Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), goalObjName, GameSettings::tutorialGoal + goalMode);
        }

    }
    if (GUI::Button("Replace InvisibleBlock")) {

        auto gameObject = Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), "InvisibleBlock", GameSettings::invisibleBlock + invisibleID);
        gameObject->GetGameComponent<InvisibleBlockComponent>()->SetID(invisibleID);
        gameObject->GetGameComponent<InvisibleBlockComponent>()->SetMapPos(Vector3(blockPos[0], blockPos[1], blockPos[2]));
    }



    GUI::BulletText("PlayerDirection");
    if (GUI::ArrowButton("##min_dir", GUI::GuiDir_::GuiDir_Left)) {
        playerDirection--;
        if (playerDirection < 0) {
            playerDirection = 3;
        }
    }

    GUI::SameLine();
    switch (playerDirection)
    {
    case 0:
        GUI::Text("Front");
        break;
    case 1:
        GUI::Text("Right");
        break;
    case 2:
        GUI::Text("Back");
        break;

    case 3:
        GUI::Text("Left");
        break;
    default:
        break;
    }
    GUI::SameLine();
    if (GUI::ArrowButton("##plus_dir", GUI::GuiDir_::GuiDir_Right)) {
        playerDirection++;
        if (playerDirection > 3) {
            playerDirection = 0;
        }
    }

    if (GUI::Button("Change PlayerInitPosition")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {
            bool isBreak = false;
            for (int j = 0; j < p_mapdata->mapData[0].size(); j++) {
                for (int k = 0; k < p_mapdata->mapData[0][0].size(); k++) {
                    int num = p_mapdata->mapData[i][j][k];
                    if (num == GameSettings::player || (num >= GameSettings::playerRotate_90 && num <= GameSettings::playerRotate_min90)) {
                        p_mapdata->mapData[i][j][k] = 0;
                        shp_currentMapData->mapData[i][j][k] = 0;
                        isBreak = true;
                        break;
                    }
                    else if (num > GameSettings::playerAndGoal) {
                        int playerGoalID = num - GameSettings::playerAndGoal;
                        int goal = playerGoalID / 10;
                        std::string goalObjName;

                        switch (goal)
                        {
                        case  GameSettings::tutorialGoal:
                            goalObjName = "TutorialGoal";
                            break;
                        case  GameSettings::easyGoal:
                            goalObjName = "EasyGoal";
                            break;
                        case  GameSettings::defaultGoal:
                            goalObjName = "DefaultGoal";
                            break;
                        default:
                            break;
                        }

                        Replace(Vector3(blockPos[i], blockPos[j], blockPos[k]), goalObjName, goal);
                        isBreak = true;
                        break;
                    }
                }

                if (isBreak) {
                    break;
                }
            }

            if (isBreak) {
                break;
            }
        }
        if (playerDirection == 0) {
            auto mapNum = p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]];
            if (mapNum >= GameSettings::tutorialGoal && mapNum <= GameSettings::defaultGoal) {
                std::string goalObjName;

                switch (mapNum)
                {
                case  GameSettings::tutorialGoal:
                    goalObjName = "TutorialGoal";
                    break;
                case  GameSettings::easyGoal:
                    goalObjName = "EasyGoal";
                    break;
                case  GameSettings::defaultGoal:
                    goalObjName = "DefaultGoal";
                    break;
                default:
                    break;
                }

                Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), goalObjName,GameSettings::playerAndGoal+ mapNum*10);
            }
            else {
                p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = GameSettings::player;
                shp_currentMapData->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = GameSettings::player;
            }

        }
        else {
            int playerNum = GameSettings::playerRotate_90 + playerDirection - 1;

            auto mapNum = p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]];
            if ((mapNum >= GameSettings::tutorialGoal && mapNum <= GameSettings::defaultGoal)) {
                std::string goalObjName;

                switch (mapNum)
                {
                case  GameSettings::tutorialGoal:
                    goalObjName = "TutorialGoal";
                    break;
                case  GameSettings::easyGoal:
                    goalObjName = "EasyGoal";
                    break;
                case  GameSettings::defaultGoal:
                    goalObjName = "DefaultGoal";
                    break;
                default:
                    break;
                }

                Replace(Vector3(blockPos[1], blockPos[2], blockPos[0]), goalObjName, GameSettings::playerAndGoal + mapNum * 10 + playerNum);
            }

            p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]] =playerNum ;
            shp_currentMapData->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = playerNum;
        }

    }

    if (GUI::Button("Remove")) {
        if ((*p_mapObjectData)[blockPos[1]][blockPos[2]][blockPos[0]]) {


            p_mapdata->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = 0;
            shp_currentMapData->mapData[blockPos[1]][blockPos[2]][blockPos[0]] = 0;

            (*p_mapObjectData)[blockPos[1]][blockPos[2]][blockPos[0]]->SetIsRemove(true);
            (*p_mapObjectData)[blockPos[1]][blockPos[2]][blockPos[0]] = nullptr;
        }

    }


    GUI::BulletText("New BlockRange");
    if (GUI::DragInt3("##position_edgeOne", blockPos_edgeOne, 1.0, 0, 300)) {

        blockPos_edgeOne[0] = min(blockPos_edgeOne[0], size.x - 1);
        blockPos_edgeOne[1] = min(blockPos_edgeOne[1], size.y - 1);
        blockPos_edgeOne[2] = min(blockPos_edgeOne[2], size.z - 1);
    }
    if (GUI::DragInt3("##position_edgeTwo", blockPos_edgeTwo, 1.0, 0, 300)) {

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
                    gameObject->GetGameComponent<InvisibleBlockComponent>()->SetMapPos(Vector3(blockPos[0], blockPos[1], blockPos[2]));
                }
            }
        }
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
        for (int i = 0; i < p_mapdata->mapData[0].size(); i++) {

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
    }
    GUI::SameLine();
    if (GUI::Button("Remove Y")) {
        p_mapdata->mapData.pop_back();
        shp_currentMapData->mapData.pop_back();

        for (int i = p_mapdata->mapData.size(); i < p_mapdata->mapData.size() + 1; i++) {
            for (int j = 0; j < p_mapdata->mapData[0].size(); j++) {

                for (int k = 0; k < p_mapdata->mapData[0][0].size(); k++) {
                    if ((*p_mapObjectData)[i][j][k])
                        (*p_mapObjectData)[i][j][k]->SetIsRemove(true);
                }
            }
        }
        (*p_mapObjectData).pop_back();
    }
    GUI::SameLine();
    if (GUI::Button("Remove Z")) {
        for (int i = 0; i < p_mapdata->mapData.size(); i++) {

            p_mapdata->mapData[i].pop_back();
            shp_currentMapData->mapData[i].pop_back();
            for (int j = p_mapdata->mapData[i].size(); j < p_mapdata->mapData[i].size() + 1; j++) {

                for (int k = 0; k < p_mapdata->mapData[i][0].size(); k++) {
                    if ((*p_mapObjectData)[i][j][k])
                        (*p_mapObjectData)[i][j][k]->SetIsRemove(true);
                }
            }
            (*p_mapObjectData)[i].pop_back();
        }
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
        OutputCereal(output, path);
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
    p_mapdata = &shp_mapComponent->GetMapData(0);
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
    Vector3 position = Vector3(arg_pos.z, arg_pos.x, arg_pos.y);
    Vector3 scale(GameSettings::BlockSize, GameSettings::BlockSize, GameSettings::BlockSize);
    position -= offset;
    position *= GameSettings::BlockSize;
    p_mapdata->mapData[arg_pos.x][arg_pos.y][arg_pos.z] = blockNum;
    shp_currentMapData->mapData[arg_pos.x][arg_pos.y][arg_pos.z] = blockNum;
    auto gameObject = GetManager().lock()->AddObjectFromCereal(arg_blockName);
    gameObject.lock()->transform->SetWorldPosition(position);

    if ((*p_mapObjectData)[arg_pos.x][arg_pos.y][arg_pos.z]) {

        (*p_mapObjectData)[arg_pos.x][arg_pos.y][arg_pos.z]->SetIsRemove(true);
    }

    (*p_mapObjectData)[arg_pos.x][arg_pos.y][arg_pos.z] = gameObject.lock();

    return gameObject.lock();
}