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
	m_vecStageObjects.resize((UINT)StageObj::END);

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingBG", L"texture\\TingBG.png");
	pBG->SetPos({ vRes.x / 2.f - 1000.f, vRes.y / 2.f + 77.f });
	pBG->SetScale({ pAtlas->GetWidth() + 8, pAtlas->GetHeight() + 2 });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::Ting] = pBG;
	m_vecStageObjects[(UINT)StageObj::TingBG] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingBGOpen", L"texture\\TingBGOpen.png");
	pBG->SetPos({ vRes.x / 2.f - 1000.f, vRes.y / 2.f + 77.f });
	pBG->SetScale({ pAtlas->GetWidth() + 8, pAtlas->GetHeight() + 2 });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::TingOpen] = pBG;
	m_vecStageObjects[(UINT)StageObj::TingBGOpen] = pBG;

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
	m_vecStageObjects[(UINT)StageObj::ColeBGBack] = pBG;
	
	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeBG", L"texture\\ColeBG.png");
	//pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f + 77.f });
	pBG->SetPos({ vRes.x / 2.f, vRes.y / 2.f + 77.f - 400.f});
	pBG->SetScale({ pAtlas->GetWidth(), pAtlas->GetHeight() });
	pBG->SetTexture(pAtlas);
	AddObject(BACKGROUND, pBG);
	
	m_vecBackGrounds[(UINT)BackgroundIndex::ColeFront] = pBG;
	m_vecStageObjects[(UINT)StageObj::ColeBGFront	] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"blueskyPixel", L"texture\\blueskyPixel.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"blueskyPixel", pAtlas, Vec2(0, 0), Vec2(4, 4), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"blueskyPixel", true);
	pBG->SetPos({ vRes.x / 2.f -1000.f, vRes.y / 2.f });
	pBG->SetScale({ 720, 398 });
	AddObject(BACKGROUND, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::BlueSky] = pBG;
	m_vecStageObjects[(UINT)StageObj::BlueSky] = pBG;

	for (int i = 0; i < 3; i++) {
		pBG = new CBackground;
		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"blackPixel", L"texture\\blackPixel.png");
		pBG->SetScale({ vRes .x, 50.f});
		pBG->SetTexture(pAtlas);
		AddObject(STAGE, pBG);
		m_vecBackGrounds[(UINT)BackgroundIndex::BVeil + i] = pBG;
		m_vecStageObjects[(UINT)StageObj::BVeil + i] = pBG;
	}
	m_vecBackGrounds[(UINT)BackgroundIndex::BVeil] ->SetPos({ vRes.x / 2.f, vRes.y + 360.f});
	m_vecBackGrounds[(UINT)BackgroundIndex::MVeil]->SetPos({ vRes.x / 2.f, vRes.y - 100.f});
	m_vecBackGrounds[(UINT)BackgroundIndex::TVeil]->SetPos({ vRes.x / 2.f, vRes.y - 100.f});


	m_UnitBar = new CUnitBar;
	AddObject(PLAYER, m_UnitBar);
	m_vecStageObjects[(UINT)StageObj::Bar] = m_UnitBar;
	

	m_Ting = new CCharacter;
	m_Ting->SetPos({ vRes.x / 2.f - 370.f, vRes.y / 2.f -1000.f});
	m_Ting->SetScale({ 40, 40 });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"TingAtlas", L"texture\\Ting.png");
	pAnimator = m_Ting->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Ting", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.1f, 6);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\Ting.txt");
	pAnimator->Play(L"Ting", true);
	AddObject(PLAYER, m_Ting);
	m_vecStageObjects[(UINT)StageObj::Ting] = m_Ting;

	m_Cole = new CCharacter;
	m_Cole->SetPos({ vRes.x / 2.f - 1150.f, vRes.y / 2.f  - 1120.f});
	m_Cole->SetScale({ 40, 40 });
	//pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeAtlas", L"texture\\Cole.png");
	pAnimator = m_Cole->GetComponent<CAnimator>();
	//pAnimator->CreateAnimation(L"Ting", pAtlas, Vec2(0, 0), Vec2(40, 40), Vec2(0, 0), 0.1f, 6);
	//pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\ColeIdle.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeRun.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeTired.txt");
	pAnimator->LoadAnimation(L"animdata\\ColeLookUp.txt");
	pAnimator->Play(L"ColeIdle", true);
	AddObject(PLAYER, m_Cole);
	m_vecStageObjects[(UINT)StageObj::Cole] = m_Cole;

	m_Boss = new CCharacter;
	m_Boss->SetPos({ vRes.x / 2.f - 485.f, vRes.y / 2.f - 50.f });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Boss", L"texture\\Boss.png");
	pAnimator = m_Boss->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Boss", pAtlas, Vec2(0, 0), Vec2(154, 41), Vec2(0, 0), 0.1f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\Boss.txt");
	pAnimator->Play(L"Boss", true);
	AddObject(STAGE, m_Boss);
	m_vecStageObjects[(UINT)StageObj::Boss] = m_Boss;

	m_Stage = new CCharacter;
	m_Stage->SetPos({ vRes.x / 2.f + 470.f, vRes.y / 2.f + 13.f });
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
	pBG->SetPos({ vRes.x / 2.f - 10000.f, vRes.y / 2.f });
	pBG->SetScale({ 310, 198 });
	AddObject(STAGE, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::Noise] = pBG;
	m_vecStageObjects[(UINT)StageObj::Noise] = pBG;


	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Glitch", L"texture\\Glitch.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	/*pAnimator->CreateAnimation(L"Glitch", pAtlas, Vec2(0, 0), Vec2(400, 200), Vec2(0, 0), 0.03f, 2);
	pAnimator->SaveAnimation(L"animdata");*/
	pAnimator->LoadAnimation(L"animdata\\Glitch.txt");
	pAnimator->Play(L"Glitch", true);
	pBG->SetPos({ vRes.x / 2.f - 1000.f, vRes.y / 2.f });
	pBG->SetScale({ 310, 198 });
	AddObject(STAGE, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::Glitch] = pBG;
	m_vecStageObjects[(UINT)StageObj::Glitch] = pBG;

	pBG = new CBackground;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"StageHospital", L"texture\\BG.png");
	pAnimator = pBG->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"StageHospital", pAtlas, Vec2(0, 0), Vec2(510, 148), Vec2(0, 0), 0.03f, 1);
	pAnimator->SaveAnimation(L"animdata");
	//pAnimator->LoadAnimation(L"animdata\\BG.txt");
	pAnimator->Play(L"StageHospital", true);
	pBG->SetPos({ vRes.x / 2.f  -1000.f, vRes.y / 2.f });
	pBG->SetScale({ 310, 198 });
	AddObject(BACKGROUND, pBG);

	m_vecBackGrounds[(UINT)BackgroundIndex::Hospital] = pBG;
	m_vecStageObjects[(UINT)StageObj::Hospital] = pBG;

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
	AddObject(HAND, m_Hand);
	m_vecStageObjects[(UINT)StageObj::Hand] = m_Hand;

	CWindowEvent* newEvent = new CWindowEvent;
	CEventMgr::GetInst()->RegistWindowEvent(newEvent);
	newEvent->LoadEventData(L"Test.txt", m_listWinInfo);

	CBeatNote* newNote = new CBeatNote;
	CEventMgr::GetInst()->RegistNoteEvent(newNote);

	CObjEvent* objEvent = new CObjEvent;
	objEvent->LoadEventData(L"TestObj.txt", m_listObjInfo);

	for (int i = 0; i < 48; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 13.7f + i *1.657f;
		noteinfo->Speed = 400.f;
		noteinfo->GetDuration = 0.4f;
		noteinfo->Cnt = 1;
		noteinfo->JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 4; i < 32; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 94.8f + i * 1.657f;
		noteinfo->Speed = 400.f;
		noteinfo->GetDuration = 0.4f;
		noteinfo->Cnt = 1;
		noteinfo->JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 12; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 160.8f + i * 0.828f;
		noteinfo->Speed = 400.f;
		noteinfo->GetDuration = 0.3f;
		noteinfo->Cnt = 1;
		noteinfo->JudgeTime = 0.55f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 8; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 170.8f + i * 0.414f;
		noteinfo->Speed = 800.f;
		noteinfo->GetDuration = 0.1f;
		noteinfo->Cnt = 1;
		noteinfo->JudgeTime = 0.25f;
		m_listNoteInfo.push_back(noteinfo);
	}

	for (int i = 0; i < 19; i++) {
		NoteInfo* noteinfo = new NoteInfo;
		noteinfo->Bar = L"bar";
		noteinfo->StartTime = 170.9f + i * 1.657f;
		noteinfo->Speed = 400.f;
		noteinfo->GetDuration = 0.4f;
		noteinfo->Cnt = 1;
		noteinfo->JudgeTime = 0.7f;
		m_listNoteInfo.push_back(noteinfo);
	}

	NoteInfo* noteinfo = new NoteInfo;
	noteinfo->Bar = L"bar";
	noteinfo->StartTime = 201.9f;
	noteinfo->Speed = 400.f;
	noteinfo->GetDuration = 1.7f;
	noteinfo->Cnt = 1;
	noteinfo->JudgeTime = 2.0f;
	m_listNoteInfo.push_back(noteinfo);



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

