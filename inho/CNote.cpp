#include "pch.h"
#include "CNote.h"

#include "CEngine.h"
#include "CAnimator.h"
#include "CAssetMgr.h"

CNote::CNote()
{
	CAnimator* pAnimator = AddComponent<CAnimator>();
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"bar", L"texture\\bar.png");
	pAnimator->CreateAnimation(L"bar", pAtlas, Vec2(0, 0), Vec2(3, 1), Vec2(0, 0), 0.3f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"bar", true);
}


CNote::~CNote()
{
}

void CNote::tick(float _dt)
{
	Vec2 vStartPos = CEngine::GetInst()->GetResolution();
	vStartPos.x += -200.f;
	vStartPos.y += 200.f;
	
	m_AccTime += _dt;
	if (m_Beat <= m_AccTime) {
		SetPos(vStartPos);
		m_AccTime = 0;
	}
}
