#pragma once
#include "CNote.h"

constexpr int NormalBeatCount = 6;
constexpr int DelayTime = 0.3f;
class CNormalNote :
    public CNote
{
    GENERATED_OBJECT(CNote);

private:
    int m_Idx;

public:
    virtual void Play() override;
    virtual void tick(float _dt) override;

public:
    CNormalNote();
    ~CNormalNote();
};

