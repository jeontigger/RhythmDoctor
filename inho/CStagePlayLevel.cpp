﻿#include "pch.h"
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
#include "CLevelMgr.h"
#include "CPathMgr.h"

#include "CUnitBar.h"
#include "CCharacter.h"
#include "CNote.h"
#include "CNormalNote.h"
#include "CBeatNote.h"
#include "CWindowEvent.h"
#include "CBackground.h"
#include "CObjEvent.h"
#include "CThermometer.h"
#include "CPausePhone.h"

#include "Resource.h"
#include <fstream>


CStagePlayLevel::CStagePlayLevel() :
	m_AccTime(0.f)
{
}

CStagePlayLevel::~CStagePlayLevel()
{
}

void CStagePlayLevel::init()
{
	CTexture* pAtlas;
	CAnimator* pAnimator;
	CBackground* pBG;
	Vec2 vRes = CEngine::GetInst()->GetResolution();

	m_vecStageObjects.resize((UINT)StageObj::END);

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingBG", L"texture\\TingBG.png");
	pBG->SetScale({ pAtlas->GetWidth() + 8, pAtlas->GetHeight() + 2 });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);
	m_vecStageObjects[(UINT)StageObj::TingBG] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingBGOpen", L"texture\\TingBGOpen.png");
	pBG->SetScale({ pAtlas->GetWidth() + 8, pAtlas->GetHeight() + 2 });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);
	m_vecStageObjects[(UINT)StageObj::TingBGOpen] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBGBG", L"texture\\ColeBGBG.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ColeBGBG", pAtlas, Vec2(0, 0), Vec2(352, 119), Vec2(0, 0), 0.1f, 3);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ColeBGBG", true);
	pBG->SetScale({ 352, 119 });
	AddObject(BACKGROUND, pBG);
	m_vecStageObjects[(UINT)StageObj::ColeBGBack] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBG", L"texture\\ColeBG.png");
	pBG->SetScale({ pAtlas->GetWidth(), pAtlas->GetHeight() });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);
	m_vecStageObjects[(UINT)StageObj::ColeBGFront] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"blueskyPixel", L"texture\\blueskyPixel.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"blueskyPixel", pAtlas, Vec2(0, 0), Vec2(4, 4), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"blueskyPixel", true);
	pBG->SetScale({ 720, 398 });
	AddObject(BACKGROUND, pBG);
	m_vecStageObjects[(UINT)StageObj::BlueSky] = pBG;

	for (int i = 0; i < 3; i++) {
		pBG = new CBackground;
		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"blackPixel", L"texture\\blackPixel.png");
		pBG->SetScale({ vRes.x, 50.f });
		pBG->SetTexture(pAtlas);
		AddObject(STAGE, pBG);
		m_vecStageObjects[(UINT)StageObj::BVeil + i] = pBG;
	}

	m_vecBars.resize((UINT)BarType::END);

	m_UnitBar = new CUnitBar;
	AddObject(PLAYER, m_UnitBar);
	pAnimator = m_UnitBar->GetCharacterAnimator();
	pAnimator->LoadAnimation(L"animdata\\Ting.txt");
	pAnimator->LoadAnimation(L"animdata\\TingCorrect.txt");
	pAnimator->LoadAnimation(L"animdata\\TingIncorrect.txt");
	pAnimator->LoadAnimation(L"animdata\\TingMiss.txt");
	m_vecStageObjects[(UINT)StageObj::TingBar] = m_UnitBar;
	m_vecBars[(UINT)BarType::Ting] = m_UnitBar;

	m_UnitBar = new CUnitBar;
	AddObject(PLAYER, m_UnitBar);
	pAnimator = m_UnitBar->GetCharacterAnimator();
	pAnimator->LoadAnimation(L"animdata\\ColeIdle.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeCorrect.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeIncorrect.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeMiss.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeRun.txt");
	m_vecStageObjects[(UINT)StageObj::Bar] = m_UnitBar;
	m_vecBars[(UINT)BarType::Cole] = m_UnitBar;

	m_Ting = new CCharacter;
	m_Ting->SetScale({ 40, 40 });
	pAnimator = m_Ting->GetComponent<CAnimator>();
	pAnimator->LoadAnimation(L"animdata\\Ting.txt");
	pAnimator->Play(L"Idle", true);
	AddObject(PLAYER, m_Ting);
	m_vecStageObjects[(UINT)StageObj::Ting] = m_Ting;

	m_Cole = new CCharacter;
	m_Cole->SetScale({ 40, 40 });
	//pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeAtlas", L"texture\\Cole.png");
	pAnimator = m_Cole->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Ting", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.1f, 6);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\ColeIdle.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeRun.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeTired.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeLookUp.txt");
	pAnimator->Play(L"Idle", true);
	AddObject(PLAYER, m_Cole);
	m_vecStageObjects[(UINT)StageObj::Cole] = m_Cole;

	m_Boss = new CCharacter;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Boss", L"texture\\Boss.png");
	pAnimator = m_Boss->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Boss", pAtlas, Vec2(0, 0), Vec2(154, 41), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\Boss.txt");
	pAnimator->Play(L"Boss", true);
	AddObject(STAGE, m_Boss);
	m_vecStageObjects[(UINT)StageObj::Boss] = m_Boss;


	m_Stage = new CCharacter;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Stage", L"texture\\Stage.png");
	pAnimator = m_Stage->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Stage", pAtlas, Vec2(0, 0), Vec2(186, 59), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\Stage.txt");
	pAnimator->Play(L"Stage", true);
	AddObject(STAGE, m_Stage);
	m_vecStageObjects[(UINT)StageObj::Stage] = m_Stage;


	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Noise", L"texture\\Noise.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->LoadAnimation(L"animdata\\Noise.txt");
	pAnimator->Play(L"Noise", true);
	pBG->SetScale({ 310, 198 });
	AddObject(STAGE, pBG);
	m_vecStageObjects[(UINT)StageObj::Noise] = pBG;


	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Glitch", L"texture\\Glitch.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	/*pAnimator->CreateAnimation(L"Glitch", pAtlas, Vec2(0, 0), Vec2(400, 200), Vec2(0, 0), 0.03f, 2);
	pAnimator->SaveAnimation(L"animdata");*/
	pAnimator->LoadAnimation(L"animdata\\Glitch.txt");
	pAnimator->Play(L"Glitch", true);
	pBG->SetScale({ 310, 198 });
	AddObject(STAGE, pBG);
	m_vecStageObjects[(UINT)StageObj::Glitch] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"StageHospital", L"texture\\BG.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"StageHospital", pAtlas, Vec2(0, 0), Vec2(510, 148), Vec2(0, 0), 0.03f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\BG.txt");
	pAnimator->Play(L"StageHospital", true);
	pBG->SetScale({ 310, 198 });
	AddObject(BACKGROUND, pBG);
	m_vecStageObjects[(UINT)StageObj::Hospital] = pBG;

	m_Hand = new CCharacter;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"HandAtlas", L"texture\\Hand.png");
	float height = (float)pAtlas->GetHeight();
	m_Hand->SetScale({ 300, 42 });
	pAnimator = m_Hand->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Hand", pAtlas, Vec2(0, 0), Vec2(307, 42), Vec2(0, 0), 0.1f, 3);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\Hand.txt");
	pAnimator->Play(L"Hand", false);
	AddObject(HAND, m_Hand);
	m_vecStageObjects[(UINT)StageObj::Hand] = m_Hand;

	CThermometer* bossHealth = new CThermometer;
	bossHealth->SetScale({ 256, 14 });
	AddObject(STAGE, bossHealth);
	m_vecStageObjects[(UINT)StageObj::Thermometer] = bossHealth;

	CCharacter* ScriptBox = new CCharacter;
	pAnimator = ScriptBox->GetComponent<CAnimator>();
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ScriptBox", L"texture\\ScriptBox.png");
	pAnimator->CreateAnimation(L"ScriptBox", pAtlas, Vec2(0, 0), Vec2(98, 21), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ScriptBox", false);
	ScriptBox->SetScale({ 560 , 100 });
	ScriptBox->SetAlpha(200);
	AddObject(STAGE, ScriptBox);
	m_vecStageObjects[(UINT)StageObj::ScriptBox] = ScriptBox;

	CCharacter* Ian = new CCharacter;
	pAnimator = Ian->GetComponent<CAnimator>();
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"IanAtlas", L"texture\\Ian.png");
	pAnimator->CreateAnimation(L"IanIdle", pAtlas, Vec2(64, 36), Vec2(32, 30), Vec2(0, 0), 0.15f, 3);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"IanIdle", true);
	Ian->SetScale({ 120, 110 });
	AddObject(STAGE, Ian);
	m_vecStageObjects[(UINT)StageObj::Ian] = Ian;


	CCharacter* wait = new CCharacter;
	pAnimator = wait->GetComponent<CAnimator>();
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Wait", L"texture\\wait.png");
	/*pAnimator->CreateAnimation(L"wait", pAtlas, Vec2(0, 0), Vec2(322, 48), Vec2(0, 0), 0.15f, 1);
	pAnimator->SaveAnimation(L"animdata");*/
	pAnimator->LoadAnimation(L"animdata\\Wait.txt");
	pAnimator->Play(L"Wait", false);
	wait->SetScale({ 30, 4 });

	AddObject(STAGE, wait);
	m_vecStageObjects[(UINT)StageObj::wait] = wait;


	CCharacter* ending = new CCharacter;
	pAnimator = ending->GetComponent<CAnimator>();
	/*pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Ending", L"texture\\Ending.png");
	pAnimator->CreateAnimation(L"Ending", pAtlas, Vec2(0, 0), Vec2(401, 262), Vec2(0, 0), 0.15f, 1);
	pAnimator->SaveAnimation(L"animdata");*/
	pAnimator->LoadAnimation(L"animdata\\Ending.txt");
	pAnimator->Play(L"Ending", false);



	AddObject(STAGE, ending);
	m_vecStageObjects[(UINT)StageObj::Ending] = ending;

	CWindowEvent* newEvent = new CWindowEvent;
	CEventMgr::GetInst()->RegistWindowEvent(newEvent);

	CBeatNote* newNote = new CBeatNote;
	CEventMgr::GetInst()->RegistNoteEvent(newNote);
	newNote = new CBeatNote;
	CEventMgr::GetInst()->RegistNoteEvent(newNote);

	CObjEvent* objEvent = new CObjEvent;
	CEventMgr::GetInst()->RegistObjEvent(objEvent);


	m_PausePhone = new CPausePhone;

	AddObject(HAND, m_PausePhone);

}

