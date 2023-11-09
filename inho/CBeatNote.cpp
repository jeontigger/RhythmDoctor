#include "pch.h"
#include "CBeatNote.h"

#include "CUnitBar.h"

CBeatNote::CBeatNote():
	m_loopCount(-1),
	m_LoopDuration(0.3f)
{
}

CBeatNote::~CBeatNote()
{
}

void CBeatNote::tick(float _dt)
{

	if (m_loopCount == -1) {
		return;
	}

	m_AccTime += _dt;
	m_AccLoopTime += _dt;
	if (m_curCount < m_loopCount && m_LoopDuration <= m_AccLoopTime) {
		m_bar->StayGetSetBeat();
		m_AccTime = 0;
		m_curCount++;
		return;
	}

	if (m_LoopDuration <= m_AccTime) {
		m_bar->GoGetSetBeat(m_BeatSpeed);
		m_loopCount = -1;
	}
}

void CBeatNote::Play()
{
	m_AccTime = 0;
	m_AccLoopTime = m_LoopDuration;
}