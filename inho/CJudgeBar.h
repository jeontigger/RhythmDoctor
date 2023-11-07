#pragma once
#include "CObj.h"
class CJudgeBar :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:

    class CAnimator* m_Bar;
    float m_AccTime;
    float m_ShowTime;

public:
    void Hide(float _duration);

public:
    virtual void tick(float _dt) override;

public:
    CLONE(CJudgeBar);

    CJudgeBar();
    ~CJudgeBar();
};

