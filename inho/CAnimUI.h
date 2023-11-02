#pragma once
#include "CUI.h"

class CAnimUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    class CAnimator* m_Animator;

public:
    virtual void tick(float _dt) override;

    CAnimator* GetAnimator() { return m_Animator; }

public:
    CLONE(CAnimUI);
    CAnimUI();
    CAnimUI(const CAnimUI& _Origin);
    ~CAnimUI();
};

