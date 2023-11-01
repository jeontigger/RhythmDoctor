﻿#include "pch.h"
#include "CStartMenuLevel.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CEngine.h"
#include "CTimeMgr.h"

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
	m_AnyPress->SetPos({ 350.f,300.f });
	m_AnyPress->SetText(L"아무 버튼이나 누르세요");
	AddObject(UI, m_AnyPress);

	m_Monitor = new CAnimUI;
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"LogoMonitor", L"texture\\Logo_Monitor.png");
	m_Monitor->GetAnimator()->CreateAnimation(L"MonitorFallDown", pAtlas, Vec2(0.f, 0.f), Vec2(184, 134), {0,0}, 0.05f, 4);
	m_Monitor->SetPos({ 354, 185 });
	m_Monitor->SetScale({ 2, 2});
	
	AddObject(UI, m_Monitor);

	m_Rhythm = new CAnimUI;
	//pAtlas = CAssetMgr::GetInst()->LoadTexture(L"LogoRhythm", L"texture\\logo_rhythm.png");
	m_Rhythm->GetAnimator()->LoadAnimation(L"animdata\\Rhythm.txt");
	
	m_Rhythm->SetScale({ 2,2 });
	m_Rhythm->SetPos(Vec2(-10.f, -20.f));
	m_Rhythm->GetAnimator()->Play(L"Rhythm", true);
	m_Monitor->AddChildUI(m_Rhythm);
	
	m_Doctor = new CAnimUI;
	//pAtlas = CAssetMgr::GetInst()->LoadTexture(L"LogoDoctor", L"texture\\logo_doctor.png");
	//doctor->GetAnimator()->CreateAnimation(L"LogoDoctor4", pAtlas, Vec2(0.f, 184.f), Vec2(114, 46), { 0,0 }, 0.05f, 4);
	//doctor->GetAnimator()->SaveAnimation(L"animdata");
	m_Doctor->GetAnimator()->LoadAnimation(L"animdata\\LogoDoctor.txt");

	m_Doctor->SetScale({ 2,2 });
	m_Doctor->SetPos(Vec2(-10.f, 33.f));
	m_Doctor->GetAnimator()->Play(L"LogoDoctor", false);
	m_Monitor->AddChildUI(m_Doctor);
	m_bHeartBeat = false;


	for (int i = 0; i < StartMenuSize; ++i) {
		CTextUI* menu = new CTextUI;
		menu->SetPos({ 530.f, 92.f + i * 30.f });
		m_vecMenus.push_back(menu);
		AddObject(UI, menu);
	}

	m_vecMenus[0]->SetText(L"스토리모드");
	m_vecMenus[1]->SetText(L"커스텀 레벨");
	m_vecMenus[2]->SetText(L"레벨 에디터");
	m_vecMenus[3]->SetText(L"보정");
	m_vecMenus[4]->SetText(L"설정");
	m_vecMenus[5]->SetText(L"제작진");
	m_vecMenus[6]->SetText(L" OST(YouTube로 이동)");
	m_vecMenus[7]->SetText(L"나가기");

	
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
	m_Monitor->GetAnimator()->Play(L"MonitorFallDown", false);
	
}

void CStartMenuLevel::exit()
{
	DeleteAllObjects();
}

void CStartMenuLevel::tick()
{
	CLevel::tick();
	if (KEY_TAP(ESC)) {
		m_Monitor->GetAnimator()->Play(L"MonitorFallDown", false);
	}

	Vec2 vScale = m_Doctor->GetScale();
	float beatScale = 0.05f;
	if (m_bHeartBeat && 0.03f <= m_AccTime) {
		m_Doctor->SetScale(vScale - beatScale);
		m_AccTime = 0;
		m_bHeartBeat = false;
	}
	else if(!m_bHeartBeat && 0.9f <= m_AccTime){
		m_Doctor->SetScale(vScale + beatScale);
		m_AccTime = 0;
		m_bHeartBeat = true;
	}
	m_AccTime += DT;
	
	Vec2 vPos = m_Doctor->GetPos();
	if (KEY_TAP(D)) {
		m_Doctor->SetPos({ vPos.x + 1, vPos.y });
	}

}
