#pragma once
class CLevelMgr {
    SINGLETON(CLevelMgr);

  private:
      bool m_stageClear;
    class CLevel* m_pCurLevel;
    CLevel* m_arrLevels[(UINT)LEVEL_TYPE::END];

  public:
    CLevel* GetCurLevel() { return m_pCurLevel; }
    void SetClear(bool _b){m_stageClear = _b;}
    bool IsClear() { return m_stageClear; }
private:
    void ChangeLevel(LEVEL_TYPE _Type);

  public:
    void init();
    void tick();
    void render(HDC _dc);

    friend class CTaskMgr;
};
