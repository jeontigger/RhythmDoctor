#pragma once
#include "CObj.h"

class CCollider;

class CProjectile : public CObj {
  private:
      CCollider* m_Collider;
    float m_Speed;
    float m_Angle;

  public:
    void SetAngle(float _theta) { m_Angle = _theta; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }

    float GetSpeed() { return m_Speed; }
    float GetAngle() { return m_Angle; }

    CCollider* GetCollider() { return m_Collider; }

  public:
    virtual void render(HDC _dc) override;

  public:
      CLONE(CProjectile);
    CProjectile();
    CProjectile(const CProjectile& _Origin);
    ~CProjectile();
};