float audioDelay = 0.0f;

void CStagePlayLevel::tick()
{
	if (Pause()) {
		return;
	}

	CLevel::tick();

	if (!m_bAnyPressed) {
		AnyPress();
	}

	else {
		auto newEvent = CEventMgr::GetInst()->GetWindowEvent();
		auto newNoteEvent = dynamic_cast<CBeatNote*>(CEventMgr::GetInst()->GetNoteEvents()[0]);

		m_AccTime += DT;
		CLogMgr::GetInst()->SetAccTime(m_AccTime);

		// 노트 이벤트 처리
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

		// 오브젝트 이벤트 처리
		if (!m_listObjInfo.empty()) {
			ObjInfo objinfo = m_listObjInfo.front();
			if (objinfo.StartTime <= m_AccTime + audioDelay) {
				switch (objinfo.Type)
				{
				case ObjEventType::Moving:
					if (objinfo.Obj == StageObj::ColeBGFront) {
						m_vecStageObjects[(UINT)StageObj::ColeBGFront]->SetMove({ objinfo.Pos.x - 0.f, objinfo.Pos.y}, objinfo.Speed);
						m_vecStageObjects[(UINT)StageObj::ColeBGBack]->SetMove({ objinfo.Pos.x - 0.f, objinfo.Pos.y - 132.f }, objinfo.Speed);
					}
					else if (objinfo.Obj == StageObj::Bar) {
						m_UnitBar->SetPosAll(objinfo.Pos);
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
						m_UnitBar->SetMoving(false);
					}
					else {
						m_UnitBar->SetMoving(true);
						m_UnitBar->SetMovingSpeed(objinfo.Speed);
						m_UnitBar->SetMovingDuration(objinfo.Duration);
					}
					break;

				case ObjEventType::Show:
					if (objinfo.Obj == StageObj::Bar) {
						if (objinfo.Show) {
							m_UnitBar->ShowAll();
						}
						else {
							m_UnitBar->HideAll();
						}
					}
					break;

				case ObjEventType::Animation:
					if (objinfo.Obj == StageObj::Bar) {
						m_UnitBar->SetAnimation(objinfo.Str, objinfo.Duration);
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
		if (KEY_TAP(U)) {
			audioDelay -= 0.1f;
			wstring buffer = L"";
			buffer += L"오디오 딜레이: " + std::to_wstring(audioDelay);
			CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });
		}
		if (KEY_TAP(I)) {
			audioDelay += 0.1f;
			wstring buffer = L"";
			buffer += L"오디오 딜레이: " + std::to_wstring(audioDelay);
			CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });
		}

		if (KEY_TAP(O)) {
			m_NoteJudgeTimeOffset -= 0.016f;
			wstring buffer = L"";
			buffer += L"노트 판정 보정 Offset: " + std::to_wstring(m_NoteJudgeTimeOffset);
			CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });
		}
		if (KEY_TAP(P)) {
			m_NoteJudgeTimeOffset += 0.016f;
			wstring buffer = L""; 
			buffer += L"노트 판정 보정 Offset: " + std::to_wstring(m_NoteJudgeTimeOffset);
			CLogMgr::GetInst()->AddLog(FLog{ LOG_LEVEL::ERR, buffer });
		}
	}
}

