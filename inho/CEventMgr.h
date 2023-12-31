﻿#pragma once
class CEventMgr
{
	SINGLETON(CEventMgr);

private:
	bool stop;
	vector<class CNote*> m_vecNotes;
	class CWindowEvent* m_WinMove;
	class CObjEvent* m_ObjEvent;
public:

	void SetStop(bool _b) { stop = _b; }
	void RegistObjEvent(class CObjEvent* _event) { m_ObjEvent = _event; }
	void RegistNoteEvent(class CNote* _event) { m_vecNotes.push_back(_event); }
	void RegistWindowEvent(class CWindowEvent* _event) { m_WinMove = _event; }
	class CWindowEvent* GetWindowEvent() { return m_WinMove; }
	class CObjEvent* GetObjEvent() { return m_ObjEvent; }

public:
	const vector<class CNote*>& GetNoteEvents() { return m_vecNotes; }

public:
	void tick();
};

