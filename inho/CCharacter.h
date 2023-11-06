#pragma once
#include "CObj.h"
class CCharacter :
    public CObj
{
    GENERATED_OBJECT(CObj);

    class CAnimator* m_Animator;

public:
    CLONE_DISABLE(CCharacter);

    CCharacter();
    ~CCharacter();
};

