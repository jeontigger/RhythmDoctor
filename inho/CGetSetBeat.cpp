#include "pch.h"
#include "CGetSetBeat.h"

#include "CAnimator.h"
#include "CAssetMgr.h"
#include "CEngine.h"

#include "CUnitBar.h"
#include "CJudgeBar.h"

CGetSetBeat::CGetSetBeat():
	m_Speed(3.f)
{
	m_Animator = AddComponent<CAnimator>();
	CTexture* pAtlas;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"GetSetBeat", L"texture\\GetSetBeat.png");
	m_Animator->CreateAnimation(L"GetSetBeatGo", pAtlas, Vec2(0, 0), Vec2(36, 43), Vec2(0, 0), 0.1f, 3);
	m_Animator->CreateAnimation(L"GetSetBeatStay", pAtlas, Vec2(108, 0), Vec2(36, 43), Vec2(0, 0), 0.1f, 4);
	m_Animator->SaveAnimation(L"animdata");
	//m_Animator->LoadAnimation(L"animdata\\GetSetBeat.txt");
	SetScale({ 72, 32 });
}

CGetSetBeat::~CGetSetBeat()
{
}

void CGetSetBeat::PlayStayAnim()
{
	m_Animator->Play(L"GetSetBeatStay", true);
}

void CGetSetBeat::PlayGoAnim()
{
	m_Animator->Play(L"GetSetBeatGo", true);
}

void CGetSetBeat::tick(float _dt)
{
	if (!m_bar->IsShow()) {
		return;
	}
	if (GetAlpha() == 0) {
		return;
	}
	if (m_bar == nullptr) {
		return;
	}

	Vec2 vRes = CEngine::GetInst()->GetResolution();
	Vec2 vPos = GetPos();
	if (GoalPosX <= vPos.x) {
		Hide();
		for (int i = 0; i < m_bar->m_vecBars.size(); i++) {
			m_bar->m_vecBars[i]->Show();
		}
		m_Speed = 3.f;
		return;
	}

	float goalLen = GoalPosX - vPos.x;

	vPos.x += m_Speed / goalLen;

	SetPos(vPos);

	float length = GetPos().x - GetScale().x/2.f - (m_bar->m_vecBars[0]->GetPos().x  - 3.f);

	for (int i = 0; length/3.f - i < m_bar->m_vecBars.size() && 0 <= length/3.f - i; i++) {
		m_bar->m_vecBars[length / 3.f - i]->Show();
	}

	for (int i = 0 ; i < GetScale().x / 3.f&& i + length / 3.f < m_bar->m_vecBars.size(); i++) {		
		m_bar->m_vecBars[i+ length/3.f]->Hide(1.f);
	}

}
