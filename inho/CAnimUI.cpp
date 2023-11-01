#include "pch.h"
#include "CAnimUI.h"

#include "CLogMgr.h"
#include "CKeyMgr.h"

CAnimUI::CAnimUI():m_Animator(nullptr)
{
	m_Animator = AddComponent<CAnimator>(L"Animator");
}

CAnimUI::CAnimUI(const CAnimUI& _Origin)
{
	delete m_Animator;
}

CAnimUI::~CAnimUI()
{
}

void CAnimUI::tick(float _dt)
{
	Super::tick(_dt);
}

void CAnimUI::finaltick(float _DT)
{
	m_Animator->finaltick(_DT);
	for (int i = 0; i < m_vecChildUI.size(); i++) {
		m_vecChildUI[i]->finaltick(_DT);
	}
}
