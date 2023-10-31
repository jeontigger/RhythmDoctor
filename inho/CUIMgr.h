#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
	
private:
	CUI* m_FocusedUI;

public:
	void tick();

private:
	CUI* GetPriorityCheck(CUI* _ParentUI);
};
