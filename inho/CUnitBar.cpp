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

#include <time.h>

CUnitBar::CUnitBar():
	m_fDuration(-1)
{
	CJudgeBar* m_Judgebar = new CJudgeBar;
	Vec2 vRes = CEngine::GetInst()->GetResolution();
	Vec2 vBarScale = { 550, 3 };
	m_Judgebar->SetPos({ vRes.x / 2.f - 270.f, vRes.y / 2.f });
	/*m_Judgebar->SetScale(vBarScale);
	AddObject(PLAYER, m_Judgebar);*/
	m_Judgebar->SetScale({ 3,1 });

	m_vecBars.push_back(m_Judgebar);

	for (int i = 1; i < 180; i++) {
		m_vecBars.push_back(m_Judgebar->Clone());
		m_vecBars[i]->SetPos({ vRes.x / 2.f - 270.f + 3.f * i,vRes.y / 2.f });
	}
	

	m_Heart = new CHeart;
	m_Heart->SetPos({ vRes.x / 2.f + 280.f, vRes.y / 2.f + 3.f });
	m_Heart->SetScale({ 10, 11 });
	

	CTexture* pAtlas;
	CAnimator* pAnimator;

	m_Character = new CCharacter;
	m_Character->SetPos({ vRes.x / 2.f - 280.f, vRes.y / 2.f });
	m_Character->SetScale({ 40, 40 });
	pAnimator = m_Character->GetComponent<CAnimator>();
	

	CNormalBeat* BeatImg;
	m_NormalBeats.resize(6);
	for (int i = 0; i < 6; ++i) {
		BeatImg = new CNormalBeat;
		m_NormalBeats[i] = BeatImg;
		m_NormalBeats[i]->SetScale({ 30, 40 });
		m_NormalBeats[i]->SetPos({ m_vecBars[0]->GetPos().x + StartPoint[i] * 3.f + 25.f, m_Judgebar->GetPos().y - 3.f });
		m_NormalBeats[i]->Hide();
	}

	m_GetSetBeat = new CGetSetBeat;
	m_GetSetBeat->SetPos({ m_vecBars[0]->GetPos().x + StartPoint[0] * 3.f + 25.f, m_Judgebar->GetPos().y   });
	m_GetSetBeat->SetBar(this);
	m_GetSetBeat->Hide();

	m_SpaceBarSprite = new CCharacter;
	m_SpaceBarSprite->SetPos({ vRes.x / 2.f + 150.f, vRes.y / 2.f });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ButtonSpacebarSprite", L"texture\\ButtonSpacebarSprite.png");
	pAnimator = m_SpaceBarSprite->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ButtonSpacebarSprite", pAtlas, Vec2(10, 10), Vec2(50, 800), Vec2(0, 0), 0.3f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ButtonSpacebarSprite", true);
	
	m_SpaceBarSprite->Hide();
	m_SpaceBarSprite->SetInitAlpha(150);

	
	m_Correct = new CCharacter;
	m_Correct->SetPos({ vRes.x / 2.f, vRes.y / 2.f - 60.f });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Correct", L"texture\\Correct.png");
	pAnimator = m_Correct->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Correct", pAtlas, Vec2(0, 0), Vec2(81, 50), Vec2(0, 0), 0.3f, 1);
	
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Fast", L"texture\\Fast.png");
	pAnimator->CreateAnimation(L"Fast", pAtlas, Vec2(0, 0), Vec2(76, 46), Vec2(0, 0), 0.3f, 1);
	
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Slow", L"texture\\Slow.png");
	pAnimator->CreateAnimation(L"Slow", pAtlas, Vec2(0, 0), Vec2(86, 60), Vec2(0, 0), 0.3f, 1);
	
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Miss", L"texture\\Miss.png");
	pAnimator->CreateAnimation(L"Miss", pAtlas, Vec2(0, 0), Vec2(83, 60), Vec2(0, 0), 0.3f, 1);
	pAnimator->SaveAnimation(L"animdata");


	pAnimator->Play(L"Correct", true);

	m_Correct->Hide();


	m_IncorrectBeats.resize(2);
	CNormalBeat* ib = new CNormalBeat;
	ib->SetPos({ vRes.x / 2.f + 110.f, vRes.y / 2.f -3.f });
	ib->SetScale({ 30, 40 });
	ib->Hide();
	 m_IncorrectBeats[(UINT)JudgeBeatType::Left] = ib;

	ib = new CNormalBeat;
	ib->SetPos({ vRes.x / 2.f + 190.f, vRes.y / 2.f - 3.f });
	ib->SetScale({ 30, 40 });
	ib->Hide();
	 m_IncorrectBeats[(UINT)JudgeBeatType::Right] = ib;

	 m_CorrectBeat = new CNormalBeat;
	 m_CorrectBeat->SetPos({ vRes.x / 2.f + 150.f, vRes.y / 2.f - 3.f });
	 m_CorrectBeat->SetScale({ 30, 40 });
	 m_CorrectBeat->Hide();
	

	srand(time(NULL));

}

