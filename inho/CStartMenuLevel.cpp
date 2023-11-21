#include "pch.h"
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

#include "CLogMgr.h"

void CStartMenuLevel::init()
{
	// 배경 생성
	CBackground* bg = new CBackground;
	bg->SetTexture(L"StartBG", L"texture\\BG.png");
	bg->SetPos({ 300, 375 });

	bg->SetScale({ bg->GetWidth(),bg->GetHeight()});
	bg->SetAlpha(50);
	
	AddObject(BACKGROUND, bg);

	// 아무 버튼이나 누르세요 텍스트 생성
	// Todo : 점멸
	m_AnyPress = new CTextUI;
	m_AnyPress->SetPos({ 260.f,300.f });
	m_AnyPress->SetText(L"아무 버튼이나 누르세요");
	AddObject(UI, m_AnyPress);

	// 모니터 생성
	m_Monitor = new CAnimUI;
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"LogoMonitor", L"texture\\Logo_Monitor.png");
	m_Monitor->GetAnimator()->CreateAnimation(L"MonitorFallDown", pAtlas, Vec2(0.f, 0.f), Vec2(184, 134), {0,0}, 0.05f, 4);
	m_Monitor->SetPos({ 354, 185 });
	m_Monitor->SetScale({ 184, 134});
	
	AddObject(UI, m_Monitor);

	// 리듬 생성 후 모니터에 추가
	m_Rhythm = new CAnimUI;
	m_Rhythm->GetAnimator()->LoadAnimation(L"animdata\\Rhythm.txt");
	
	m_Rhythm->SetScale({ 130,36 });
	m_Rhythm->SetPos(Vec2(-10.f, -20.f));
	m_Rhythm->GetAnimator()->Play(L"Rhythm", true);
	m_Monitor->AddChildUI(m_Rhythm);
	
	
	// 닥터 생성 후 모니터에 추가
	m_Doctor = new CAnimUI;
	m_Doctor->GetAnimator()->LoadAnimation(L"animdata\\LogoDoctor.txt");

	m_Doctor->SetScale({ 114,46 });
	m_Doctor->SetPos(Vec2(-10.f, 33.f));
	m_Doctor->GetAnimator()->Play(L"LogoDoctor", false);
	m_Monitor->AddChildUI(m_Doctor);
	m_bHeartBeat = false;

	// 메뉴 버튼들 생성
	for (int i = 0; i < StartMenuSize; ++i) {
		CTextUI* menu = new CTextUI;
		menu->SetPos({ 750.f, 92.f + i * 30.f });
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

	m_vecMenus[0]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::STAGE_SELECT_LEVEL); });
	m_vecMenus[1]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL); });
	m_vecMenus[2]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL);});
	m_vecMenus[3]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL);});
	m_vecMenus[4]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL);});
	m_vecMenus[5]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL);});
	m_vecMenus[6]->SetCallBack([]() {ChangeLevel(LEVEL_TYPE::START_MENU_LEVEL); });
	
	m_vecMenus[7]->SetCallBack([]() {DestroyWindow(CEngine::GetInst()->GetMainWind()); });

	m_curMenu = m_vecMenus[0];

	// 커서 생성
	m_Cursor = new CAnimUI;
	//pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Cursor", L"texture\\Cursor.png");

	//m_Cursor->GetAnimator()->CreateAnimation(L"Cursor", pAtlas, Vec2(0.f, 0.f), Vec2(3, 5), { 0,0 }, 0.05f, 1);
	m_Cursor->GetAnimator()->LoadAnimation(L"animdata\\Cursor.txt");
	m_Cursor->SetScale({ 3.f, 5.f });
	
	m_Cursor->SetPos({ 740.f, 100.f });
	m_Cursor->GetAnimator()->Play(L"Cursor", true);
	AddObject(UI, m_Cursor);

	m_sndBGM = CAssetMgr::GetInst()->LoadSound(L"BGM_Intro", L"sound\\Intro.wav");
	m_sndCursorMove = CAssetMgr::GetInst()->LoadSound(L"sndCursorMove", L"sound\\sndCursorMove.wav");
	m_sndMenuEnter = CAssetMgr::GetInst()->LoadSound(L"sndMenuEnter", L"sound\\sndMenuEnter.wav");
	m_sndMenuCancel = CAssetMgr::GetInst()->LoadSound(L"sndMenuCancel", L"sound\\sndMenuCancel.wav");

}

