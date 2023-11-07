#include "pch.h"
#include "CHeart.h"

#include "CTimeMgr.h"
#include "CTexture.h"

CHeart::CHeart():
	m_Acctime(0),
	m_isBig(false)
{
	m_Animator = AddComponent<CAnimator>(L"Animator");
}

CHeart::~CHeart()
{
}



void CHeart::begin()
{
	m_vOriginScale = GetScale();
}

void CHeart::tick(float _dt)
{
	Super::tick(_dt);

	ScaleBeat();
}


void CHeart::ScaleBeat()
{
	m_Acctime += DT;
	if (!m_isBig && BigScaleTime <= m_Acctime) {
		m_Acctime = 0.f;
		SetScale(GetScale() * BigScale);
		m_isBig = true;
	}
	else if (m_isBig && SmallScaleTime <= m_Acctime) {
		m_Acctime = 0.f;
		SetScale(m_vOriginScale);
		m_isBig = false;
	}
}
