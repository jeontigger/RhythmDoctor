#pragma once
#include "CProjectile.h"

class CMonster;

class CGuidedProjectile : public CProjectile {
    GENERATED_OBJECT(CProjectile);

  private:
    CMonster* target;

    float m_fMass;
    Vec2  m_vAccel;
    Vec2  m_vVelocity;
    Vec2  m_vForce;
    Vec2  m_vDir;

    float m_fRotateSpeed;

  private:
    void Update_1();
    void Update_2();
    void Update_3();

  public:
    virtual void FindTarget();
    void         SetDir(Vec2 _vDir) {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

  public:
      virtual void begin() override;
    virtual void tick(float _dt) override;

    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

  public:
      CLONE(CGuidedProjectile);
    CGuidedProjectile();
    CGuidedProjectile(const CGuidedProjectile& _Origin);
    ;
    ~CGuidedProjectile();
};