void CStagePlayLevel::enter()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	m_BGSound = CAssetMgr::GetInst()->LoadSound(L"BGM_allthetimes", L"sound\\sndAllTheTimes.wav");

	CWindowEvent* event = CEventMgr::GetInst()->GetWindowEvent();

	event->SetPos(event->GetMonitorRes() / 2 - event->GetWinRes() / 2);

	dynamic_cast<CUnitBar*>(m_vecStageObjects[(UINT)StageObj::Bar])->HideAll();
	dynamic_cast<CUnitBar*>(m_vecStageObjects[(UINT)StageObj::TingBar])->HideAll();

	CEventMgr::GetInst()->GetWindowEvent()->LoadEventData(L"Test.txt", m_listWinInfo);
	CEventMgr::GetInst()->GetObjEvent()->LoadEventData(L"TestObj.txt", m_listObjInfo);
	MakeNotes();
	m_AccTime = 0;
	m_bAnyPressed = false;
	m_Paused = false;

#pragma region 초기 위치 설정

	Vec2 vRes = CEngine::GetInst()->GetResolution();

	m_vecStageObjects[(UINT)StageObj::TingBG]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f + 77.f }, 0);
	m_vecStageObjects[(UINT)StageObj::TingBGOpen]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f + 77.f }, 0);
	m_vecStageObjects[(UINT)StageObj::ColeBGBack]->SetMove({ vRes.x / 2.f, vRes.y / 2.f - 55.f - 400.f }, 0);
	m_vecStageObjects[(UINT)StageObj::ColeBGFront]->SetMove({ vRes.x / 2.f, vRes.y / 2.f + 77.f - 400.f }, 0);
	m_vecStageObjects[(UINT)StageObj::BlueSky]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f }, 0);
	m_vecStageObjects[(UINT)StageObj::BVeil]->SetMove({ vRes.x / 2.f, vRes.y + 360.f }, 0);
	m_vecStageObjects[(UINT)StageObj::MVeil]->SetMove({ vRes.x / 2.f, vRes.y - 100.f }, 0);
	m_vecStageObjects[(UINT)StageObj::MVeil]->SetScaleMove({ vRes.x, 50.f }, 0);
	m_vecStageObjects[(UINT)StageObj::TVeil]->SetMove({ vRes.x / 2.f, vRes.y - 100.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Ting]->SetMove({ vRes.x / 2.f - 370.f, vRes.y / 2.f - 1000.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Cole]->SetMove({ vRes.x / 2.f - 1150.f, vRes.y / 2.f - 1120.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Cole]->GetComponent<CAnimator>()->Play(L"Idle", true);
	m_vecStageObjects[(UINT)StageObj::Stage]->SetMove({ vRes.x / 2.f + 470.f, vRes.y / 2.f + 13.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Boss]->SetMove({ vRes.x / 2.f - 485.f, vRes.y / 2.f - 50.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Noise]->SetMove({ vRes.x / 2.f - 10000.f, vRes.y / 2.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Glitch]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Hospital]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Hand]->SetMove({ vRes.x / 2.f + 100.f, 358.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Thermometer]->SetMove({ vRes.x / 2.f - 70.f, vRes.y - 470.f }, 0);
	m_vecStageObjects[(UINT)StageObj::ScriptBox]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f + 120.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Ian]->SetMove({ vRes.x / 2.f - 1260.f, vRes.y / 2.f + 93.f }, 0);
	m_vecStageObjects[(UINT)StageObj::wait]->SetMove({ vRes.x / 2.f - 1020.f, vRes.y / 2.f + 100.f }, 0);
	m_vecStageObjects[(UINT)StageObj::Ending]->SetMove({ vRes.x / 2.f - 1000.f, vRes.y / 2.f }, 0);
	m_PausePhone->SetMove({ vRes.x / 2.f, 500.f }, 0);
	m_curTime = 0;

#pragma endregion

	audioDelay = m_PausePhone->GetAudioDelay();
	m_NoteJudgeTimeOffset = m_PausePhone->GetJudgeOffset();

	CEngine::GetInst()->SetDrawResolution({ 704, 396 });
	CEventMgr::GetInst()->SetStop(false);
	CEventMgr::GetInst()->GetWindowEvent()->SetMode(WindowEventType::END);
}

void CStagePlayLevel::exit()
{
	m_Paused = false;
	m_listWinInfo.clear();
	m_listObjInfo.clear();
	m_listNoteInfo.clear();
	m_PausePhone->Close();
	CEngine::GetInst()->SetDrawResolution({ 1600, 900 });
	CEngine::GetInst()->ChangeWindowSize({ 1600, 900 }, false);
	CEventMgr::GetInst()->SetStop(true);
}

void CStagePlayLevel::tick()
{
	if (Pause()) {
		if (KEY_TAP(C)) {
			OpenCreateWindow();
		}
		if (KEY_TAP(UP)) {
			m_PausePhone->CursorUp();
		}
		if (KEY_TAP(DOWN)) {
			m_PausePhone->CursorDown();
		}
		if (KEY_TAP(ENTER)) {
			int res = m_PausePhone->Enter();
			if (res == (UINT)PauseBtn::Continue) {
				m_Paused = false;
				m_BGSound->StopPlay();
				CEventMgr::GetInst()->SetStop(false);
				m_PausePhone->Close();
			}
			if (res == (UINT)PauseBtn::Replay) {
				exit();
				enter();
			}
			if (res == (UINT)PauseBtn::Quit) {

				ChangeLevel(LEVEL_TYPE::STAGE_SELECT_LEVEL);
			}
		}
		if (KEY_TAP(RIGHT)) {
			m_PausePhone->Right();
			audioDelay = m_PausePhone->GetAudioDelay();
			m_NoteJudgeTimeOffset = m_PausePhone->GetJudgeOffset();
		}
		if (KEY_TAP(LEFT)) {
			m_PausePhone->Left();
			audioDelay = m_PausePhone->GetAudioDelay();
			m_NoteJudgeTimeOffset = m_PausePhone->GetJudgeOffset();
		}
		return;
	}

	if (219.f <= m_AccTime) {
		if (CKeyMgr::GetInst()->IsAnyKeyTap()) {
			CLevelMgr::GetInst()->SetClear(true);
			::ChangeLevel(LEVEL_TYPE::STAGE_SELECT_LEVEL);
		}
		else {
			return;
		}
	}

	CLevel::tick();

	if (!m_bAnyPressed) {
		AnyPress();
	}

	else {
		if (KEY_TAP(C)) {
			m_bCorrectMode = !m_bCorrectMode;
		}

		auto newEvent = CEventMgr::GetInst()->GetWindowEvent();

		m_AccTime += DT;
		CLogMgr::GetInst()->SetAccTime(m_AccTime);

		// 노트 이벤트 처리
		if (!m_listNoteInfo.empty()) {
			NoteInfo noteinfo = m_listNoteInfo.front();

			if (noteinfo.StartTime <= m_AccTime + audioDelay) {

				CUnitBar* bar = m_vecBars[(UINT)noteinfo.Bar];
				auto newNoteEvent = dynamic_cast<CBeatNote*>(CEventMgr::GetInst()->GetNoteEvents()[(UINT)noteinfo.Bar]);
				newNoteEvent->SetBar(bar);
				newNoteEvent->SetBeatSpeed(noteinfo.Speed);
				newNoteEvent->SetLoopCount(noteinfo.Cnt);
				newNoteEvent->SetLoopDuration(noteinfo.GetDuration);
				newNoteEvent->Play();
				m_listNoteInfo.pop_front();
				CCamera::GetInst()->Zoom(20.f, 0.2f);

				m_NoteJudgeTime = noteinfo.StartTime + noteinfo.JudgeTime - audioDelay;
				m_newNote = true;

			}
		}

		// 오브젝트 이벤트 처리
		if (!m_listObjInfo.empty()) {
			ObjInfo objinfo = m_listObjInfo.front();
			if (objinfo.StartTime <= m_AccTime + audioDelay) {
				switch (objinfo.Type)
				{
				case ObjEventType::Moving:
					if (objinfo.Obj == StageObj::ColeBGFront) {
						m_vecStageObjects[(UINT)StageObj::ColeBGFront]->SetMove({ objinfo.Pos.x - 0.f, objinfo.Pos.y }, objinfo.Speed);
						m_vecStageObjects[(UINT)StageObj::ColeBGBack]->SetMove({ objinfo.Pos.x - 0.f, objinfo.Pos.y - 132.f }, objinfo.Speed);
					}
					else if (objinfo.Obj == StageObj::Bar) {
						m_vecBars[(UINT)BarType::Cole]->SetPosAll(objinfo.Pos);
					}
					else if (objinfo.Obj == StageObj::TingBar) {
						m_vecBars[(UINT)BarType::Ting]->SetPosAll(objinfo.Pos);
					}
					else {
						m_vecStageObjects[(UINT)objinfo.Obj]->SetMove(objinfo.Pos, objinfo.Speed);
					}
					break;
				case ObjEventType::Scale:
					m_vecStageObjects[(UINT)objinfo.Obj]->SetScaleMove(objinfo.Scale, objinfo.Speed);
					break;
				case ObjEventType::BarMoving:
					if (objinfo.Speed == 0) {
						m_vecBars[(UINT)BarType::Cole]->SetMoving(false);
					}
					else {
						m_vecBars[(UINT)BarType::Cole]->SetMoving(true);
						m_vecBars[(UINT)BarType::Cole]->SetMovingSpeed(objinfo.Speed);
						m_vecBars[(UINT)BarType::Cole]->SetMovingDuration(objinfo.Duration);
					}
					break;

				case ObjEventType::Show:
					if (objinfo.Obj == StageObj::Bar) {
						if (objinfo.Show) {
							m_vecBars[(UINT)BarType::Cole]->ShowAll();
						}
						else {
							m_vecBars[(UINT)BarType::Cole]->HideAll();
						}
					}
					else if (objinfo.Obj == StageObj::TingBar) {
						if (objinfo.Show) {
							m_vecBars[(UINT)BarType::Ting]->ShowAll();
						}
						else {
							m_vecBars[(UINT)BarType::Ting]->HideAll();
						}
					}
					break;

				case ObjEventType::Animation:
					if (objinfo.Obj == StageObj::Bar) {
						m_vecBars[(UINT)BarType::Cole]->SetAnimation(objinfo.Str, objinfo.Duration);
					}
					else {
						m_vecStageObjects[(UINT)objinfo.Obj]->GetComponent<CAnimator>()->Play(objinfo.Str, objinfo.Duration);
					}
					break;

				case ObjEventType::BlinkOut:
					CCamera::GetInst()->BlinkOut(objinfo.Duration);
					break;

				case ObjEventType::BlinkIn:
					CCamera::GetInst()->BlinkIn(objinfo.Duration);
					break;

				case ObjEventType::FadeOut:
					CCamera::GetInst()->FadeOut(objinfo.Duration);
					break;

				case ObjEventType::FadeIn:
					CCamera::GetInst()->FadeIn(objinfo.Duration);
					break;

				case ObjEventType::END:
					break;

				default:
					break;
				}
				m_listObjInfo.pop_front();
			}
		}

		// 윈도우 이벤트 처리
		if (!m_listWinInfo.empty()) {
			WinInfo info = m_listWinInfo.front();
			if (info.StartTime <= m_AccTime + audioDelay) {
				switch (info.Type)
				{
				case WindowEventType::LinearMove:
					newEvent->SetMode(info.Type);
					newEvent->SetTarget(info.Target, info.Speed);
					newEvent->SetFlash(info.Flash);
					break;
				case WindowEventType::CircleMove:
					newEvent->SetMode(info.Type);
					if (info.Theta != -5) {
						newEvent->SetTheta(info.Theta);
					}
					newEvent->SetSpeed(info.Speed);
					newEvent->SetRadius(info.Radius);
					newEvent->SetCW(info.CW);
					if (info.Decrease != 0) {
						newEvent->SetDecreaseSpeed(info.Decrease);
					}
					break;

				case WindowEventType::Quake:
					newEvent->SetFlash(info.Flash);
					newEvent->SetMode(info.Type);
					newEvent->SetQuakeAmount((int)info.QuakeAmount);
					break;

				case WindowEventType::UpAndDown:
					newEvent->SetMode(info.Type);
					newEvent->SetTarget(info.Target, 0.05f);
					newEvent->SetUpDownSize(info.Size);
					newEvent->SetUpDownCount((int)info.Count);
					break;

				case WindowEventType::Jumping:
					newEvent->SetMode(info.Type);
					newEvent->SetJumpingSize(info.Size);
					newEvent->SetJumpingSpeed(info.Speed);
					break;

				case WindowEventType::Disapear:
					newEvent->SetDisappearSpeed(info.Speed);
					newEvent->SetMode(info.Type);
					newEvent->SetDisappearDistance(info.Size);
					newEvent->SetDisappearDuration(info.Duration);
					break;

				case WindowEventType::Wave:
					newEvent->SetMode(info.Type);
					newEvent->SetWaveSpeed(info.Speed);
					newEvent->SetWaveFrequency(info.Duration);
					newEvent->SetWaveSize(info.Size);
					newEvent->SetWavePersist(info.CW);
					break;

				case WindowEventType::PortalMove:
					newEvent->SetMode(info.Type);
					newEvent->SetPortalDirection(info.Target);
					newEvent->SetSpeed(info.Speed);
					break;

				case WindowEventType::END:
					break;
				default:
					break;
				}
				m_listWinInfo.pop_front();
			}
		}


		if (KEY_TAP(_4)) {
			SetMusic(10);
		}

		Judge();

		if (KEY_TAP(SPACE)) {
			m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
		}
	}
}

bool CStagePlayLevel::Pause()
{
	if (m_Paused) {
		if (KEY_TAP(ESC)) {
			m_Paused = false;
			m_BGSound->StopPlay();
			CEventMgr::GetInst()->SetStop(false);
			m_PausePhone->Close();
		}

		return true;
	}
	else {
		if (KEY_TAP(ESC)) {
			m_Paused = true;
			m_BGSound->Stop();
			CEventMgr::GetInst()->SetStop(true);
			m_PausePhone->Open();
		}
	}

	return false;
}

void CStagePlayLevel::SetMusic(float _time)
{
	m_curTime += _time;
	m_AccTime = m_curTime;
	m_BGSound->SetPosition(m_curTime * 100 / 230.7f);
}

void CStagePlayLevel::AnyPress()
{
	if (KEY_TAP(SPACE)) {
		m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
		m_BGSound->Play();
		m_vecBars[(UINT)BarType::Cole]->Start(true);
		m_vecBars[(UINT)BarType::Ting]->Start(true);
		m_bAnyPressed = true;
	}
	return;

}

void CStagePlayLevel::Judge()
{
	if (m_NoteJudgeTime - JudgeTime + m_NoteJudgeTimeOffset <= m_AccTime + m_NoteJudgeTimeOffset
		&& m_AccTime + m_NoteJudgeTimeOffset < m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE) && m_newNote && !m_bCorrectMode) {
			m_newNote = false;
			m_vecBars[(UINT)BarType::Cole]->Incorrect(JudgeBeatType::Left);
			m_vecBars[(UINT)BarType::Ting]->Incorrect(JudgeBeatType::Left);
		}
	}
	else if (m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset <= m_AccTime + m_NoteJudgeTimeOffset
		&& m_AccTime + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset) {
		if ((KEY_TAP(SPACE) && m_newNote) || m_bCorrectMode) {
			m_newNote = false;
			CCamera::GetInst()->Judge(0.3f);
			m_vecBars[(UINT)BarType::Cole]->Correct();
			m_vecBars[(UINT)BarType::Ting]->Correct();

		}
	}
	else if (m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset < m_AccTime + m_NoteJudgeTimeOffset
		&& m_AccTime + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE) && m_newNote) {
			m_newNote = false;
			m_vecBars[(UINT)BarType::Cole]->Incorrect(JudgeBeatType::Right);
			m_vecBars[(UINT)BarType::Ting]->Incorrect(JudgeBeatType::Right);
		}
	}
	else if (m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset < m_AccTime + m_NoteJudgeTimeOffset) {
		if (m_newNote) {
			m_newNote = false;
			m_vecBars[(UINT)BarType::Cole]->Incorrect(JudgeBeatType::Miss);
			m_vecBars[(UINT)BarType::Ting]->Incorrect(JudgeBeatType::Miss);

		}
	}
}

