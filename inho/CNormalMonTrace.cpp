#include "pch.h"
#include "CNormalMonTrace.h"

CNormalMonTrace::CNormalMonTrace()
{
}

CNormalMonTrace::~CNormalMonTrace()
{
}

void CNormalMonTrace::finaltick(float _DT)
{
	// 플레이어의 위치를 알아낸다.
	Vec2 vPlayerPos = m_pTarget->GetPos();

	// 몬스터 본인의 위치를 알아낸다.
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;
	Vec2 vMonsterPos = pMonster->GetPos();


	// 플레이어가 탐지범위를 벗어나면 Idle 상태로 돌아간다.
	// 1. 블랙보드에서 몬스터의 탐지범위를 꺼내온다.
	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float DetectRange = *pDetectRange;

	// 2. 플레이어와 몬스터의 거리를 구한다.
	float fDist = vPlayerPos.Distance(vMonsterPos);

	// 3. 플레이어와 몬스터의 거리가 탐지범위 이상이면 Idle 상태로 변경한다.
	if (DetectRange < fDist)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		return;
	}


	// 플레이어가 공격범위 이내로 들어오면 Attack 상태로 변경한다.
	{


	}


	// 플레이어를 추적한다.
	// 1. 몬스터가 이동할 방향을 알아낸다. (플레이어위치 - 몬스터 위치)
	Vec2 vDir = vPlayerPos - vMonsterPos;
	vDir.Normalize();

	// 2. 본인(몬스터) 의 이동속도를 알아낸다.
	float* pSpeed = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Speed");
	float fSpeed = *pSpeed;

	// 3. 플레이어를 향해서 이동한다.
	vMonsterPos += vDir * fSpeed * _DT;
	pMonster->SetPos(vMonsterPos);
}

void CNormalMonTrace::Enter()
{
	// 레벨에 있는 플레이어를 알아낸다.
	m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

	// Animator 에 Move Animation 재생
}

void CNormalMonTrace::Exit()
{
}