bool CStagePlayLevel::Pause()
{
	if (m_Paused) {
		if (KEY_TAP(ESC)) {
			m_Paused = false;
			m_BGSound->StopPlay();
		}

		return true;
	}
	else {
		if (KEY_TAP(ESC)) {
			m_Paused = true;
			m_BGSound->Stop();
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
		if (KEY_TAP(SPACE)&& m_newNote) {
			m_newNote = false;
			m_UnitBar->Incorrect(JudgeBeatType::Left);
		}
	}
	else if (m_NoteJudgeTime - CorrectTime + m_NoteJudgeTimeOffset <= m_AccTime + audioDelay + m_NoteJudgeTimeOffset
		&& m_AccTime + audioDelay + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE) && m_newNote) {
			m_newNote = false;
			CCamera::GetInst()->Judge(0.1f);
			m_UnitBar->Correct();
		}
	}
	else if (m_NoteJudgeTime + CorrectTime + m_NoteJudgeTimeOffset < m_AccTime + audioDelay + m_NoteJudgeTimeOffset
		&& m_AccTime + audioDelay + m_NoteJudgeTimeOffset <= m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset) {
		if (KEY_TAP(SPACE) && m_newNote) {
			m_newNote = false;
			m_UnitBar->Incorrect(JudgeBeatType::Right);
		}
	}
	else if (m_NoteJudgeTime + JudgeTime + m_NoteJudgeTimeOffset < m_AccTime + audioDelay + m_NoteJudgeTimeOffset) {
		if (m_newNote) {
			m_newNote = false;
			m_UnitBar->Incorrect(JudgeBeatType::Miss);
		}
	}
}