#include "pch.h"
#include "CStartMenuLevel.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CEngine.h"

#include "CBackground.h"
#include "CTextUI.h"
#include "CAnimUI.h"

void CStartMenuLevel::init()
{
	CBackground* bg = new CBackground;
	bg->SetTexture(L"StartBG", L"texture\\BG.png");
	bg->SetPos({ 100, 125 });
	bg->SetScale({ 2,2 });
	bg->SetAlpha(50);
	
	AddObject(BACKGROUND, bg);

	m_AnyPress = new CTextUI;
	m_AnyPress->SetPos({ 300.f,300.f });
	m_AnyPress->SetText(L"아무 버튼이나 누르세요");
	AddObject(UI, m_AnyPress);

	m_Monitor = new CAnimUI;
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"LogoMonitor", L"texture\\Logo_Monitor.png");
	m_Monitor->GetAnimator()->CreateAnimation(L"MonitorFallDown", pAtlas, Vec2(0.f, 0.f), Vec2(184, 134), {0,60}, 0.05f, 4);
	m_Monitor->GetAnimator()->Play(L"MonitorFallDown", false);
	m_Monitor->SetPos({ 300, 00 });
	m_Monitor->SetScale({ 2, 2});
	AddObject(UI, m_Monitor);


	
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

}
