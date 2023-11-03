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

void CAnimUI::render(HDC _dc) {
	Super::render(_dc);
}