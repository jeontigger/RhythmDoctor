#include "pch.h"
#include "CCharacter.h"

#include "CAssetMgr.h"

CCharacter::CCharacter()
{
	m_Animator = AddComponent<CAnimator>(L"Animator");
}

CCharacter::~CCharacter()
{
}
