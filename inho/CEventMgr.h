#pragma once
class CEventMgr
{
	SINGLETON(CEventMgr);

private:
	vector<class CEvent*> m_vecEvents;
public:
	void Play(class CEvent* _event);

public:
	void tick();
};

