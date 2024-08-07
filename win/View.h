// View.h : interface of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//LPCWSTR title_string = L"CMD.EXE - 0"; // L"C:\\windows\\system32\\cmd.exe";

/* DUI_ALIGN() is only to be used to align on a power of 2 boundary */
#define DUI_ALIGN(size, boundary)   (((size) + ((boundary) -1)) & ~((boundary) - 1))
#define DUI_ALIGN_DEFAULT32(size)   DUI_ALIGN(size, 4)
#define DUI_ALIGN_DEFAULT64(size)   DUI_ALIGN(size, 8)      /** Default alignment */
#define DUI_ALIGN_PAGE8K(size)      DUI_ALIGN(size, 8192)      /** Default alignment */
#define DUI_ALIGN_PAGE(size)        DUI_ALIGN(size, (1<<16))
#define DUI_ALIGN_TRUETYPE(size)    DUI_ALIGN(size, 64)    

// a pure 32-bit true color bitmap object
typedef struct XBitmap
{
	U8    id;
	U32* data;
	int   w;
	int   h;
} XBitmap;

#define IDM_COMMAND_EXE		100
#define IDM_POWER_SHELL		101

#define TAB_MAX_LENGTH		256
#define TAB_MIN_LENGTH		64
#define SPECIAL_LENGTH		64

#define ACTIVE_ITEM_ZORDER	0xFFFFFFFF
#define XITEM_MAX_NUMBER	60
#define TITLE_MAX_STRING	32
typedef struct XItem XItem;

#define XITEM_XBUTTON_HIT	0x00000001
//#pragma pack(push, 1)
struct XItem
{
	XItem* prev;
	XItem* next;
	U32 status;
	U32 zorder;
	RECT rect;
	WCHAR title[TITLE_MAX_STRING + 1];
	U8 length;
	XBitmap* imgNormal;
	XBitmap* imgActive;
	IDWriteTextLayout* pTextLayout;
	void* udata;
};
//#pragma pack(pop)

// Notifications:
#define CTCN_FIRST              (0U-550U)           // TCN_FIRST
#define CTCN_LAST               (0U-580U)           // TCN_LAST

#define CTCN_SELCHANGE          (TCN_FIRST - 1)     // TCN_SELCHANGE
#define CTCN_SELCHANGING        (TCN_FIRST - 2)     // TCN_SELCHANGING
//#define CTCN_GETOBJECT          (TCN_FIRST - 3)     // TCN_GETOBJECT
//#define CTCN_FOCUSCHANGE        (TCN_FIRST - 4)     // TCN_FOCUSCHANGE
#define CTCN_PLUSBUTTON         (TCN_FIRST - 10)    // obsolete for now
#define CTCN_INSERTITEM         (TCN_FIRST - 11)
#define CTCN_DELETEITEM         (TCN_FIRST - 12)
#define CTCN_MOVEITEM           (TCN_FIRST - 13)
#define CTCN_SWAPITEMPOSITIONS  (TCN_FIRST - 14)
#define CTCN_CLOSE              (TCN_FIRST - 15)
#define CTCN_BEGINITEMDRAG      (TCN_FIRST - 21)
#define CTCN_ACCEPTITEMDRAG     (TCN_FIRST - 22)
#define CTCN_CANCELITEMDRAG     (TCN_FIRST - 23)
#define CTCN_MCLICK             (TCN_FIRST - 24)
#define CTCN_MDBLCLK            (TCN_FIRST - 25)

// Structures
typedef struct tagNMCTCITEM
{
	NMHDR   hdr;
	int     iItem;  // Item Index
	POINT   pt;     // Client Coordinates
} NMCTCITEM, * LPNMCTCITEM;

typedef struct tagNMCTC2ITEMS
{
	NMHDR   hdr;
	int     iItem1;  // First Item Index
	int     iItem2;  // Second Item Index
	POINT   pt;      // Client Coordinates
} NMCTC2ITEMS, * LPNMCTC2ITEMS;

typedef struct tagCTCHITTESTINFO
{
	POINT pt;        // Client Coordinates of point to test
	UINT flags;
} CTCHITTESTINFO, * LPCTCHITTESTINFO;

class CView : public CWindowImpl<CView>
{
	U32* m_screenBuff = nullptr;
	U32  m_screenSize = 0;

