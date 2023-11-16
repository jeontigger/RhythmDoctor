#pragma once
#include "CObj.h"
class CCharacter :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    float m_AccTime;
    float m_Duration;
    class CAnimator* m_Animator;

public:
    CLONE_DISABLE(CCharacter);

    CCharacter();
    ~CCharacter();
};

