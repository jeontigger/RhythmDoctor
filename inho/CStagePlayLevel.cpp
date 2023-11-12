#include "pch.h"
#include "CStagePlayLevel.h"

#include "CCamera.h"
#include "CEngine.h"
#include "CBtnUI.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CLogMgr.h"

#include "CUnitBar.h"
#include "CCharacter.h"
#include "CNote.h"
#include "CNormalNote.h"
#include "CBeatNote.h"
#include "CWindowEvent.h"
#include "CBackground.h"


CStagePlayLevel::CStagePlayLevel(): 
	m_AccTime(0.f)
{
}

CStagePlayLevel::~CStagePlayLevel()
{
	for (auto iter = m_listNoteInfo.begin(); iter != m_listNoteInfo.end(); ++iter) {
		delete* iter;
	}
	for (auto iter = m_listBarInfo.begin(); iter != m_listBarInfo.end(); ++iter) {
		delete* iter;
	}
	
}

void CStagePlayLevel::init()
{
	CTexture* pAtlas;
	CAnimator* pAnimator;
	Vec2 vRes = CEngine::GetInst()->GetResolution();

	m_ColeBGBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBGBG", L"texture\\ColeBGBG.png");
	pAnimator = m_ColeBGBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ColeBGBG", pAtlas, Vec2(0, 0), Vec2(352, 119), Vec2(0, 0), 0.1f, 3);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ColeBGBG", true);
	m_ColeBGBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f -55.f });
	m_ColeBGBG->SetScale({ 352, 119 });
	AddObject(BACKGROUND, m_ColeBGBG);

	m_ColeBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBG", L"texture\\ColeBG.png");
	m_ColeBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f + 77.f });
	m_ColeBG->SetScale({ pAtlas->GetWidth(), pAtlas->GetHeight() });
	m_ColeBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, m_ColeBG);


	m_UnitBar = new CUnitBar;
	AddObject(PLAYER, m_UnitBar);

	



	m_Hand = new CCharacter;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"HandAtlas", L"texture\\Hand.png");
	float height = pAtlas->GetHeight();
	m_Hand->SetPos({ vRes.x / 2.f +  100.f, vRes.y - height / 2.f + 12.f });
	m_Hand->SetScale({ 300, 42 });
	pAnimator = m_Hand->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Hand", pAtlas, Vec2(0, 0), Vec2(307, 42), Vec2(0, 0), 0.1f, 3);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\Hand.txt");
	pAnimator->Play(L"Hand", false);
	AddObject(PLAYER, m_Hand);



	CWindowEvent* newEvent = new CWindowEvent;
	CEventMgr::GetInst()->RegistWindowEvent(newEvent);

	CBeatNote* newNote = new CBeatNote;
	CEventMgr::GetInst()->RegistNoteEvent(newNote);

	for (int i = 0; i < 100; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 13.7f + i *1.657f;
		noteinfo->Speed = 400.f;
		noteinfo->GetDuration = 0.4f;
		noteinfo->Cnt = 1;
		noteinfo->JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	BarInfo* barinfo = new BarInfo;
	barinfo->Moving = true;
	barinfo->StartTime = 12.7f;
	barinfo->Speed = 40.f;
	barinfo->Duration = 0.5f;

	m_listBarInfo.push_back(barinfo);
}

void CStagePlayLevel::enter()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	m_BGSound = CAssetMgr::GetInst()->LoadSound(L"BGM_Intro", L"sound\\sndAllTheTimes.wav");
	
	CWindowEvent* event =  CEventMgr::GetInst()->GetWindowEvent();
	
	event->SetPos(event->GetMonitorRes()/2 - event->GetWinRes() / 2);

}


void CStagePlayLevel::exit()
{
}