	XBitmap m_xbmpLA = { 0 };
	XBitmap m_xbmpL0 = { 0 };
	XBitmap m_xbmpRA = { 0 };
	XBitmap m_xbmpR0 = { 0 };

	XBitmap m_xbmpTA = { 0 };
	XBitmap m_xbmpT0 = { 0 };

	XBitmap m_xbmpXA0 = { 0 };
	XBitmap m_xbmpXAA = { 0 };
	XBitmap m_xbmpX00 = { 0 };
	XBitmap m_xbmpX0A = { 0 };
	
	XBitmap m_xbmpCMD = { 0 };

	XBitmap m_xbmpL0RA = { 0 };
	XBitmap m_xbmpLAR0 = { 0 };
	XBitmap m_xbmpL0R1 = { 0 };
	XBitmap m_xbmpL1R0 = { 0 };

	XItem* m_itemBank = nullptr;
	XItem* m_itemFree = nullptr;
	XItem* m_itemCurr = nullptr;
	XItem* m_itemHead = nullptr;
	XItem* m_itemTail = nullptr;

	HCURSOR m_hCursorHand = nullptr;
	BOOL m_bSetCursor = FALSE;

	int m_itemCount = 0;
	int m_itemIndex = 0;
	int m_scrollOffset = 0;
	int m_offsetX = 0;
	int m_offsetY = 0;
	int m_tabLength = 0;
	int m_tablengthPrev = 0;

	RECT m_rectClient = { 0 };
	RECT m_btnPlus = { 0 };

	UINT m_nDPI = 96;
	float m_deviceScaleFactor = 1.f;
	ID2D1HwndRenderTarget* m_pD2DRenderTarget = nullptr;
	ID2D1SolidColorBrush* m_pTextBrush = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;
	IDWriteInlineObject* m_pEllipsis = nullptr;
public:
	CView()
	{
		XBitmap* bmp;
		U8 id;
		int w, h;
		XItem* p;
		XItem* q;
		size_t bytes = sizeof(XItem);
		bytes *= XITEM_MAX_NUMBER;
		bytes = DUI_ALIGN_PAGE8K(XITEM_MAX_NUMBER * sizeof(XItem));

		m_hCursorHand = ::LoadCursor(NULL, IDC_HAND);

		ATLASSERT(!m_itemBank);
		m_itemBank = (XItem*)malloc(bytes);
		ZeroMemory(m_itemBank, bytes);

		if (!m_pTextFormat)
		{
			g_pDWriteFactory->CreateTextFormat(
				L"Courier New",
				NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				13.5f,
				L"en-US",
				&m_pTextFormat
			);

			if (m_pTextFormat)
			{
				DWRITE_TRIMMING trimmingOptions = {};
				m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

				trimmingOptions.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
				g_pDWriteFactory->CreateEllipsisTrimmingSign(m_pTextFormat, &m_pEllipsis);

			}
		}

		p = m_itemBank;
		for (int i = 0; i < XITEM_MAX_NUMBER - 1; i++)
		{
			q = p + 1;
			p->next = q;
			p = q;
		}

		m_itemFree = m_itemBank;

		m_itemHead = GetFreeItem();
		m_itemCurr = m_itemTail = m_itemHead;
		if (m_itemHead)
		{
			WCHAR title[TITLE_MAX_STRING + 1];
			swprintf((wchar_t*)title, TITLE_MAX_STRING, L"CMD.EXE-[%d]", m_itemIndex++);
			m_itemCount = 1;
			m_itemHead->zorder = ACTIVE_ITEM_ZORDER; // the active item
			m_itemHead->imgNormal = &m_xbmpCMD;
			m_itemHead->imgActive = &m_xbmpCMD;
			size_t length = wcslen(title);
			if (length > TITLE_MAX_STRING - 1)
				length = TITLE_MAX_STRING - 1;

			for (size_t i = 0; i < length; i++) m_itemHead->title[i] = title[i];
			m_itemHead->length = (U8)length;
		}

		id = 0;
		w = 18; h = 30;
		bmp = &m_xbmpLA;
		bmp->data = (U32*)xbmpLA;
		bmp->id = id; bmp->w = w; bmp->h = h;

		bmp = &m_xbmpL0;
		bmp->data = (U32*)xbmpL0;
		bmp->id = id; bmp->w = w; bmp->h = h;

		w = 40; h = 30;
		bmp = &m_xbmpRA;
		bmp->data = (U32*)xbmpRA;
		bmp->id = id; bmp->w = w; bmp->h = h;

		bmp = &m_xbmpR0;
		bmp->data = (U32*)xbmpR0;
		bmp->id = id; bmp->w = w; bmp->h = h;

		id = 0;
		w = 1; h = 30;
		bmp = &m_xbmpTA;
		bmp->data = (U32*)xbmpTA;
		bmp->id = id; bmp->w = w; bmp->h = h;

		bmp = &m_xbmpT0;
		bmp->data = (U32*)xbmpT0;
		bmp->id = id; bmp->w = w; bmp->h = h;

		id = 0;
		w = 16; h = 14;
		bmp = &m_xbmpCMD;
		bmp->data = (U32*)xbmpCMD;
		bmp->id = id; bmp->w = w; bmp->h = h;

		w = 12; h = 12;
		bmp = &m_xbmpXA0; bmp->data = (U32*)xbmpXA0; bmp->id = id; bmp->w = w; bmp->h = h;
		bmp = &m_xbmpXAA; bmp->data = (U32*)xbmpXAA; bmp->id = id; bmp->w = w; bmp->h = h;
		bmp = &m_xbmpX00; bmp->data = (U32*)xbmpX00; bmp->id = id; bmp->w = w; bmp->h = h;
		bmp = &m_xbmpX0A; bmp->data = (U32*)xbmpX0A; bmp->id = id; bmp->w = w; bmp->h = h;

		w = 16; h = 30;
		bmp = &m_xbmpL0RA; bmp->data = (U32*)xbmpL0RA; bmp->id = id; bmp->w = w; bmp->h = h;
		bmp = &m_xbmpLAR0; bmp->data = (U32*)xbmpLAR0; bmp->id = id; bmp->w = w; bmp->h = h;
		bmp = &m_xbmpL0R1; bmp->data = (U32*)xbmpL1R0; bmp->id = id; bmp->w = w; bmp->h = h;
		bmp = &m_xbmpL1R0; bmp->data = (U32*)xbmpL1R0; bmp->id = id; bmp->w = w; bmp->h = h;

	}

