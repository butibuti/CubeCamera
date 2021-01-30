#pragma once
#include"stdafx.h"
#include"../Resources/WaveDatas.h"
namespace ButiEngine {
	class SoundManager:public ISoundManager
	{
	public:
		SoundManager(std::weak_ptr<IScene> arg_wkp_iscene);
		~SoundManager();
		void Initialize()override;
		void StopCheck()override;
		void Update()override;
		void ClearCheck()override;
		void Play(SoundTag tag, float volume)override;
		void PlayBGM(SoundTag tag,float volume)override;
		void Stop()override;
		void StopBGM()override;
		void ReStartSE() override;
		void DestroySE() override;
		void Release()override;
		void ReStartBGM(float volume)override;
		void SetBGMVolume(float volume)override;
	private:
		IXAudio2SourceVoice* cmp_bgm;
		IXAudio2MasteringVoice* p_masterVoice;
		Microsoft::WRL::ComPtr< IXAudio2> cmp_pXAudio2;
		std::vector<IXAudio2SourceVoice*> vec_seVoices;
		std::shared_ptr<Timer> shp_clearCheckTimer; 
		std::weak_ptr<IScene> wkp_iscene;
	};
}

