#pragma once
#include "CNote.h"
class CNormalNote :
    public CNote
{
    GENERATED_OBJECT(CNote);
    class CAnimator* m_Animator;
private:
    int m_Idx;

public:
    virtual void Play(class CUnitBar* _bar) override;
    virtual void tick(float _dt) override;

public:
    CLONE(CNormalNote);
    CNormalNote();
    ~CNormalNote();
};