	~CView()
	{
		if (m_itemBank)
		{
			free(m_itemBank);
			m_itemBank = nullptr;
			m_itemFree = nullptr;
			m_itemCurr = nullptr;
			m_itemHead = nullptr;
		}

		if (nullptr != m_screenBuff)
			VirtualFree(m_screenBuff, 0, MEM_RELEASE);

		m_screenBuff = nullptr;
		m_screenSize = 0;

		ReleaseUnknown(m_pEllipsis);
		ReleaseUnknown(m_pTextFormat);

	}

	XItem* GetFreeItem()
	{
		XItem* pI = m_itemFree;
		if (m_itemFree)
		{
			m_itemFree = m_itemFree->next;
		}

		if (pI)
		{
			pI->next = nullptr;
			pI->prev = nullptr;
		}
		return pI;
	}

	void FillLeftMost(BOOL active)
	{
		int screenW, screenH;
		XBitmap* bmp = active? &m_xbmpLA : &m_xbmpL0;

		screenW = m_rectClient.right - m_rectClient.left;
		screenH = m_rectClient.bottom - m_rectClient.top;
		ScreenDrawRect(m_screenBuff, screenW, screenH, bmp->data, bmp->w, bmp->h, 0, screenH - bmp->h);
	}

	void FillRightMost(BOOL active)
	{
		int screenW, screenH;
		XBitmap* bmp = active ? &m_xbmpRA : &m_xbmpR0;

		screenW = m_rectClient.right - m_rectClient.left;
		screenH = m_rectClient.bottom - m_rectClient.top;
		ScreenDrawRect(m_screenBuff, screenW, screenH, bmp->data, bmp->w, bmp->h, m_offsetX, screenH - bmp->h);
	}

