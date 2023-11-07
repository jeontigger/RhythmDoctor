#pragma once
#include "CObj.h"
class CJudgeBar :
    public CObj
{
    GENERATED_OBJECT(CObj);
    class CAnimator* m_Bar;

public:
    CLONE(CJudgeBar);

    CJudgeBar();
    ~CJudgeBar();
};

