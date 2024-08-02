// View.h : interface of the CTABView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
class CTABView : public CWindowImpl<CTABView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	BEGIN_MSG_MAP(CTABView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		RECT rect = {};
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(&ps);

		GetClientRect(&rect);

		HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 128)); // RGB for gray

		::FillRect(hdc, &rect, hBrush);
		::DeleteObject(hBrush);

		EndPaint(&ps);
		return 0;
	}

};