	void FillItemBody(XItem* pI)
	{
		int screenW, screenH, W, H, offset = 0;
		XBitmap* bmp;
		screenW = m_rectClient.right - m_rectClient.left;
		screenH = m_rectClient.bottom - m_rectClient.top;

		ATLASSERT(pI);

		bmp = (pI->zorder != ACTIVE_ITEM_ZORDER) ? &m_xbmpT0 : &m_xbmpTA;
		H = bmp->h;
		ScreenStretchBlt(m_screenBuff, screenW, screenH,
			bmp->data, bmp->h, m_tabLength, m_offsetX, screenH - H);

		pI->rect.left = m_offsetX;
		pI->rect.right = m_offsetX + m_tabLength;
		pI->rect.top = screenH - H;
		pI->rect.bottom = pI->rect.top + m_xbmpT0.h;

		if (pI->imgNormal)
		{
			bmp = pI->imgNormal;
			offset = (H - bmp->h) >> 1;
			ScreenDrawRect(m_screenBuff, screenW, screenH, bmp->data, bmp->w, bmp->h, m_offsetX, screenH - H + 8);
		}

		bmp = nullptr;
		if (pI->zorder == ACTIVE_ITEM_ZORDER)
		{
			bmp = (pI->status & XITEM_XBUTTON_HIT) ? &m_xbmpXAA : &m_xbmpXA0;
		}
		else
		{
			bmp = (pI->status & XITEM_XBUTTON_HIT) ? &m_xbmpX0A : &m_xbmpX00;
		}

		if (bmp)
		{
			ScreenDrawRect(m_screenBuff, screenW, screenH, bmp->data, bmp->w, bmp->h,
				m_offsetX + m_tabLength - bmp->w, screenH - H + 6);
		}
	}

	void FillGap(XItem* curr, XItem* next, int startPos)
	{
		XBitmap* bmp = nullptr;
		ATLASSERT(curr);
		ATLASSERT(next);

		if (curr->zorder == ACTIVE_ITEM_ZORDER)
		{
			bmp = &m_xbmpLAR0;
		}
		else if(next->zorder == ACTIVE_ITEM_ZORDER)
		{
			bmp = &m_xbmpL0RA;
		}
		else
		{
			if (curr->zorder > next->zorder)
			{
				bmp = &m_xbmpL1R0;
			}
			else if (curr->zorder < next->zorder)
			{
				bmp = &m_xbmpL0R1;
			}
			else // curr->zorder == next->zorder
			{
				ATLASSERT(0);
			}
		}

		if (bmp)
		{
			int screenW, screenH;
			screenW = m_rectClient.right - m_rectClient.left;
			screenH = m_rectClient.bottom - m_rectClient.top;
			ScreenDrawRect(m_screenBuff, screenW, screenH, bmp->data, bmp->w, bmp->h, startPos, screenH - bmp->h);
		}
	}

	void FillPlusButton()
	{

	}

	void UpdateTabs()
	{
		const unsigned int bottomLine[1 * 5] =
		{
		0xFF8C4F2E,
		0xFFF9F8F9,
		0xFFF9F9F8,
		0xFFF8F7F7,
		0xFFF8F7F7
		};

		int screenW = m_rectClient.right - m_rectClient.left;
		int screenH = m_rectClient.bottom - m_rectClient.top;
		XItem* p = m_itemHead;
		m_offsetX = 0;

		ScreenStretchBlt(m_screenBuff, screenW, screenH, (U32*)bottomLine, 5, screenW, m_offsetX, screenH - 5);

		while (p)
		{
			if (!p->prev) // p is pointing to the left-most node
			{
				if (p->zorder != ACTIVE_ITEM_ZORDER)
					FillLeftMost(FALSE);
				else
					FillLeftMost(TRUE);
				m_offsetX += m_xbmpLA.w;
			}

			FillItemBody(p);
			m_offsetX += m_tabLength;

			if (p->next)
			{
				FillGap(p, p->next, m_offsetX);
				m_offsetX += m_xbmpL0RA.w;
			}
			else // p is pointing to the right-most node
			{
				if (p->zorder != ACTIVE_ITEM_ZORDER)
					FillRightMost(FALSE);
				else
					FillRightMost(TRUE);
				m_offsetX += m_xbmpRA.w;

				m_btnPlus.left  = m_offsetX - 20;
				m_btnPlus.right = m_offsetX - 12;
				m_btnPlus.bottom = 20;
				m_btnPlus.top = 12;
			}
			p = p->next;
		}

		FillPlusButton();
	}

