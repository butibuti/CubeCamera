#include"stdafx_u.h"
#include"Header/ApplicationCreater.h"
#pragma comment(lib,"ButiEngine.lib")
#include"Header/Scene/ComponentsLoader.h"
#include"Header/Device/ModelFileConverter.h"
#include"CameraController.h"
#include"ThanksSceneManager.h"
//#include"Header/GameObjects/DefaultGameComponent/ChaseComponent.h"
#include"InvisibleBlockAuraComponent.h"

using namespace::ButiEngine;

#ifdef DEBUG

int main() {
	std::cout << "debug" << std::endl;

#else

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//int main()
{
#endif

	auto app = CreateDefaultApplicationInstance("Find", WindowPopType::normal, 1920,1080, true);
	GameDevice::Initialize();
	GameDevice::GetInput()->Initialize(app);
	GameDevice::GetInput()->SetCursorHide(true);

	
	//ModelFileConverter::FBXtoB3M("Player.fbx", "Player.b3m", "Model/Cubes/player/");
	app->InitLoadResources();
	//ComponentsLoader::GetInstance()->AddGameComponent<ThanksSceneManager>();
	
	app->GetSceneManager()->LoadScene_Init("TitleScene");

	app->GetGraphicDevice()->SetClearColor(Vector4(0, 0, 0, 1));
	int returnCode = app->Run();
	

	app->Exit();

	return returnCode;
}