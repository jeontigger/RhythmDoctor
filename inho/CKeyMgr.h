#pragma once
class CKeyMgr {

    SINGLETON(CKeyMgr);

  private:
    vector<FKeyData> m_vecKeyData;

    Vec2 m_vMousePos;
    bool m_bAnyKey_Tap;
    bool m_bAnyKey_Pressed;
    bool m_bAnyKey_Released;

  public:
    KEY_STATE GetKeyState(KEY _Key) { return m_vecKeyData[_Key].eState; }
    Vec2 GetMousePos() { return m_vMousePos; }
    bool IsAnyKeyTap() { return m_bAnyKey_Tap; }
    bool IsAnyKeyPressed() { return m_bAnyKey_Pressed; }
    bool IsAnyKeyReleased() { return m_bAnyKey_Released; }

  public:
    void init();
    void tick();
};
