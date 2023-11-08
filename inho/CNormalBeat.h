#pragma once

#include "CObj.h"
constexpr float Magnificant[6] = { 1.f, 1.2f, 0.8f, 0.6f, 0.4f, 0.2f};
class CNormalBeat:
	public CObj
{
	GENERATED_OBJECT(CObj);
private:
	int m_Idx;
	CAnimator* pAnimator;
	float m_ScaleAccTime;
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