	void SwitchItem(XItem* next)
	{
		U32 zleft = 0, zright = 0;
		XItem* p;
		ATLASSERT(m_itemCurr);
		ATLASSERT(m_itemCurr->zorder == ACTIVE_ITEM_ZORDER);
		ATLASSERT(next);

		p = m_itemCurr->prev;
		if (p)
		{
			if(p->zorder != ACTIVE_ITEM_ZORDER)
				zleft = p->zorder;

		}
		p = m_itemCurr->next;
		if (p)
		{
			if (p->zorder != ACTIVE_ITEM_ZORDER)
				zright = p->zorder;
		}

		m_itemCurr->zorder = std::max(zleft, zright) + 1;

		next->zorder = ACTIVE_ITEM_ZORDER;
		m_itemCurr = next;
	}

	int FillScreen(U32* dst, U16 width, U16 height, U32 color)
	{
		// because using pointer 64 bit is 2 times faster than pointer 32 bit
		// so we use pointer 64 to speed up the copying
		if (dst)
		{
			U32 i, half_size, size;
			U64* p64 = (U64*)dst;
			U64 newColor = (((U64)(color)) << 32) | ((U64)color);

			size = width * height;
			half_size = (size >> 1);

			for (i = 0; i < half_size; i++)
				*p64++ = newColor;

			if (1 & size)  // fix the last pixel if the whole size is not even number
			{
				U32* p32 = dst + (size - 1);
				*p32 = color;
			}
		}
		return 0;
	}

	int ScreenDrawRect(U32* dst, int w, int h, U32* src, int sw, int sh, int dx, int dy)
	{
		if (dst && src)
		{
			U32* startDST;
			U32* startSRC;
			U32* p;
			int SW, SH;

			if (dx >= w || dy >= h) // not in the scope
				return 1;

			if (dy < 0)
			{
				src += ((-dy) * sw);
				sh += dy;
				dy = 0;
			}

			SW = sw;
			SH = sh;

			if (sw + dx > w)
				SW = w - dx;
			if (sh + dy > h)
				SH = h - dy;

			for (int i = 0; i < SH; i++)
			{
				startDST = dst + w * (dy + i) + dx;
				startSRC = src + i * sw;
				for (int k = 0; k < SW; k++)
					*startDST++ = *startSRC++;
			}
		}
		return 0;
	}

