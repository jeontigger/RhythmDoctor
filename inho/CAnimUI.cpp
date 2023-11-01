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
}

CAnimUI::~CAnimUI()
{
}

void CAnimUI::tick(float _dt)
{
	//CheckPosAndScale;
	Super::tick(_dt);

	
}