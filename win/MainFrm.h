// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define MESSAGE_DWM_HANDLER() \
	{ \
		LRESULT result = 0; \
		BOOL bRet = DwmDefWindowProc(m_hWnd, uMsg, wParam, lParam, &result); \
		if(bRet) \
			return result; \
	}

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CTABView m_viewTAB;
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
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_viewTAB.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
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

		m_viewTXT.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL);
		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

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
			if (pnmhdr->code == NM_CLICK)
				return 0;
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		RECT rect = {};
		GetClientRect(&rect);

		// resize client window
		::SetWindowPos(m_viewTAB.m_hWnd, NULL, rect.left, rect.top,
			rect.right - rect.left, rect.top + TAB_WINDOW_HEIGHT,
			SWP_NOZORDER | SWP_NOACTIVATE);

		::SetWindowPos(m_viewTXT.m_hWnd, NULL, rect.left, rect.top + TAB_WINDOW_HEIGHT,
			rect.right - rect.left, rect.bottom - (rect.top + TAB_WINDOW_HEIGHT),
			SWP_NOZORDER | SWP_NOACTIVATE);

		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}
};
