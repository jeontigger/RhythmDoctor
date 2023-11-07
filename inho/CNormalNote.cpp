#include "pch.h"
#include "CNormalNote.h"

#include "CAssetMgr.h"
#include "CUnitBar.h"

CNormalNote::CNormalNote()
{
	m_Animator = AddComponent<CAnimator>();
	/*CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"bar", L"texture\\bar.png");
	m_Animator->CreateAnimation(L"bar", pAtlas, Vec2(0, 0), Vec2(3, 1), Vec2(0, 0), 0.3f, 1);
	m_Animator->SaveAnimation(L"animdata");
	m_Animator->Play(L"bar", true);*/
}

CNormalNote::~CNormalNote()
{
}

void CNormalNote::tick(float _dt)
{
	if (m_Idx == -1) {
		return;
	}
	
	m_AccTime += _dt;
	if (m_BeatSpeed <= m_AccTime) {
		m_bar->HideBar(m_Idx, m_BeatSpeed+0.1f);
		m_bar->ShowBeat(m_Idx, m_BeatSpeed + 0.1f);
		m_AccTime = 0;
		m_Idx++;
	}

	if (m_Idx >= 6) {
		m_Idx = -1;
	}
}

void CNormalNote::Play(CUnitBar* _bar)
{
	Super::Play(_bar);
	m_AccTime = 0;
	m_Idx = 0;
}
