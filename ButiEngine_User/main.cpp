#include"stdafx_u.h"
#include"Header/ApplicationCreater.h"
#pragma comment(lib,"ButiEngine.lib")
#include"Header/Scene/ComponentsLoader.h"
#include"Header/Device/ModelFileConverter.h"
#include"CameraController.h"
#include"BlockComponent.h"
//#include"Header/GameObjects/DefaultGameComponent/ChaseComponent.h"

using namespace::ButiEngine;

#ifdef DEBUG

int main() {
	std::cout << "debug" << std::endl;

#else

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//int main()
{
#endif

	auto app = CreateDefaultApplicationInstance("cubegame_editor", WindowPopType::max, 1080,720, false);
	GameDevice::Initialize();
	GameDevice::GetInput()->Initialize(app);

	
	//ModelFileConverter::FBXtoB3M("Player.fbx", "Player.b3m", "Model/Cubes/player/");
	app->InitLoadResources();
	//ComponentsLoader::GetInstance()->AddGameComponent<ShakeComponent>();
	
	app->GetSceneManager()->LoadScene_Init_EditMode("Stage0Scene");

	app->GetGraphicDevice()->SetClearColor(Vector4(0, 0, 0, 1));
	int returnCode = app->Run();
	

	app->Exit();

	return returnCode;
}