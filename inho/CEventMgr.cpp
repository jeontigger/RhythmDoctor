#include "pch.h"
#include "CEventMgr.h"

#include "CEvent.h"
#include "CWindowEvent.h"
#include "CNote.h"

#include "CTimeMgr.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
	if (nullptr != m_WinMove) {
		delete m_WinMove;
	}

	for (int i = 0; i < m_vecNotes.size(); ++i) {
		if(nullptr!= m_vecNotes[i]){
			delete m_vecNotes[i];
		}
	}
	delete m_ObjEvent;
}

void CEventMgr::tick()
{
	float _dt = DT;
	for (int i = 0; i < m_vecNotes.size(); ++i) {
		if (m_vecNotes[i] != nullptr) {
			m_vecNotes[i]->tick(_dt);
		}
	}
	m_WinMove->tick(_dt);
}
