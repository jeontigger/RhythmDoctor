#pragma once

class CLevel;
class CTexture;

class CEngine {
    SINGLETON(CEngine);

  private:
    HWND  m_hWnd;
    POINT m_ptResolution;

    HDC     m_dc;
    CTexture* m_SubTex;
    bool m_bDebugRender;

  public:
    HWND  GetMainWind() { return m_hWnd; }
    HDC   GetMainDC() { return m_dc; }
    POINT GetResolution() { return m_ptResolution; }

    bool DebugRender() { return m_bDebugRender; }
    void ChangeWindowSize(POINT _ptResolution, bool _bMenu);

  public:
    void init(HWND _hWnd, POINT _ptResolution);
    void tick();
};
