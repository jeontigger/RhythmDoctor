#include "pch.h"
#include "CStagePlayLevel.h"

#include "CCamera.h"
#include "CEngine.h"
#include "CBtnUI.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"
#include "CEventMgr.h"

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
}

void CStagePlayLevel::enter()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);
}


void CStagePlayLevel::exit()
{
}

void CStagePlayLevel::tick()
{
	CLevel::tick();
	auto newEvent = CEventMgr::GetInst()->GetWindowEvent();
#pragma region Presentation
	
		if (KEY_TAP(Q)) {
		newEvent->SetMode(WindowEventType::LinearMove);
		newEvent->SetTarget({ 10, 10 });
	}
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

	if(KEY_TAP(SPACE)) {
		
		auto newEvent = CEventMgr::GetInst()->GetWindowEvent();
		
		newEvent->SetMode(WindowEventType::CircleMove);

		newEvent->SetSpeed(3.f);
		newEvent->SetRadius(100.f);
		newEvent->SetCW(true);
		newEvent->SetTheta(-PI/2.f);
		

		m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
	}*/
#pragma endregion

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


	/*CNote* note = m_listNotes.front();
	if (m_AccTime <= note->m_StartTime) {
		note->Play(m_UnitBar);
		m_listNotes.pop_front();
	}*/

	


}

void CStagePlayLevel::Judge()
{
	
}