CUnitBar::~CUnitBar()
{
	for (int i = 0; i < m_vecBars.size(); ++i) {
		delete m_vecBars[i];
	}
	delete m_Heart;
	delete m_Character;
	for (int i = 0; i < m_NormalBeats.size(); ++i) {
		delete m_NormalBeats[i];
	}
	delete m_GetSetBeat;
	delete m_SpaceBarSprite;
	delete m_Correct;

	for (int i = 0; i < m_IncorrectBeats.size(); ++i) {
		delete m_IncorrectBeats[i];
	}

	delete m_CorrectBeat;
}

void CUnitBar::begin()
{

}

void CUnitBar::tick(float _dt)
{
	Super::tick(_dt);
	if (!m_IsStart) {
		return;
	}
	
	tickAll(_dt);
	if (KEY_TAP(SPACE)&& m_IsShow) {
		m_SpaceBarSprite->SetFadeAway(0.3f);
	}

	if (m_fDuration <= m_AccTime) {
		m_Character->GetComponent<CAnimator>()->Play(L"Idle", true);
		m_fDuration = 230.7f;
		m_Animating = false;
	}
	m_AccTime += _dt;
	if (m_IsMoving) {
		float y = m_vecBars[0]->GetPos().y;
		
		y = m_fSpeed * sinf(m_AccTime);
		Vec2 vRes = CEngine::GetInst()->GetResolution();
		
		SetPosAll({ vRes.x / 2.f,vRes.y / 2.f + y });


		if (m_AccTime <= m_fQuakeDuration) {
			Vec2 vPos = m_Character->GetPos();
			Vec2 vPosH = m_Heart->GetPos();
			int m_QuakeAmount = 10;
			int x = rand() % m_QuakeAmount - m_QuakeAmount / 2;
			int y = rand() % m_QuakeAmount - m_QuakeAmount / 2;

			vPos.x += x;
			vPos.y += y;
			vPosH.x += x;
			vPosH.y += y;

			m_Character->SetPos(vPos);
			m_Heart->SetPos(vPosH);

		}
	}
}

void CUnitBar::render(HDC _dc)
{
	if (m_IsShow) {
		Super::render(_dc);
		renderAll(_dc);
	}
}

void CUnitBar::finaltick(float _dt)
{
	Super::finaltick(_dt);
	finaltickAll(_dt);
}

void CUnitBar::finaltickAll(float _dt)
{
	for (int i = 0; i < m_vecBars.size(); ++i) {
		m_vecBars[i]->finaltick(_dt);
	}
	m_Heart->finaltick(_dt);
	m_Character->finaltick(_dt);
	for (int i = 0; i < m_NormalBeats.size(); ++i) {
		m_NormalBeats[i]->finaltick(_dt);
	}
	m_GetSetBeat->finaltick(_dt);
	m_SpaceBarSprite->finaltick(_dt);
	m_Correct->finaltick(_dt);

	for (int i = 0; i < m_IncorrectBeats.size(); ++i) {
		m_IncorrectBeats[i]->finaltick(_dt);
	}

	m_CorrectBeat->finaltick(_dt);
}

void CUnitBar::renderAll(HDC _dc)
{
	for (int i = 0; i < m_vecBars.size(); ++i) {
		m_vecBars[i]->render(_dc);
	}
	m_Heart->render(_dc);
	m_Character->render(_dc);
	for (int i = 0; i < m_NormalBeats.size(); ++i) {
		m_NormalBeats[i]->render(_dc);
	}
	m_GetSetBeat->render(_dc);
	m_SpaceBarSprite->render(_dc);
	m_Correct->render(_dc);

	for (int i = 0; i < m_IncorrectBeats.size(); ++i) {
		m_IncorrectBeats[i]->render(_dc);
	}

	m_CorrectBeat->render(_dc);
}

void CUnitBar::tickAll(float _dt)
{
	for (int i = 0; i < m_vecBars.size(); ++i) {
		m_vecBars[i]->tick(_dt);
	}
	m_Heart->tick(_dt);
	m_Character->tick(_dt);
	for (int i = 0; i < m_NormalBeats.size(); ++i) {
		m_NormalBeats[i]->tick(_dt);
	}
	m_GetSetBeat->tick(_dt);
	m_SpaceBarSprite->tick(_dt);
	m_Correct->tick(_dt);

	for (int i = 0; i < m_IncorrectBeats.size(); ++i) {
		m_IncorrectBeats[i]->tick(_dt);
	}

	m_CorrectBeat->tick(_dt);
}

