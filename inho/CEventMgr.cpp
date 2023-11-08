#include "pch.h"
#include "CEventMgr.h"

#include "CEvent.h"

#include "CTimeMgr.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::Play(CEvent* _event)
{
	_event->Play(); 
	m_vecEvents.push_back(_event);
}

void CEventMgr::tick()
{
	float _dt = DT;
	for (int i = 0; i < m_vecEvents.size(); ++i) {
		if (m_vecEvents[i] != nullptr) {
			m_vecEvents[i]->tick(_dt);
		}
	}
}
