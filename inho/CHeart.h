#pragma once
#include "CObj.h"

constexpr float BigScaleTime = 0.3f;
constexpr float SmallScaleTime = 0.3f;
constexpr float BigScale = 1.3f;

class CHeart :
    public CObj
{
    GENERATED_OBJECT(CObj);

    class CAnimator* m_Animator;

private:
    void ScaleBeat();
    float m_Acctime;
    Vec2 m_vOriginScale;
    bool m_isBig;



public:
    virtual void begin() override;
    virtual void tick(float _dt) override;

public:
    CLONE_DISABLE(CHeart);

    CHeart();
    ~CHeart();
};