CAnimator* CUnitBar::GetCharacterAnimator()
{
	return m_Character->GetComponent<CAnimator>();
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

void CUnitBar::SetPosAll(Vec2 _target)
{
	for (int i = 0; i < m_vecBars.size(); ++i) {
		m_vecBars[i]->SetPos({ m_vecBars[i]->GetPos().x, _target.y });
	}
	m_Character->SetPos({ _target.x - 280.f,  _target.y });
	m_Heart->SetPos({ _target.x + 280.f,  _target.y });
	m_GetSetBeat->SetPos({ m_GetSetBeat->GetPos().x,  _target.y - 3.5f });
	for (int i = 0; i < m_NormalBeats.size(); ++i) {
		m_NormalBeats[i]->SetPos({ m_NormalBeats[i]->GetPos().x,  _target.y - 3.5f });
	}
	for (int i = 0; i < m_IncorrectBeats.size(); ++i) {
		m_IncorrectBeats[i]->SetPos({ m_IncorrectBeats[i]->GetPos().x,  _target.y - 3.5f });
	}
	m_CorrectBeat->SetPos({ m_CorrectBeat->GetPos().x,  _target.y - 3.5f });
}

void CUnitBar::SetAnimation(const wstring& _str, float _time)
{
	m_Character->GetComponent<CAnimator>()->Play(_str, true);
	m_fDuration = m_AccTime + _time;
	m_Animating = true;
}

void CUnitBar::StayGetSetBeat()
{
	Vec2 vRes = CEngine::GetInst()->GetResolution();
	m_GetSetBeat->SetPos({ m_vecBars[0]->GetPos().x + StartPoint[0] * 3.f + 53.f,m_GetSetBeat->GetPos().y });
	m_GetSetBeat->PlayStayAnim();
	m_GetSetBeat->SetSpeed(10.f);
	m_GetSetBeat->Show();
}

void CUnitBar::GoGetSetBeat(float _speed)
{
	m_GetSetBeat->SetSpeed(_speed);
	m_GetSetBeat->PlayGoAnim();
}

void CUnitBar::HideAll()
{
	m_IsShow = false;
	m_Character->Hide();
	m_Heart->Hide();
	for (int i = 0; i < m_vecBars.size(); ++i) {
		m_vecBars[i]->Hide(1000.f);
	}
}

void CUnitBar::ShowAll()
{
	m_IsShow = true;
	m_Character->Show();
	m_Heart->Show();
	for (int i = 0; i < m_vecBars.size(); ++i) {
		m_vecBars[i]->Show();
	}
}

void CUnitBar::ShowCharacter()
{
	m_Character->Show();
}

void CUnitBar::Incorrect(JudgeBeatType _type)
{
	if (!m_IsShow)
		return;
	CAnimator* pAnimator = m_Character->GetComponent<CAnimator>();
	if (_type == JudgeBeatType::Left) {
		m_IncorrectBeats[(UINT)JudgeBeatType::Left]->Show(0.3f);
		HideBar((UINT)BeatPoint::Left, 0.3f);
		m_Correct->GetComponent<CAnimator>()->Play(L"Fast", true);
		m_Correct->SetFadeAway(0.7f);
		if (!m_Animating) {
			pAnimator->Play(L"Incorrect", false);
			m_fDuration = m_AccTime + 1.1f;
			m_Animating = true;
		}

	}
	else if(_type == JudgeBeatType::Right) {
		m_IncorrectBeats[(UINT)JudgeBeatType::Right]->Show(0.3f);
		HideBar((UINT)BeatPoint::Right, 0.3f);
		m_Correct->GetComponent<CAnimator>()->Play(L"Slow", true);
		m_Correct->SetFadeAway(0.7f);
		if (!m_Animating) {
			pAnimator->Play(L"Incorrect", false);
			m_fDuration = m_AccTime + 1.1f;
		}
	}
	else {
		m_Correct->GetComponent<CAnimator>()->Play(L"Miss", true);
		m_Correct->SetFadeAway(0.7f);
		if (!m_Animating) {
			pAnimator->Play(L"Miss", false);
			m_fDuration = m_AccTime + 0.9f;
		}
	}
	m_fQuakeDuration = m_AccTime + 0.3f;
}

void CUnitBar::Correct()
{
	if (m_IsShow) {
		m_CorrectBeat->Show(0.3f);
		HideBar((UINT)BeatPoint::Correct, 0.3f);

		m_Correct->GetComponent<CAnimator>()->Play(L"Correct", true);
		m_Correct->SetFadeAway(0.7f);

		if (!m_Animating) {
			m_Character->GetComponent<CAnimator>()->Play(L"Correct", false);
			m_fDuration = m_AccTime + 0.8f;
		}
	}
}