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
#include "CObjEvent.h"


CStagePlayLevel::CStagePlayLevel(): 
	m_AccTime(0.f)
{
}

CStagePlayLevel::~CStagePlayLevel()
{
	for (auto iter = m_listNoteInfo.begin(); iter != m_listNoteInfo.end(); ++iter) {
		delete* iter;
	}
}

void CStagePlayLevel::init()
{
	CTexture* pAtlas;
	CAnimator* pAnimator;
	CBackground* pBG;
	Vec2 vRes = CEngine::GetInst()->GetResolution();

	m_vecBackGrounds.resize((UINT)BackgroundIndex::END);

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingBG", L"texture\\TingBG.png");
	pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f + 77.f });
	pBG->SetScale({ pAtlas->GetWidth() + 8, pAtlas->GetHeight() + 2 });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::Ting] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBGBG", L"texture\\ColeBGBG.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ColeBGBG", pAtlas, Vec2(0, 0), Vec2(352, 119), Vec2(0, 0), 0.1f, 3);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ColeBGBG", true);
	//pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f -55.f });
	pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f - 55.f - 400.f });
	pBG->SetScale({ 352, 119 });
	AddObject(BACKGROUND, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::ColeBack] = pBG;
	
	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBG", L"texture\\ColeBG.png");
	//pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f + 77.f });
	pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f + 77.f - 400.f});
	pBG->SetScale({ pAtlas->GetWidth(), pAtlas->GetHeight() });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);
	
	m_vecBackGrounds[(UINT)BackgroundIndex::ColeFront] = pBG;




	for (int i = 0; i < 3; i++) {
		pBG = new CBackground;
		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"blackPixel", L"texture\\blackPixel.png");
		pBG->SetScale({ vRes .x, 50.f});
		pBG->SetTexture(pAtlas);
		AddObject(STAGE, pBG);
		m_vecBackGrounds[(UINT)BackgroundIndex::BVeil + i] = pBG;
	}
	m_vecBackGrounds[(UINT)BackgroundIndex::BVeil] ->SetPos({ vRes.x / 2.f, vRes.y + 360.f});
	m_vecBackGrounds[(UINT)BackgroundIndex::MVeil]->SetPos({ vRes.x / 2.f, vRes.y - 100.f});
	m_vecBackGrounds[(UINT)BackgroundIndex::TVeil]->SetPos({ vRes.x / 2.f, vRes.y - 100.f});

	m_UnitBar = new CUnitBar;
	AddObject(PLAYER, m_UnitBar);
	

	m_Ting = new CCharacter;
	m_Ting->SetPos({ vRes.x / 2.f + 70.f, vRes.y / 2.f });
	m_Ting->SetScale({ 40, 40 });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingAtlas", L"texture\\Ting.png");
	pAnimator = m_Ting->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Ting", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.1f, 6);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\Ting.txt");
	pAnimator->Play(L"Ting", true);
	AddObject(PLAYER, m_Ting);

	m_Cole = new CCharacter;
	m_Cole->SetPos({ vRes.x / 2.f - 1150.f, vRes.y / 2.f  - 1120.f});
	m_Cole->SetScale({ 40, 40 });
	//pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeAtlas", L"texture\\Cole.png");
	pAnimator = m_Cole->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Ting", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.1f, 6);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\ColeIdle.txt");
	pAnimator->Play(L"ColeIdle", true);
	AddObject(PLAYER, m_Cole);

	m_Boss = new CCharacter;
	m_Boss->SetPos({ vRes.x / 2.f - 485.f, vRes.y / 2.f - 50.f });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Boss", L"texture\\Boss.png");
	pAnimator = m_Boss->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Boss", pAtlas, Vec2(0, 0), Vec2(154, 41), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\Boss.txt");
	pAnimator->Play(L"Boss", true);
	AddObject(STAGE, m_Boss);

	m_Stage = new CCharacter;
	m_Stage->SetPos({ vRes.x / 2.f + 470.f, vRes.y / 2.f + 13.f });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Stage", L"texture\\Stage.png");
	pAnimator = m_Stage->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Stage", pAtlas, Vec2(0, 0), Vec2(186, 59), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\Stage.txt");
	pAnimator->Play(L"Stage", true);
	AddObject(STAGE, m_Stage);


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
	newEvent->LoadEventData(L"Test.txt", m_listWinInfo);


	CBeatNote* newNote = new CBeatNote;
	CEventMgr::GetInst()->RegistNoteEvent(newNote);

	CObjEvent* objEvent = new CObjEvent;
	objEvent->LoadEventData(L"AllTheTimesObj.txt", m_listObjInfo);

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

	/*ObjInfo* barinfo = new ObjInfo;
	barinfo->Moving = true;
	barinfo->StartTime = 12.7f;
	barinfo->Speed = 40.f;
	barinfo->Duration = 0.5f;

	m_listObjInfo.push_back(barinfo);*/


	

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

	m_UnitBar->HideAll();
}


void CStagePlayLevel::exit()
{
}

