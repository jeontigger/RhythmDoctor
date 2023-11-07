#include "pch.h"
#include "CStagePlayLevel.h"

#include "CCamera.h"
#include "CEngine.h"
#include "CBtnUI.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"

#include "CUnitBar.h"
#include "CCharacter.h"

CStagePlayLevel::CStagePlayLevel()
{
}

CStagePlayLevel::~CStagePlayLevel()
{
	
}

void CStagePlayLevel::init()
{

	m_Judgebar = new CUnitBar;
	AddObject(PLAYER, m_Judgebar);

	Vec2 vRes = CEngine::GetInst()->GetResolution();
	
	CTexture* pAtlas;
	CAnimator* pAnimator;


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