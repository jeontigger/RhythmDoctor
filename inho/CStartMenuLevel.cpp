#include "pch.h"
#include "CStartMenuLevel.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CEngine.h"

#include "CBackground.h"

void CStartMenuLevel::init()
{
	CBackground* bg = new CBackground;
	bg->SetTexture(L"StartBG", L"texture\\BG.png");
	bg->SetPos({ 100, 125 });
	bg->SetScale({ 2,2 });
	bg->SetAlpha(50);
	
	AddObject(BACKGROUND, bg);
	
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);
	
}

void CStartMenuLevel::enter()
{
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	pSound->SetVolume(100);
	pSound->SetPosition(45.f);
	pSound->Play(true);
}

void CStartMenuLevel::exit()
{
	DeleteAllObjects();
}

void CStartMenuLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::W)) {
		
	}

}