void CStagePlayLevel::MakeNotes()
{
	for (int i = 0; i < 48; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 13.7f + i * 1.657f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.4f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 4; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Ting;
		noteinfo.StartTime = 94.8f + i * 1.657f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.4f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 4; i < 8; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 94.8f + i * 1.657f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.4f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 8; i < 16; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 94.8f + i * 1.657f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.4f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);

		NoteInfo noteinfo2 = {};
		noteinfo2.Bar = BarType::Ting;
		noteinfo2.StartTime = 94.8f + i * 1.657f;
		noteinfo2.Speed = 400.f;
		noteinfo2.GetDuration = 0.4f;
		noteinfo2.Cnt = 1;
		noteinfo2.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo2);
	}

	for (int i = 16; i < 32; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 94.8f + i * 1.657f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.4f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 12; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 160.8f + i * 0.828f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.3f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.55f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 8; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 170.8f + i * 0.414f;
		noteinfo.Speed = 800.f;
		noteinfo.GetDuration = 0.1f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.25f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 19; i++) {
		NoteInfo noteinfo = {};
		noteinfo.Bar = BarType::Cole;
		noteinfo.StartTime = 170.9f + i * 1.657f;
		noteinfo.Speed = 400.f;
		noteinfo.GetDuration = 0.4f;
		noteinfo.Cnt = 1;
		noteinfo.JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	NoteInfo noteinfo = {};
	noteinfo.Bar = BarType::Cole;
	noteinfo.StartTime = 201.9f;
	noteinfo.Speed = 400.f;
	noteinfo.GetDuration = 1.7f;
	noteinfo.Cnt = 1;
	noteinfo.JudgeTime = 2.0f;
	m_listNoteInfo.push_back(noteinfo);

}


