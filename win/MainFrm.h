// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#define IDM_NEWTAB		0x1010

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
#if 0
	CTABView m_viewTAB;
#endif 
	CView m_viewTab;
	CTXTView m_viewTXT;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return FALSE; // m_viewTAB.PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
#if 0
		MESSAGE_HANDLER(WM_NCCALCSIZE, OnNCCalcSize)
#endif 
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnNewTab)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{

		m_viewTab.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
#if 0
		m_viewTAB.ModifyStyle(0, 
			CTCS_TOOLTIPS | 
			CTCS_SCROLL | 
			CTCS_CLOSEBUTTON | 
			CTCS_DRAGREARRANGE | 
			CTCS_BOLDSELECTEDTAB | CTCS_FLATEDGE
		);
		m_viewTAB.InsertItem(0, L"cmd.exe", -1, L"command line", true);
		m_viewTAB.InsertItem(1, L"WSL", -1, L"Windows Subsystem for Linux", true);
		m_viewTAB.InsertItem(2, L"PowerShell", -1, L"Windows Subsystem for Linux", true);
		m_viewTAB.InsertItem(3, L"Ubuntu Linux", -1, L"Windows Subsystem for Linux", true);
#endif 
		m_viewTXT.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL);

		HMENU m = GetSystemMenu(FALSE);
		AppendMenu(m, MF_SEPARATOR, 0, 0);
		AppendMenu(m, MF_ENABLED, IDM_NEWTAB, L"New Tab");

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		SetWindowPos(NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		bHandled = FALSE;
		return 1;
	}

	LRESULT OnNotify(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		NMHDR* pnmhdr = (NMHDR*)lParam;
		if (pnmhdr)
		{
			if (pnmhdr->hwndFrom == m_viewTab)
			{
				if (pnmhdr->code == CTCN_PLUSBUTTON)
				{
					//m_viewTab.AddNewTab();
					m_viewTab.ShowDropDownMenu();
				}
				return 0;
			}
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		RECT rect = {};
		GetClientRect(&rect);

		// resize client window
		::SetWindowPos(m_viewTab.m_hWnd, NULL, rect.left, rect.top,
			rect.right - rect.left, rect.top + TAB_WINDOW_HEIGHT,
			SWP_NOZORDER | SWP_NOACTIVATE);

		::SetWindowPos(m_viewTXT.m_hWnd, NULL, rect.left, rect.top + TAB_WINDOW_HEIGHT,
			rect.right - rect.left, rect.bottom - (rect.top + TAB_WINDOW_HEIGHT),
			SWP_NOZORDER | SWP_NOACTIVATE);

		Invalidate();
		return 0;
	}
#if 0
	LRESULT OnNCCalcSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (!wParam) 
			return DefWindowProc();
		else
		{
			UINT dpi = GetDpiForWindow(m_hWnd);
			int frame_x = GetSystemMetricsForDpi(SM_CXFRAME, dpi);
			int frame_y = GetSystemMetricsForDpi(SM_CYFRAME, dpi);
			int padding = GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);

			NCCALCSIZE_PARAMS* params = (NCCALCSIZE_PARAMS*)lParam;
			RECT* requested_client_rect = params->rgrc;

			requested_client_rect->right -= frame_x + padding;
			requested_client_rect->left += frame_x + padding;
			requested_client_rect->bottom -= frame_y + padding;
		}
		return 0;
	}
#endif 

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		RECT wr = {};
		RECT cr = {};

		GetWindowRect(&wr);
		GetClientRect(&cr);

		int i = 0;

		return i;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		PAINTSTRUCT ps = {};
		HDC hdc = BeginPaint(&ps);
#if 0
		RECT rc = {};
		HPEN hPen, hOldPen;

		GetClientRect(&rc);

		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hOldPen = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, rc.left, rc.top, NULL);
		LineTo(hdc, rc.right, rc.bottom);
#if 0
		MoveToEx(hdc, rc.right, rc.top, NULL);
		LineTo(hdc, rc.left, rc.bottom);
#endif 
		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);
#endif 
		EndPaint(&ps);
		return 0;
	}

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		switch (wParam & ~0xF) /* low 4 bits reserved to Windows */
		{
		case IDM_NEWTAB:
			m_viewTab.AddNewTab();
			break;
		default:
			bHandled = FALSE;
			break;
		}

		return 0;
	}

	LRESULT OnNewTab(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}
};
