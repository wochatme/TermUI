/////////////////////////////////////////////////////////////////////////////
#pragma once
class CTXTView
{
public:
	HWND m_hWnd = NULL;

	HWND Create(
		_In_opt_ HWND hWndParent,
		_In_ _U_RECT rect = NULL,
		_In_opt_z_ LPCTSTR szWindowName = NULL,
		_In_ DWORD dwStyle = 0,
		_In_ DWORD dwExStyle = 0,
		_In_ _U_MENUorID MenuOrID = 0U,
		_In_opt_ LPVOID lpCreateParam = NULL)
	{
		m_hWnd = CreateWindowExW(0, L"Scintilla", NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
			0, 0, 16, 16, hWndParent, NULL, HINST_THISCOMPONENT, NULL);

		if (::IsWindow(m_hWnd))
		{
			::SendMessage(m_hWnd, SCI_SETTECHNOLOGY, SC_TECHNOLOGY_DIRECTWRITE, 0);
			::SendMessage(m_hWnd, SCI_SETCODEPAGE, SC_CP_UTF8, 0);
			::SendMessage(m_hWnd, SCI_SETEOLMODE, SC_EOL_LF, 0);
			::SendMessage(m_hWnd, SCI_SETWRAPMODE, SC_WRAP_WORD, 0);
			::SendMessage(m_hWnd, SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)"Courier New");
			::SendMessage(m_hWnd, SCI_STYLESETSIZEFRACTIONAL, STYLE_DEFAULT, 1300);

			::SendMessage(m_hWnd, SCI_SETPHASESDRAW, SC_PHASES_MULTIPLE, 0);
#if 0
			::SendMessage(m_hWnd, SCI_STYLESETBACK, STYLE_LINENUMBER, RGB(255, 255, 255));
			::SendMessage(m_hWnd, SCI_SETMARGINWIDTHN, 1, 2);
			::SendMessage(m_hWnd, SCI_SETREADONLY, 1, 0);
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 0, 0);
#endif 
		}
		return m_hWnd;
	}

	operator HWND() const throw()
	{
		return m_hWnd;
	}

	BOOL IsWindow() const throw()
	{
		return ::IsWindow(m_hWnd);
	}

	BOOL GetFocus()
	{
		return (m_hWnd == ::GetFocus());
	}

	BOOL ShowWindow(int nCmdShow)
	{
		BOOL bRet = FALSE;

		if (IsWindow())
		{
			bRet = ::ShowWindow(m_hWnd, nCmdShow);
		}

		return bRet;
	}

	BOOL SetWindowPos(HWND hWndInsertAfter, int  X, int  Y, int  cx, int  cy, UINT uFlags)
	{
		BOOL bRet = FALSE;
		if (IsWindow())
		{
			bRet = ::SetWindowPos(m_hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
		}
		return bRet;
	}
#if 0
	int AppendText(const char* text, U32 length)
	{
		if (IsWindow())
		{
			int totalLines;
			//bool readonly = (bool)::SendMessage(m_hWnd, SCI_GETREADONLY, 0, 0);
			::SendMessage(m_hWnd, SCI_SETREADONLY, 0, 0);
			::SendMessage(m_hWnd, SCI_APPENDTEXT, length, (LPARAM)text);
			totalLines = (int)SendMessage(m_hWnd, SCI_GETLINECOUNT, 0, 0);
			::SendMessage(m_hWnd, SCI_LINESCROLL, 0, totalLines);
			::SendMessage(m_hWnd, SCI_SETREADONLY, 1, 0);
		}
		return 0;
	}
#endif 
};
