#pragma once
class CPaletteMgr {
    SINGLETON(CPaletteMgr);

  public:
    enum PenColor { PWHITE, PBLACK, PRED, PBLUE, PGREEN };

    enum BrushColor { BWHITE, BBLACK, BRED, BBLUE, BGREEN, BHOLLOW };

  private:
    map<PenColor, HPEN>     pens;
    map<BrushColor, HBRUSH> brushes;
    HDC                     dc;

  public:
    void init(HDC _dc);
    void AddPen(PenColor en, HPEN pen);
    bool SelectPen(PenColor en);

    void AddBrush(BrushColor en, HBRUSH);
    bool SelectBrush(BrushColor en);
};
