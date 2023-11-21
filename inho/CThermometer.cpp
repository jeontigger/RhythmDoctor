#include "pch.h"
#include "CThermometer.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CThermometer::CThermometer()
	:m_TexBossThermometer(nullptr)
	,m_TexBossHealthBar(nullptr)
	,m_TexUserThermometer(nullptr)
	,m_TexUserHealthBar(nullptr)
{
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"bosstemp", L"texture\\BossThermometer.png");
	CAnimator* pAnimator = AddComponent<CAnimator>();
	pAnimator->CreateAnimation(L"Idle", pAtlas, Vec2(0, 0), Vec2(256, 14), Vec2(0, 0), 0.1f, 1);
	pAnimator->Play(L"Idle", false);
}

CThermometer::~CThermometer()
{
}

void CThermometer::BossHealthReduce()
{
	m_IBossCurHealth--;
}

bool CThermometer::UserHealthReduce()
{
	m_IUserCurHealth--;
	if (m_IUserCurHealth < 0) {
		return false;
	}
}

