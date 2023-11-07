#include "pch.h"
#include "CStagePlayLevel.h"

#include "CCamera.h"
#include "CEngine.h"
#include "CBtnUI.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"

#include "CJudgeBar.h"
#include "CCharacter.h"
#include "CHeart.h"

CStagePlayLevel::CStagePlayLevel()
{
}

CStagePlayLevel::~CStagePlayLevel()
{
	
}

void CStagePlayLevel::init()
{

	m_Judgebar = new CJudgeBar;
	Vec2 vRes = CEngine::GetInst()->GetResolution();
	Vec2 vBarScale = { 550, 1 };
	m_Judgebar->SetPos({ vRes.x/2.f,vRes.y/2.f });
	m_Judgebar->SetScale(vBarScale);
	AddObject(PLAYER, m_Judgebar);

	CTexture* pAtlas;
	CAnimator* pAnimator;

	m_Character = new CCharacter;
	m_Character->SetPos({ vRes.x / 2.f-  280.f, vRes.y / 2.f });
	m_Character->SetScale({ 40, 40 });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"ColeAtlas", L"texture\\Cole.png");
	pAnimator = m_Character->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"ColeIdle", pAtlas, Vec2(40, 0), Vec2(40, 40), Vec2(0, 0), 0.3f, 4);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"ColeIdle", true);
	AddObject(PLAYER, m_Character);

	m_Heart = new CHeart;
	m_Heart->SetPos({ vRes.x / 2.f + 280.f, vRes.y / 2.f+ 3.f });
	m_Heart->SetScale({ 10, 11 });
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"HeartAtlas", L"texture\\Heart.png");
	pAnimator = m_Heart->GetComponent<CAnimator>();
	pAnimator->CreateAnimation(L"HeartIdle", pAtlas, Vec2(0, 132), Vec2(39, 44), Vec2(0, 0), 0.3f, 1);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->Play(L"HeartIdle", true);

	AddObject(PLAYER, m_Heart);

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
	AddObject(PLAYER, m_Hand);
}

void CStagePlayLevel::enter()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);
}


void CStagePlayLevel::exit()
{
}

void CStagePlayLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(ESC)) {
		ChangeLevel(LEVEL_TYPE::STAGE_SELECT_LEVEL);
	}
	if(KEY_TAP(SPACE)) {
		Judge();
	}
}

void CStagePlayLevel::Judge()
{
	m_Hand->GetComponent<CAnimator>()->Play(L"Hand", false);
}