float audioDelay = 0.f;

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
		CLogMgr::GetInst()->SetAccTime(m_AccTime);
		if (!m_listNoteInfo.empty()) {
			NoteInfo* noteinfo = m_listNoteInfo.front();
			if (noteinfo->StartTime <= m_AccTime + audioDelay) {
				newNoteEvent->SetBar(m_UnitBar);
				newNoteEvent->SetBeatSpeed(noteinfo->Speed);
				newNoteEvent->SetLoopCount(noteinfo->Cnt);
				newNoteEvent->SetLoopDuration(noteinfo->GetDuration);
				newNoteEvent->Play();
				m_listNoteInfo.pop_front();
				CCamera::GetInst()->Zoom(20.f, 0.2f);

				m_NoteJudgeTime = noteinfo->StartTime + noteinfo->JudgeTime + audioDelay;
				m_newNote = true;

				delete noteinfo;
			}
		}

		if (!m_listObjInfo.empty()) {
			ObjInfo objinfo = m_listObjInfo.front();
			if (objinfo.StartTime <= m_AccTime + audioDelay) {
				switch (objinfo.Type)
				{
				case StageObj::Hand:
					if (-1000.f <= objinfo.Pos.x) {
						m_Hand->SetMove(objinfo.Pos, objinfo.Speed);
					}
					break;

				case StageObj::Bar:
					/*[BAR]
						[TYPE]
						1
						[START_TIME]
						0
						[SPEED]
						40
						[DURATION]
						0.5*/
					if (objinfo.Speed == 0) {
						m_UnitBar->SetMoving(false);
					}
					else {
						m_UnitBar->SetMoving(true);
					}
					m_UnitBar->SetMovingSpeed(objinfo.Speed);
					m_UnitBar->SetMovingDuration(objinfo.Duration);
					break;
				case StageObj::Ting:
					m_Ting->SetMove(objinfo.Pos, objinfo.Speed);
					break;

				case StageObj::Cole:
					m_Cole->SetMove(objinfo.Pos, objinfo.Speed);
					
					break;
				case StageObj::BVeil:
					m_vecBackGrounds[(UINT)BackgroundIndex::BVeil]->SetMove(objinfo.Pos, objinfo.Speed); 
					break;	

				case StageObj::MVeil:
					m_vecBackGrounds[(UINT)BackgroundIndex::MVeil]->SetMove(objinfo.Pos, objinfo.Speed);
					m_vecBackGrounds[(UINT)BackgroundIndex::MVeil]->SetScaleMove(objinfo.Scale, objinfo.Speed);
					break;

				case StageObj::TVeil:
					m_vecBackGrounds[(UINT)BackgroundIndex::TVeil]->SetMove(objinfo.Pos, objinfo.Speed);
					break;

				case StageObj::TingBG:
					m_vecBackGrounds[(UINT)BackgroundIndex::Ting]->SetMove(objinfo.Pos, objinfo.Speed);
					break;

				case StageObj::ColeBG:
					m_vecBackGrounds[(UINT)BackgroundIndex::ColeFront]->SetMove(objinfo.Pos, objinfo.Speed);
					m_vecBackGrounds[(UINT)BackgroundIndex::ColeBack]->SetMove(objinfo.Pos - 132.f, objinfo.Speed);
					break;

				case StageObj::Boss:
					m_Boss->SetMove(objinfo.Pos, objinfo.Speed);
					break;

				case StageObj::Stage:
					m_Stage->SetMove(objinfo.Pos, objinfo.Speed);
					break;

				case StageObj::END:
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
					newEvent->SetQuakeAmount(info.QuakeAmount);
					break;

				case WindowEventType::UpAndDown:
					newEvent->SetMode(info.Type);
					newEvent->SetTarget(info.Target, 0.05f);
					newEvent->SetUpDownSize(info.Size);
					newEvent->SetUpDownCount(info.Count);
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

		if (KEY_TAP(_1)) {
			SetMusic(-60);
		}
		if (KEY_TAP(_2)) {
			SetMusic(60);
		}
		if (KEY_TAP(_3)) {
			SetMusic(-10);
		}
		if (KEY_TAP(_4)) {
			SetMusic(10);
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
	}
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
		m_BGSound->PlayToBGM(false);
		m_UnitBar->Start(true);
		m_bAnyPressed = true;
	}
	return;
	
}

void CStagePlayLevel::Judge()
{
	if (m_NoteJudgeTime - JudgeTime + m_NoteJudgeTimeOffset <= m_AccTime + audioDelay + m_NoteJudgeTimeOffset 
		&& m_AccTime + audioDelay + m_NoteJudgeTimeOffset < m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE)) {
			LOG(ERR, L"빠름");
			m_newNote = false;
			m_UnitBar->Incorrect(JudgeBeatType::Left);
		}
	}
	else if (m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset <= m_AccTime + audioDelay + m_NoteJudgeTimeOffset
		&& m_AccTime + audioDelay + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE)) {
			LOG(ERR, L"판정!");
			m_newNote = false;
			CCamera::GetInst()->Judge(0.1f);
			m_UnitBar->Correct();
		}
	}
	else if (m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset < m_AccTime + audioDelay + m_NoteJudgeTimeOffset
		&& m_AccTime + audioDelay + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE)) {
			LOG(ERR, L"느림");
			m_newNote = false;
			m_UnitBar->Incorrect(JudgeBeatType::Right);
		}
	}
	else if (m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset < m_AccTime + audioDelay + m_NoteJudgeTimeOffset) {
		if (m_newNote) {
			LOG(ERR, L"놓침");
			m_newNote = false;
			m_UnitBar->Incorrect(JudgeBeatType::Miss);
		}
	}
}