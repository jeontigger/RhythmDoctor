#pragma once
class CEvent
{
public:
	virtual void Play() = 0;
	virtual void tick(float _dt) = 0;

public:
	CEvent();
	~CEvent();
};

