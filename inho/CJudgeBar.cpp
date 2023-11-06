#include "pch.h"
#include "CJudgeBar.h"

#include "CAnimator.h"
#include "CAssetMgr.h"

CJudgeBar::CJudgeBar()
{
	m_Bar = AddComponent<CAnimator>();
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"bar", L"texture\\bar.png");
	m_Bar->CreateAnimation(L"bar", pAtlas, Vec2(0, 0), Vec2(3, 1), Vec2(0, 0), 0.3f, 1);
	m_Bar->SaveAnimation(L"animdata");
	m_Bar->Play(L"bar", true);
}

CJudgeBar::~CJudgeBar()
{
}
