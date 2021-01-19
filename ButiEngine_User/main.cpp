#include"stdafx_u.h"
#include"Header/ApplicationCreater.h"
#pragma comment(lib,"ButiEngine.lib")
#include"Header/Scene/ComponentsLoader.h"
#include"Header/Device/ModelFileConverter.h"

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

	auto app = CreateDefaultApplicationInstance("cubegame", WindowPopType::max, 1080,720, false);
	GameDevice::Initialize();
	GameDevice::GetInput()->Initialize(app);

	ModelFileConverter::FBXtoB3M("Player.fbx", "Player.b3m", "Model/");

	app->InitLoadResources();

	//ComponentsLoader::GetInstance()->AddGameComponent<ChaseComponent>();

	app->GetSceneManager()->LoadScene_Init_EditMode("CollisionScene");
	//app->GetSceneManager()->LoadScene_Init("CollisionScene");

	app->GetGraphicDevice()->SetClearColor(Vector4(180.0f / 255, 180.0f / 255, 1, 1));
	int returnCode = app->Run();


	app->Exit();

	return returnCode;
}