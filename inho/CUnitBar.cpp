#include "pch.h"
#include "CUnitBar.h"

#include "CEngine.h"
#include "CJudgeBar.h"
#include "CHeart.h"
#include "CCharacter.h"
#include "CNote.h"
#include "CNormalBeat.h"
#include "CGetSetBeat.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"

CUnitBar::CUnitBar()
{


}

CUnitBar::~CUnitBar()
{
}

void CUnitBar::begin()
{
	CJudgeBar* m_Judgebar = new CJudgeBar;
	Vec2 vRes = CEngine::GetInst()->GetResolution();
	Vec2 vBarScale = { 550, 1 };
	m_Judgebar->SetPos({ vRes.x / 2.f,vRes.y / 2.f });
	/*m_Judgebar->SetScale(vBarScale);
	AddObject(PLAYER, m_Judgebar);*/
	m_Judgebar->SetPos({ vRes.x / 2.f,vRes.y / 2.f });
	m_Judgebar->SetScale({ 3,1 });
	
	m_vecBars.push_back(m_Judgebar);

	for (int i = 1; i < 180; i++) {
		m_vecBars.push_back(m_Judgebar->Clone());
	}
	for (int i = 0; i < 180; i++) {
		m_vecBars[i]->SetPos({ vRes.x / 2.f - 270.f + 3.f * i,vRes.y / 2.f });

		CLevelMgr::GetInst()->GetCurLevel()->GetLayer((int)LAYER::PLAYER)->AddObject(m_vecBars[i]);
	}

	m_Heart = new CHeart;
	m_Heart->SetPos({ vRes.x / 2.f + 280.f, vRes.y / 2.f + 3.f });
	m_Heart->SetScale({ 10, 11 });
	CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER)->AddObject(m_Heart);

	CTexture* pAtlas;
	CAnimator* pAnimator;

	m_Character = new CCharacter;
	m_Character->SetPos({ vRes.x / 2.f - 280.f, vRes.y / 2.f });
	m_Character->SetScale({ 40, 40 });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeAtlas", L"texture\\Cole.png");
	pAnimator = m_Character->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ColeIdle", pAtlas, Vec2(40, 0), Vec2(40, 40), Vec2(0, 0), 0.3f, 4);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ColeIdle", true);
	CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER)->AddObject(m_Character);

	CNormalBeat* BeatImg;
	m_NormalBeats.resize(6);
	for (int i = 0; i < 6; ++i) {
		BeatImg = new CNormalBeat;
		m_NormalBeats[i] = BeatImg;
		m_NormalBeats[i]->SetScale({ 30, 40 });
		m_NormalBeats[i]->SetPos({ m_vecBars[0]->GetPos().x + StartPoint[i] * 3.f + 25.f, m_Judgebar->GetPos().y  -3.f});
		CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER)->AddObject(m_NormalBeats[i]);
		m_NormalBeats[i]->Hide();
	}

	m_GetSetBeat = new CGetSetBeat;
	m_GetSetBeat->SetPos({ m_vecBars[0]->GetPos().x + StartPoint[0] * 3.f + 25.f, m_Judgebar->GetPos().y - 3.f });
	m_GetSetBeat->SetBar(this);
	m_GetSetBeat->Hide();
	
	CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER)->AddObject(m_GetSetBeat);


	m_SpaceBarSprite = new CCharacter;
	m_SpaceBarSprite->SetPos({ vRes.x / 2.f +150.f, vRes.y / 2.f });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ButtonSpacebarSprite", L"texture\\ButtonSpacebarSprite.png");
	pAnimator = m_SpaceBarSprite->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ButtonSpacebarSprite", pAtlas, Vec2(10, 10), Vec2(50, 800), Vec2(0, 0), 0.3f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ButtonSpacebarSprite", true);
	CLevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER)->AddObject(m_SpaceBarSprite);
	m_SpaceBarSprite->Hide();


}
	float beatSpeed = 0.3f;

void CUnitBar::tick(float _dt)
{
	if (KEY_TAP(SPACE)) {
		m_SpaceBarSprite->FadeAway(0.3f);
	}
	if (m_IsMoving) {
		float y = m_vecBars[0]->GetPos().y;
		m_AccTime += _dt;
		
		y = m_fSpeed*sinf(m_AccTime);
		Vec2 vRes = CEngine::GetInst()->GetResolution();

		for (int i = 0; i < m_vecBars.size(); ++i) {
			m_vecBars[i]->SetPos({ m_vecBars[i]->GetPos().x, vRes.y/2.f +y});
		}
		m_Character->SetPos({ m_Character->GetPos().x, vRes.y / 2.f + y });
		m_Heart->SetPos({ m_Heart->GetPos().x, vRes.y / 2.f + y });
		m_GetSetBeat->SetPos({ m_GetSetBeat->GetPos().x, vRes.y / 2.f + y - 3.5f });
		for (int i = 0; i < m_NormalBeats.size(); ++i) {
			m_NormalBeats[i]->SetPos({ m_NormalBeats[i]->GetPos().x, vRes.y / 2.f + y - 3.5f });
		}
	}
}

void CUnitBar::HideBar(int _idx, float _duration)
{
	for (int i = StartPoint[_idx]; i < StartPoint[_idx]+NoteSize; i++) {
		m_vecBars[i]->Hide(_duration);
	}
}

void CUnitBar::ShowNormalBeat(int _idx, float _duration)
{
	m_NormalBeats[_idx]->Show(_duration);
}

void CUnitBar::StayGetSetBeat()
{
	Vec2 vRes = CEngine::GetInst()->GetResolution();
	m_GetSetBeat->SetPos({ m_vecBars[0]->GetPos().x + StartPoint[0] * 3.f + 53.f,m_GetSetBeat->GetPos().y - 3.5f});
	m_GetSetBeat->PlayStayAnim();
	m_GetSetBeat->SetSpeed(10.f);
	m_GetSetBeat->Show();
}

void CUnitBar::GoGetSetBeat(float _speed)
{
	m_GetSetBeat->SetSpeed(_speed);
	m_GetSetBeat->PlayGoAnim();
}


