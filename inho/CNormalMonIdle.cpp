#include "pch.h"
#include "CNormalMonIdle.h"



CNormalMonIdle::CNormalMonIdle()
{
}

CNormalMonIdle::~CNormalMonIdle()
{
}

void CNormalMonIdle::finaltick(float _DT)
{
	if (nullptr == m_pTarget)
		return;

	// 플레이어가 탐지범위 내에 있는지 확인
	// 1. 블랙보드에 저장되어있는 탐지범위를 가져온다/
	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float DetectRange = *pDetectRange;

	// 2. 플레이어와 몬스터간의 거리를 체크
	Vec2 vPlayerPos = m_pTarget->GetPos();
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;

	Vec2 vMonsterPos = pMonster->GetPos();

	float fDist = vPlayerPos.Distance(vMonsterPos);

	if (fDist < DetectRange)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::TRACE);
	}
}

void CNormalMonIdle::Enter()
{
	//CAnimator* pAnimator = GetOwnerSM()->GetOwner()->GetComponent<CAnimator>();
	//pAnimator->Play(L"")

	// 레벨에 있는 플레이어를 알아낸다.
	m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CNormalMonIdle::Exit()
{
}