void CStartMenuLevel::enter()
{

	m_sndBGM->SetVolume(80);
	m_sndBGM->SetPosition(0.f);
	m_sndBGM->Play();

	m_bOpen = false;

	m_Monitor->SetPos({ 354, 185 });
	// 메뉴 버튼들 생성
	for (int i = 0; i < StartMenuSize; ++i) {
		m_vecMenus[i]->SetPos({ 750.f, 92.f + i * 30.f });
	}
	m_Monitor->GetAnimator()->Play(L"MonitorFallDown", false);
	m_Cursor->SetPos({ 740.f, 100.f });

	m_AnyPress->SetBlink(0.6f, 0.2f);
	
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);
}

void CStartMenuLevel::exit()
{
	//DeleteAllObjects();
	m_sndBGM->Stop(true);
}

void CStartMenuLevel::tick()
{
	CLevel::tick();

	Vec2 vScale = m_Doctor->GetScale();
	float beatScale = 3.f;
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
	
	// 메뉴 출력 in & out
	if (!m_bOpen && CKeyMgr::GetInst()->IsAnyKeyTap()) {
		m_bOpen = true;
		m_sndMenuEnter->Play(false);
		m_Monitor->MoveTo({ m_Monitor->GetPos().x - 100.f,m_Monitor->GetPos().y }, 0.04f);

		for (int i = 0; i < m_vecMenus.size(); i++) {
			m_vecMenus[i]->MoveTo({ m_vecMenus[i]->GetPos().x - 250.f, m_vecMenus[i]->GetPos().y }, 0.04f);
		}
		m_Cursor->MoveTo({ m_Cursor->GetPos().x - 250.f,m_Cursor->GetPos().y }, 0.04f);
		m_AnyPress->SetBlink(0.f, 1.f);
	}
	else if (m_bOpen) {
		if (KEY_TAP(ENTER)) {
			m_curMenu->LBtnClicked({ 0,0 });
		}

		if (KEY_TAP(ESC)) {
			m_bOpen = false;
			m_sndMenuCancel->Play(false);
			m_Monitor->MoveTo({ m_Monitor->GetPos().x + 100.f,m_Monitor->GetPos().y }, 0.04f);
			for (int i = 0; i < m_vecMenus.size(); i++) {
				m_vecMenus[i]->MoveTo({ m_vecMenus[i]->GetPos().x + 250.f, m_vecMenus[i]->GetPos().y }, 0.04f);
			}
			m_Cursor->MoveTo({ m_Cursor->GetPos().x + 250.f,m_Cursor->GetPos().y }, 0.04f);
			m_AnyPress->SetBlink(0.6f, 0.2f);
		}
	}

	if (KEY_TAP(DOWN)) {
		m_iCursorIdx++;
		if (StartMenuSize <= m_iCursorIdx) {
			m_iCursorIdx = 0;
		}
		MoveCursor(m_iCursorIdx);
		
	}
	if (KEY_TAP(UP)) {
		m_iCursorIdx--;
		if (m_iCursorIdx < 0) {
			m_iCursorIdx = StartMenuSize - 1;
		}
		MoveCursor(m_iCursorIdx);
	}

}

void CStartMenuLevel::MoveCursor(int _idx)
{
	Vec2 vPos = m_Cursor->GetPos();
	m_Cursor->MoveTo({ vPos.x, 100.f + _idx * 30.f });
	m_curMenu = m_vecMenus[_idx];

	m_sndCursorMove->Play(false);
}