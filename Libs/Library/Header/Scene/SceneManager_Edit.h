#pragma once
#ifndef _SceneManager_Edit_H_
#define _SceneManager_Edit_H_

#include"stdafx.h"
#include"SceneManager.h"
namespace ButiEngine {
	class IApplication;
	class SceneManager_Edit :public SceneManager
	{
	public:
		SceneManager_Edit(std::weak_ptr<IApplication> arg_wkp_app);
		void Initialize()override;
		void Update()override;
		void UIUpdate();

		void ChangeScene(const std::string& arg_sceneName, float sceneChangeDalay = 0)override;
		void LoadScene(const std::string& arg_sceneName, std::shared_ptr<SceneInformation> shp_scene = nullptr) override;
		void LoadScene_Init(const std::string& arg_sceneName, std::shared_ptr<SceneInformation> shp_scene = nullptr) override;
	private:

		bool isActive = false;
		bool isPlaying = false;
		bool showCollisionManager = false;

		bool showHeirarcy = true;

		bool showInspector = true;

		bool showContainer = true;

		bool showCamera = false;

		UINT startCount = 0;
	};
}
#endif // !_SceneManager_Edit_H_