INT_PTR CALLBACK CreateWindowEventProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CStagePlayLevel::OpenCreateWindow()
{
	DialogBox(nullptr, MAKEINTRESOURCE(IDD_WND_EVENT), CEngine::GetInst()->GetMainWind(), CreateWindowEventProc);
}

INT_PTR CALLBACK CreateWindowEventProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	auto hComboBox = GetDlgItem(hDlg, IDC_WND_TYPE);
	auto hFlash = GetDlgItem(hDlg, IDC_WND_FLASH);
	auto hCW = GetDlgItem(hDlg, IDC_WND_CW);
	auto hStartTime = GetDlgItem(hDlg, IDC_STARTTIME);
	
	switch (message) {
	case WM_INITDIALOG:
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::LinearMove, (LPARAM)L"LinearMove");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::CircleMove, (LPARAM)L"CircleMove");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::Quake, (LPARAM)L"Quake");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::UpAndDown, (LPARAM)L"UpAndDown");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::Jumping, (LPARAM)L"Jumping");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::Disapear, (LPARAM)L"Disapear");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::Wave, (LPARAM)L"Wave");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::PortalMove, (LPARAM)L"PortalMove");
		SendMessage(hComboBox, CB_ADDSTRING, (UINT)WindowEventType::END, (LPARAM)L"END");
		SendMessage(hFlash, CB_ADDSTRING, 0, (LPARAM)L"True");
		SendMessage(hFlash, CB_ADDSTRING, 1, (LPARAM)L"False");
		SendMessage(hCW, CB_ADDSTRING, 0, (LPARAM)L"True");
		SendMessage(hCW, CB_ADDSTRING, 1, (LPARAM)L"False");

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			wstring strFilePath = CPathMgr::GetContentPath();
			strFilePath += L"eventdata\\Test.txt" ;
			std::ofstream outputFile(strFilePath, std::ios::app);
			wchar_t what[256] = {};

			int Idx;
			Idx = (int)SendMessage((HWND)hComboBox, CB_GETCURSEL, 0, 0);

			GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);

			int flash;
			flash= (int)SendMessage((HWND)hFlash, CB_GETCURSEL, 0, 0);

			int cw;
			cw = (int)SendMessage((HWND)hCW, CB_GETCURSEL, 0, 0);


			switch ((WindowEventType)Idx)
			{
			case WindowEventType::LinearMove:
				outputFile << "[LINEAR_MOVE]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::LinearMove << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[TARGET]" << std::endl;
				GetDlgItemText(hDlg, IDC_TARGET_X, what, 256);
				outputFile << _wtof(what);
				outputFile << " ";
				GetDlgItemText(hDlg, IDC_TARGET_Y, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[FLASH]" << std::endl;
				outputFile << flash << std::endl;
				break;

			case WindowEventType::CircleMove:
				outputFile << "[CIRCLE_MOVE]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::CircleMove << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[THETA]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_THETA, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[RADIUS]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_RADIUS, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[CW]" << std::endl;
				outputFile << cw << std::endl;
				outputFile << "[DECREASE]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_DEC, what, 256);
				outputFile << _wtof(what) << std::endl;
				break;

			case WindowEventType::Quake:
				outputFile << "[QUAKE_MOVE]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::Quake << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[QUAKE_AMOUNT]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_QUAKE, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[FLASH]" << std::endl;
				outputFile << flash << std::endl;
				break;

			case WindowEventType::UpAndDown:
				outputFile << "[UP_DOWN]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::UpAndDown << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[TARGET]" << std::endl;
				GetDlgItemText(hDlg, IDC_TARGET_X, what, 256);
				outputFile << _wtof(what);
				outputFile << " ";
				GetDlgItemText(hDlg, IDC_TARGET_Y, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SIZE]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SIZE, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[COUNT]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_COUNT, what, 256);
				outputFile << _wtof(what) << std::endl;
				break;

			case WindowEventType::Jumping:
				outputFile << "[JUMPING]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::Jumping<< std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SIZE]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SIZE, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				break;

			case WindowEventType::Disapear:
				outputFile << "[DISAPPEAR]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::Disapear << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SIZE]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SIZE, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[DURATION]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_DURATION, what, 256);
				outputFile << _wtof(what) << std::endl;
				break;

			case WindowEventType::Wave:
				outputFile << "[WAVE]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::Wave << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SIZE]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SIZE, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[DURATION]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_DURATION, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[PERSIST]" << std::endl;
				outputFile << cw << std::endl;
				break;

			case WindowEventType::PortalMove:
				outputFile << "[PORTAL]" << std::endl;
				outputFile << "[TYPE]" << std::endl;
				outputFile << (UINT)WindowEventType::PortalMove << std::endl;
				outputFile << "[START_TIME]" << std::endl;
				GetDlgItemText(hDlg, IDC_STARTTIME, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[TARGET]" << std::endl;
				GetDlgItemText(hDlg, IDC_TARGET_X, what, 256);
				outputFile << _wtof(what);
				outputFile << " ";
				GetDlgItemText(hDlg, IDC_TARGET_Y, what, 256);
				outputFile << _wtof(what) << std::endl;
				outputFile << "[SPEED]" << std::endl;
				GetDlgItemText(hDlg, IDC_WND_SPEED, what, 256);
				outputFile << _wtof(what) << std::endl;
				break;

			case WindowEventType::END:
				break;
			default:
				break;
			}
			
			outputFile << std::endl;
			outputFile.close(); // 파일을 닫습니다.
			



			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
