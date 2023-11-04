#pragma once

class CTexture;

enum class CAM_EFFECT {
    FADE_IN,
    FADE_OUT,
};

struct FCamEvent {
    CAM_EFFECT type;
    float AccTime;
    float Duration;
};

class CCamera {
    SINGLETON(CCamera);

  private:
      bool m_bUseCamera;

    Vec2 m_vLookAt;
    Vec2 m_vDiff;
    CTexture* m_Veil;

    Vec2 m_TargetAt;
    float m_LinearSpeed;

    list<FCamEvent> m_EventList;
    UINT m_Alpha;

  public:
    void tick();
    void render(HDC _dc);
    void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; m_TargetAt = _vLookAt; }
    void SetLinearLookAt(Vec2 _vLookAt, float _time);

    void FadeIn(float _time) {
        FCamEvent evnt = {};
        evnt.type = CAM_EFFECT::FADE_IN;
        evnt.AccTime = 0.f;
        evnt.Duration = _time;
        m_EventList.push_back(evnt);
    }

    void FadeOut(float _time) {
        FCamEvent evnt = {};
        evnt.type = CAM_EFFECT::FADE_OUT;
        evnt.AccTime = 0.f;
        evnt.Duration = _time;
        m_EventList.push_back(evnt);
    }

    Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
    Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
};
