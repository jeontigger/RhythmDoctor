#include "pch.h"
#include "CNormalNote.h"

#include "CAssetMgr.h"
#include "CUnitBar.h"

CNormalNote::CNormalNote():
	m_Idx(-1)
{
}

CNormalNote::~CNormalNote()
{
}

void CNormalNote::tick(float _dt)
{
	if (m_Idx == -1) {
		return;
	}
	
	m_AccTime += _dt;
	if (m_BeatSpeed <= m_AccTime) {
		m_bar->HideBar(m_Idx, m_BeatSpeed+DelayTime);
		m_bar->ShowNormalBeat(m_Idx, m_BeatSpeed + DelayTime);
		m_AccTime = 0;
		m_Idx++;
	}

	if (m_Idx >= NormalBeatCount) {
		m_Idx = -1;
	}
}

void CNormalNote::Play()
{
	m_AccTime = 0;
	m_Idx = 0;
}
