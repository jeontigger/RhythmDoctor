#pragma once
#include "CObj.h"

constexpr float GoalPosX = 400.f;

class CGetSetBeat:
	public CObj
{
	GENERATED_OBJECT(CObj);

private:
	class CAnimator* m_Animator;
	class CUnitBar* m_bar;

	float m_Speed;

public:
	void PlayStayAnim();
	void PlayGoAnim();
	void SetSpeed(float _speed) { m_Speed = _speed; }
	void SetBar(class CUnitBar* _bar) { m_bar = _bar; }

public:
	virtual void tick(float _dt) override;

public:
	CLONE_DISABLE(CGetSetBeat);
	CGetSetBeat();
	~CGetSetBeat();
};

