// View.h : interface of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
class CView : public CWindowImpl<CView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	BEGIN_MSG_MAP(CView)
	END_MSG_MAP()
};
