﻿#pragma once

#include "CObj.h"
class CNormalBeat:
	public CObj
{
	GENERATED_OBJECT(CObj);
private:
	int m_Idx;
	CAnimator* pAnimator;
	float m_AccTime;
	float m_HideTime;

public:
	void Show(float _duration);

public:
	virtual void tick(float _dt) override;
	void Play();

public:
	CLONE(CNormalBeat);
	CNormalBeat();
	~CNormalBeat();
};

