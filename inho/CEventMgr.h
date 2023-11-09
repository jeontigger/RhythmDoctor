#pragma once
class CEventMgr
{
	SINGLETON(CEventMgr);

private:
	vector<class CEvent*> m_vecEvents;
	class CWindowEvent* m_WinMove;
public:
	void Play(class CEvent* _event);
	void RegistWindowEvent(class CWindowEvent* _event) { 
		m_WinMove = _event;
		m_vecEvents.push_back((CEvent*)m_WinMove);
	}
	class CWindowEvent* GetWindowEvent() { return m_WinMove; }

public:
	void tick();
};

