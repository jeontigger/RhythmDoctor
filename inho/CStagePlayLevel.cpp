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

#include "CUnitBar.h"
#include "CCharacter.h"
#include "CNote.h"
#include "CNormalNote.h"
#include "CBeatNote.h"
#include "CWindowEvent.h"


CStagePlayLevel::CStagePlayLevel(): 
	m_AccTime(0.f)
{
}

CStagePlayLevel::~CStagePlayLevel()
{
	m_listNoteInfo.clear();
}

void CStagePlayLevel::init()
{

	m_UnitBar = new CUnitBar;
	AddObject(PLAYER, m_UnitBar);

	Vec2 vRes = CEngine::GetInst()->GetResolution();
	
	CTexture* pAtlas;
	CAnimator* pAnimator;


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

	for (int i = 0; i < 10; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 13.7f + i *1.63f;
		noteinfo->Speed = 180.f;
		noteinfo->GetDuration = 0.5f;
		noteinfo->Cnt = 1;
		m_listNoteInfo.push_back(noteinfo);
	}
}

void CStagePlayLevel::enter()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_Intro", L"sound\\sndAllTheTimes.wav");
	pSound->PlayToBGM(false);
}


void CStagePlayLevel::exit()
{
}

void CStagePlayLevel::tick()
{
	CLevel::tick();
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
			delete noteinfo;
		}
	}

#pragma region Presentation

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
	if(KEY_TAP(SPACE)) {
		m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
	}


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

void CStagePlayLevel::Judge()
{
	
}