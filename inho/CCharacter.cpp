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
		float alpha = 150 - 255 * (m_AccTime / m_Duration);
		SetAlpha(alpha);
		if (alpha <= 3.f) {
			SetAlpha(0);
		}
	}
}

void CCharacter::FadeAway(float _duration)
{
	m_AccTime = 0;
	m_Duration = _duration;
}
