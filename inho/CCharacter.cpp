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

void CCharacter::tick(float _dt)
{
	m_AccTime += _dt;
	if (m_AccTime <= m_Duration) {
		SetAlpha(255 - 255*(m_AccTime/ m_Duration));
	}
}

void CCharacter::FadeAway(float _duration)
{
	m_AccTime = 0;
	m_Duration = _duration;
}
