#pragma once

#include "CCamera.h"
#include "CEntity.h"
#include "CTaskMgr.h"

#include "components.h"

class CObj : public CEntity {
  private:

    Vec2                      m_Pos;
    Vec2                      m_Scale;
    vector<CComponent*> m_vecComponent;
    int m_iLayerIdx;
    int m_iAlpha;

  public:
    Vec2 GetPos() { return m_Pos; }
    virtual Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); }
    Vec2 GetScale() { return m_Scale; }

    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    
    int GetLayerIdx() { return m_iLayerIdx; }

    int GetAlpha() { return m_iAlpha; }
    void SetAlpha(int _alpha) { m_iAlpha = _alpha; }

#pragma region Component
  protected:
    template <typename T> T* AddComponent(const wstring& _strName = L"") {
        T* pNewCom = new T(this);
        m_vecComponent.push_back(pNewCom);
        pNewCom->SetName(_strName);
        return pNewCom;
    }

public:
    const vector<CComponent*>& GetComponentAll() { return m_vecComponent; }
    template<typename T>
    T* GetComponent() {
        for (size_t i = 0; i < m_vecComponent.size(); ++i) {
            if (dynamic_cast<T*>(m_vecComponent[i])) {
                return (T*)m_vecComponent[i];
            }
        }

        return nullptr;
    }

    template<typename T>
    void GetComponents(vector<T*>& _out) {
        for (size_t i = 0; i < m_vecComponent.size(); ++i) {
            if (dynamic_cast<T>(m_vecComponent[i])) {
                _out.push_back((T*)m_vecComponent[i]);
            }
        }
    }
#pragma endregion

public:
    void Show() { m_iAlpha = 255; }
    void Hide() { m_iAlpha = 0; }

private:
    void(CObj::* pFunc)(float);
    float m_Duration;
    float m_AccTime;
    Vec2 m_Target;
    float m_Speed;

private:
    void FadeAway(float _dt);
    void Move(float _dt);
public:
    void SetFadeAway(float _duration);
    void SetMove(Vec2 _target, float _time);

  public:
     virtual void begin() {};
    virtual void tick(float _DT);
    virtual void finaltick(float _DT);
    virtual void render(HDC _dc);

    void Destroy();

    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) {}

private:
    void SetDead();

  public:
    CObj();
    CObj(const CObj& _Origin);
    virtual ~CObj();

    friend class CLevel;
    friend class CTaskMgr;
};