void CStagePlayLevel::tick()
{

	CLevel::tick();

	if (!m_bAnyPressed) {
		AnyPress();
	}
	else {
		auto newEvent = CEventMgr::GetInst()->GetWindowEvent();
		auto newNoteEvent = dynamic_cast<CBeatNote*>(CEventMgr::GetInst()->GetNoteEvents()[0]);

		m_AccTime += DT;

		if (!m_listNoteInfo.empty()) {
			NoteInfo* noteinfo = m_listNoteInfo.front();
			if (noteinfo->StartTime <= m_AccTime) {
				newNoteEvent->SetBar(m_UnitBar);
				newNoteEvent->SetBeatSpeed(noteinfo->Speed);
				newNoteEvent->SetLoopCount(noteinfo->Cnt);
				newNoteEvent->SetLoopDuration(noteinfo->GetDuration);
				newNoteEvent->Play();
				m_listNoteInfo.pop_front();

				m_NoteJudgeTime = noteinfo->StartTime + noteinfo->JudgeTime;
				m_newNote = true;

				delete noteinfo;
			}
		}

		if (!m_listBarInfo.empty()) {
			BarInfo* barinfo = m_listBarInfo.front();
			if (barinfo->StartTime <= m_AccTime) {
				m_UnitBar->SetMoving(barinfo->Moving);
				m_UnitBar->SetMovingSpeed(barinfo->Speed);
				m_UnitBar->SetMovingDuration(barinfo->Duration);

				
			}
		}

		Judge();

		if (KEY_TAP(SPACE)) {
			m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
		}
		if (KEY_TAP(O)) {
			LOG(LOG_LEVEL::WARNING, L"보정 Offset 빠르게");
			m_NoteJudgeTimeOffset -= 0.016f;
		}
		if (KEY_TAP(P)) {
			LOG(LOG_LEVEL::WARNING, L"보정 Offset 느리게");
			m_NoteJudgeTimeOffset += 0.016f;
		}

#pragma region UseCase

		/*
		if (KEY_TAP(W)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 1200, 10 });
		}
		if (KEY_TAP(E)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 1200, 600 });
		}
		if (KEY_TAP(R)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 10,600 });
		}
		if (KEY_TAP(A)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 10, 10 }, 1);
		}
		if (KEY_TAP(S)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 1200, 10 }, 1);
		}
		if (KEY_TAP(D)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 1200, 600 }, 1);
		}
		if (KEY_TAP(F)) {
			newEvent->SetMode(WindowEventType::LinearMove);
			newEvent->SetTarget({ 10, 600 }, 1);
		}
		if (KEY_TAP(Z)) {
			newEvent->SetMode(WindowEventType::Quake);
			newEvent->SetQuakeAmount(5);
		}
		if (KEY_TAP(X)) {
			newEvent->SetMode(WindowEventType::UpAndDown);
			newEvent->SetTarget({ 1200, 340 },0.1);
			newEvent->SetUpDownSize(50);
			newEvent->SetUpDownCount(3);
		}
		if (KEY_TAP(C)) {
			newEvent->SetMode(WindowEventType::Jumping);
			newEvent->SetJumpingSpeed(0.1f);
			newEvent->SetJumpingSize(200.f);
		}
		if (KEY_TAP(V)) {
			CBeatNote* newNote = new CBeatNote;
			newNote->SetBeatSpeed(60.f);
			newNote->SetBar(m_UnitBar);
			newNote->SetLoopCount(1);
			CEventMgr::GetInst()->Play(newNote);
		}
		if (KEY_TAP(B)) {
			CNormalNote* newNote = new CNormalNote;
			newNote->SetBeatSpeed(0.3f);
			newNote->SetBar(m_UnitBar);
			CEventMgr::GetInst()->Play(newNote);
		}
		if (KEY_TAP(ESC)) {
			ChangeLevel(LEVEL_TYPE::STAGE_SELECT_LEVEL);
		}
		*/
		

		if (KEY_TAP(A)) {
			newEvent->SetMode(WindowEventType::Disapear);
			newEvent->SetDisapearSpeed(0.3f);
			newEvent->SetDisapearDistance(300.f);
		}
		if (KEY_TAP(S)) {
			newEvent->SetPos({ 0, 540 - 198 });
			newEvent->SetMode(WindowEventType::Wave);
			newEvent->SetWaveSpeed(200.f);
			newEvent->SetWaveFrequency(60.f);
			newEvent->SetWaveSize(240.f);
		}

		if (KEY_TAP(D)) {
			newEvent->SetMode(WindowEventType::PortalMove);
			newEvent->SetPortalDirection(PortalDirection::Right);
			newEvent->SetSpeed(800.f);
		}

		if (KEY_TAP(F)) {
			newEvent->SetMode(WindowEventType::PortalMove);
			newEvent->SetPortalDirection(PortalDirection::Bottom);
			newEvent->SetSpeed(800.f);
		}
		if (KEY_TAP(G)) {
			newEvent->SetMode(WindowEventType::PortalMove);
			newEvent->SetPortalDirection(PortalDirection::Left);
			newEvent->SetSpeed(800.f);
		}
		if (KEY_TAP(H)) {
			newEvent->SetMode(WindowEventType::PortalMove);
			newEvent->SetPortalDirection(PortalDirection::Top);
			newEvent->SetSpeed(800.f);
		}

#pragma endregion
	}

	
}

void CStagePlayLevel::AnyPress()
{
	if (KEY_TAP(SPACE)) {
		m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
		m_BGSound->PlayToBGM(false);
		m_UnitBar->Start(true);
		m_bAnyPressed = true;
	}
	return;
	
}

void CStagePlayLevel::Judge()
{
	if (m_NoteJudgeTime - JudgeTime + m_NoteJudgeTimeOffset <= m_AccTime+ m_NoteJudgeTimeOffset 
		&& m_AccTime + m_NoteJudgeTimeOffset < m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE)) {
			LOG(ERR, L"빠름");
			m_newNote = false;
		}
	}
	else if (m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset <= m_AccTime + m_NoteJudgeTimeOffset 
		&& m_AccTime + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE)) {
			LOG(ERR, L"판정!");
			m_newNote = false;
			CCamera::GetInst()->Judge(0.1f);
			CCamera::GetInst()->Zoom(30.f, 0.3f);
			m_UnitBar->GetSpaceBarSprite()->FadeAway(0.3f);
			
		}
	}
	else if (m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset < m_AccTime + m_NoteJudgeTimeOffset
		&& m_AccTime + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE)) {
			LOG(ERR, L"느림");
			m_newNote = false;
		}
	}
	else if (m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset < m_AccTime + m_NoteJudgeTimeOffset) {
		if (m_newNote) {
			LOG(ERR, L"놓침");
			m_newNote = false;
		}
	}
}