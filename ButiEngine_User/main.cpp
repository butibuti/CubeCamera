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

	auto app = CreateDefaultApplicationInstance("Find", WindowPopType::max, 1080,720, false);
	GameDevice::Initialize();
	GameDevice::GetInput()->Initialize(app);

	
	//ModelFileConverter::FBXtoB3M("Player.fbx", "Player.b3m", "Model/Cubes/player/");
	app->InitLoadResources();
<<<<<<< HEAD
	//ComponentsLoader::GetInstance()->AddGameComponent<ThanksSceneManager>();
=======
	ComponentsLoader::GetInstance()->AddGameComponent<InvisibleBlockAuraComponent>();
>>>>>>> 268a1845b06874291b163db627200c1a6a8b493d
	
	app->GetSceneManager()->LoadScene_Init_EditMode("TitleScene");

	app->GetGraphicDevice()->SetClearColor(Vector4(0, 0, 0, 1));
	int returnCode = app->Run();
	

	app->Exit();

	return returnCode;
}