#pragma once
class CEvent
{
private:
	float m_StartTime;

public:
	void SetStartTime(float _time) { m_StartTime = _time; }
	float GetStartTime() { return m_StartTime; }

public:
	virtual void Play() = 0;
	virtual void tick(float _dt) = 0;

public:
	CEvent();
	~CEvent();
};