	int ScreenStretchBlt(U32* dst, int w, int h, U32* src, int sh, int len, int dx, int dy)
	{
		if (dst && src)
		{
			U32* startDST;
			U32* startSRC;
			U32* p;
			int SW, SH;

			if (dx < 0 || dx >= w || dy >= h) // not in the scope
				return 1;

			if (dy < 0)
			{
				src += ((-dy) * 1);
				sh += dy;
				dy = 0;
			}

			if (dx + len > w)
				len = w - dx;

			for (int i = 0; i < sh; i++)
			{
				startDST = dst + w * (dy + i) + dx;
				startSRC = src + i;
				for (int k = 0; k < len; k++)
					*startDST++ = *startSRC;
			}
		}
		return 0;
	}

public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CView)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDM_COMMAND_EXE, OnCmdEXE)
	END_MSG_MAP()

	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// handled, no background painting needed
		return 1;
	}

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT ptCursor = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		XItem* q = m_itemHead;

		while (q)
		{
			if (::PtInRect(&q->rect, ptCursor))
			{
				break;
			}
			q = q->next;
		}

		if (q)
		{
			RECT xr = { 0 };
			xr.right = q->rect.right;
			xr.left = xr.right - m_xbmpXA0.w;
			xr.top = q->rect.top + 6;
			xr.bottom = xr.top + m_xbmpXA0.h;
			if (::PtInRect(&xr, ptCursor))
			{
				MessageBox(L"Are you sure to close this session?", L"Close Session", MB_YESNO);
				q->status &= ~XITEM_XBUTTON_HIT;
				Invalidate();
			}
			else if(q != m_itemCurr)
			{
				SwitchToTab(q, true);
			}
		}

		return 0;
	}

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT ptCursor = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

		if (::PtInRect(&m_btnPlus, ptCursor))
		{
			NMCTCITEM nmh =
			{
				{m_hWnd, 0,CTCN_PLUSBUTTON},
				0, {-1,-1}
			};

			m_bSetCursor = TRUE;
			::SetCursor(m_hCursorHand);
			::SendMessage(GetParent(), WM_NOTIFY, nmh.hdr.idFrom, (LPARAM)&nmh);
		}

		return 0;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bNeedUpdate = FALSE;
		POINT ptCursor = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		XItem* q = m_itemHead;

		while (q)
		{
			if (q->status & XITEM_XBUTTON_HIT)
				bNeedUpdate = TRUE;

			q->status = 0;
			if (::PtInRect(&q->rect, ptCursor))
			{
				break;
			}
			q = q->next;
		}

		if (q)
		{
			RECT xr = { 0 };
			xr.right = q->rect.right;
			xr.left = xr.right - m_xbmpXA0.w;
			xr.top = q->rect.top + 6;
			xr.bottom = xr.top + m_xbmpXA0.h;
			if (::PtInRect(&xr, ptCursor))
			{
				q->status |= XITEM_XBUTTON_HIT;
				bNeedUpdate = TRUE;
			}
		}

		if (::PtInRect(&m_btnPlus, ptCursor))
		{
			m_bSetCursor = TRUE;
			::SetCursor(m_hCursorHand);
		}

		if(bNeedUpdate)
			Invalidate();

		return 0;
	}

	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (((HWND)wParam == m_hWnd) && (LOWORD(lParam) == HTCLIENT))
		{
			if (m_bSetCursor)
			{
				m_bSetCursor = FALSE;
				return 1;
			}
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		ReleaseUnknown(m_pTextBrush);
		ReleaseUnknown(m_pD2DRenderTarget);
		return 1;
	}

	void DoItemTextLayout(XItem* item)
	{
		if (item)
		{
			DWRITE_TRIMMING trimmingOptions = {};
			trimmingOptions.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;

			ReleaseUnknown(item->pTextLayout);
			if (item->length)
			{
				g_pDWriteFactory->CreateTextLayout(
					item->title,
					item->length,
					m_pTextFormat,
					m_tabLength - m_xbmpXA0.w - m_xbmpCMD.w,
					1.0f, // arbitrary height, as we only care about width here
					&item->pTextLayout
				);
			}

			if (item->pTextLayout)
			{
				item->pTextLayout->SetTrimming(&trimmingOptions, m_pEllipsis);
			}
		}
	}

	void DoTextLayout()
	{
		DWRITE_TRIMMING trimmingOptions = {};
		trimmingOptions.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;

		XItem* q = m_itemHead;
		while (q)
		{
			ReleaseUnknown(q->pTextLayout);
			if (q->length)
			{
				g_pDWriteFactory->CreateTextLayout(
					q->title,
					q->length,
					m_pTextFormat,
					m_tabLength - m_xbmpXA0.w - m_xbmpCMD.w,
					1.0f, // arbitrary height, as we only care about width here
					&q->pTextLayout
				);
			}

			if (q->pTextLayout)
			{
				q->pTextLayout->SetTrimming(&trimmingOptions, m_pEllipsis);
			}
			q = q->next;
		}
	}

	void DrawTabText()
	{
		XItem* q = m_itemHead;
		while (q)
		{
			if (q->pTextLayout)
			{
				m_pD2DRenderTarget->DrawTextLayout(
					D2D1::Point2F(q->rect.left + m_xbmpCMD.w + 2, q->rect.top + 8),
					q->pTextLayout, m_pTextBrush);

			}
			q = q->next;
		}
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ReleaseUnknown(m_pD2DRenderTarget);

		GetClientRect(&m_rectClient);
		int w = m_rectClient.right - m_rectClient.left;
		int h = m_rectClient.bottom - m_rectClient.top;

		if (nullptr != m_screenBuff)
		{
			VirtualFree(m_screenBuff, 0, MEM_RELEASE);
		}
		m_screenBuff = nullptr;
		m_screenSize = 0;

		m_screenSize = DUI_ALIGN_PAGE(w * h * sizeof(U32));
		ATLASSERT(m_screenSize >= (w * h * sizeof(U32)));
		if (m_screenSize)
		{
			m_screenBuff = (U32*)VirtualAlloc(NULL, m_screenSize, MEM_COMMIT, PAGE_READWRITE);
		}

		if (m_screenBuff)
		{
			ATLASSERT(m_itemCount > 0);
			int exalength = m_xbmpLA.w + m_xbmpRA.w + (m_itemCount - 1) * m_xbmpL0RA.w;
			int sumlength = w - SPECIAL_LENGTH;
			int tablength = (sumlength - exalength) / m_itemCount;

			if (tablength > TAB_MAX_LENGTH)
				tablength = TAB_MAX_LENGTH;
			if(tablength < TAB_MIN_LENGTH)
				tablength = TAB_MIN_LENGTH;

			m_tabLength = tablength;
			if (m_tablengthPrev != m_tabLength)
			{
				m_tablengthPrev = m_tabLength;
				DoTextLayout();
			}

			FillScreen(m_screenBuff, (U16)w, (U16)h, 0xFFCD7949);
		}
		Invalidate();

		return 0;
	}

	D2D1_SIZE_U GetSizeUFromRect(const RECT& rc, const int scaleFactor) noexcept
	{
		const long width = rc.right - rc.left;
		const long height = rc.bottom - rc.top;
		const UINT32 scaledWidth = width * scaleFactor;
		const UINT32 scaledHeight = height * scaleFactor;
		return D2D1::SizeU(scaledWidth, scaledHeight);
	}

	int GetFirstIntegralMultipleDeviceScaleFactor() const noexcept
	{
		return static_cast<int>(std::ceil(m_deviceScaleFactor));
	}

	HRESULT CreateDeviceDependantResource(int left, int top, int right, int bottom)
	{
		HRESULT hr = S_OK;
		if (nullptr == m_pD2DRenderTarget)  // Create a Direct2D render target.
		{
			RECT rc;
			const int integralDeviceScaleFactor = GetFirstIntegralMultipleDeviceScaleFactor();
			D2D1_RENDER_TARGET_PROPERTIES drtp{};
			drtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
			drtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
			drtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
			drtp.dpiX = 96.f * integralDeviceScaleFactor;
			drtp.dpiY = 96.f * integralDeviceScaleFactor;
			// drtp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN);
			drtp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE);

			rc.left = left; rc.top = top; rc.right = right; rc.bottom = bottom;
			D2D1_HWND_RENDER_TARGET_PROPERTIES dhrtp{};
			dhrtp.hwnd = m_hWnd;
			dhrtp.pixelSize = GetSizeUFromRect(rc, integralDeviceScaleFactor);
			dhrtp.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

			ATLASSERT(nullptr != g_pD2DFactory);

			//hr = g_pD2DFactory->CreateHwndRenderTarget(renderTargetProperties, hwndRenderTragetproperties, &m_pD2DRenderTarget);
			hr = g_pD2DFactory->CreateHwndRenderTarget(drtp, dhrtp, &m_pD2DRenderTarget);
			if (S_OK == hr && m_pD2DRenderTarget)
			{
				hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pTextBrush);
			}
		}

		return hr;
	}


	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		PAINTSTRUCT ps;
		BeginPaint(&ps);

		RECT rc;
		GetClientRect(&rc);
		HRESULT hr = CreateDeviceDependantResource(rc.left, rc.top, rc.right, rc.bottom);

		if (S_OK == hr && m_pD2DRenderTarget)
		{
			m_pD2DRenderTarget->BeginDraw();
			////////////////////////////////////////////////////////////////////////////////////////////////////
			//m_pD2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			//m_pD2DRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::LightBlue));
			if (m_screenBuff)
			{
				ID2D1Bitmap* pBitmap = nullptr;
				int w = m_rectClient.right - m_rectClient.left;
				int h = m_rectClient.bottom - m_rectClient.top;

				UpdateTabs();

				hr = m_pD2DRenderTarget->CreateBitmap(D2D1::SizeU(w, h), m_screenBuff, (w << 2),
					D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)), &pBitmap);

				if (S_OK == hr && nullptr != pBitmap)
				{
					D2D1_RECT_F rect = D2D1::RectF(
						static_cast<FLOAT>(m_rectClient.left),
						static_cast<FLOAT>(m_rectClient.top),
						static_cast<FLOAT>(m_rectClient.right),
						static_cast<FLOAT>(m_rectClient.bottom)
					);

					m_pD2DRenderTarget->PushAxisAlignedClip(rect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

					m_pD2DRenderTarget->DrawBitmap(pBitmap, &rect); // do the real draw
					ReleaseUnknown(pBitmap);
					m_pD2DRenderTarget->PopAxisAlignedClip();
				}
				DrawTabText();
			}

			hr = m_pD2DRenderTarget->EndDraw();
			////////////////////////////////////////////////////////////////////////////////////////////////////
			if (FAILED(hr) || D2DERR_RECREATE_TARGET == hr)
			{
				ReleaseUnknown(m_pD2DRenderTarget);
			}
		}

		EndPaint(&ps);
		return 0;
	}

	void SwitchToTab(XItem* newItem, bool bUpdate = false)
	{
		int zleft = 0;
		int zright = 0;

		ATLASSERT(newItem);
		ATLASSERT(m_itemCurr);

		XItem* q = m_itemCurr;

		if (q->prev)
			zleft = q->prev->zorder;
		if (q->next)
			zright = q->next->zorder;
		q->zorder = std::max(zleft, zright) + 1;

		m_itemCurr = newItem;
		m_itemCurr->zorder = ACTIVE_ITEM_ZORDER; // the active item

		if (bUpdate)
		{
			Invalidate();
		}
	}

	void ShowDropDownMenu()
	{
		POINT cursorpos = {};
		GetCursorPos(&cursorpos);

		HMENU hMenu = CreatePopupMenu();

		AppendMenu(hMenu, MF_STRING | MF_ENABLED, IDM_COMMAND_EXE, L"CMD.EXE");
		AppendMenu(hMenu, MF_STRING | MF_ENABLED, IDM_POWER_SHELL, L"POWER SHELL");

		TrackPopupMenu(hMenu,TPM_LEFTALIGN | TPM_TOPALIGN | TPM_VERTICAL,
			cursorpos.x, cursorpos.y + 10,
			0, m_hWnd, NULL);

	}

	void AddNewTab()
	{
		XItem* p = GetFreeItem();
		if (p)
		{
			int zleft = 0;
			int zright = 0;
			XItem* q = m_itemCurr;
			ATLASSERT(q);

			if (q->prev)
				zleft = q->prev->zorder;
			if (q->next)
				zright = q->next->zorder;
			q->zorder = std::max(zleft, zright) + 1;

			ATLASSERT(m_itemTail);
			m_itemTail->next = p;
			p->prev = m_itemTail;
			m_itemCount++;
			m_itemCurr = m_itemTail = p;
			m_itemCurr->zorder = ACTIVE_ITEM_ZORDER; // the active item
			m_itemCurr->imgNormal = &m_xbmpCMD;
			m_itemCurr->imgActive = &m_xbmpCMD;
			{
				WCHAR title[TITLE_MAX_STRING + 1];
				swprintf((wchar_t*)title, TITLE_MAX_STRING, L"CMD.EXE-[%d]", m_itemIndex++);
				size_t length = wcslen(title);
				if (length > TITLE_MAX_STRING)
					length = TITLE_MAX_STRING;

				for (size_t i = 0; i < length; i++)
					m_itemCurr->title[i] = title[i];
				m_itemCurr->length = (U8)length;
				
			}

			{
				int w = m_rectClient.right - m_rectClient.left;
				int exalength = m_xbmpLA.w + m_xbmpRA.w + (m_itemCount - 1) * m_xbmpL0RA.w;
				int sumlength = w - SPECIAL_LENGTH;
				int tablength = (sumlength - exalength) / m_itemCount;

				if (tablength > TAB_MAX_LENGTH)
					tablength = TAB_MAX_LENGTH;
				if (tablength < TAB_MIN_LENGTH)
					tablength = TAB_MIN_LENGTH;

				m_tabLength = tablength;
				if (m_tablengthPrev != m_tabLength)
				{
					m_tablengthPrev = m_tabLength;
					DoTextLayout();
				}
				else
				{
					DoItemTextLayout(m_itemCurr);
				}
			}

			Invalidate();
		}
	}

	LRESULT OnCmdEXE(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		AddNewTab();
		return 0;
	}

};
