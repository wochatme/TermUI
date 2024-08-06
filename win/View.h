// View.h : interface of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

// a pure 32-bit true color bitmap object
typedef struct XBitmap
{
	U8    id;
	U32* data;
	int   w;
	int   h;
} XBitmap;

typedef struct XItem XItem;
struct XItem
{
	XItem* prev;
	XItem* next;
	U32 zorder;
	LPWSTR	title;
	XBitmap* imgNormal;
	XBitmap* imgHover;
	XBitmap* imgPress;
	XBitmap* imgActive;
};

/* fill the whole screen with one color */
int DUI_ScreenClear(U32* dst, U32 size, U32 color)
{
	uint32_t i, half_size;
	uint64_t newColor;
	uint64_t* p64;

	if (NULL == dst)
		return 1;

	newColor = (((uint64_t)(color)) << 32) | ((uint64_t)color);

	// because using pointer 64 bit is 2 times faster than pointer 32 bit
	// so we use pointer 64 to speed up the copying
	p64 = (uint64_t*)dst;
	half_size = (size >> 1);

	for (i = 0; i < half_size; i++)
		*p64++ = newColor;

	if (1 & size)  // fix the last pixel if the whole size is not even number
	{
		uint32_t* p32 = dst + (size - 1);
		*p32 = color;
	}

	return 0;
}

class CView : public CWindowImpl<CView>
{
	U32* m_screenBuff = nullptr;
	U32  m_screenSize = 0;

	RECT m_rectClient = { 0 };

	UINT m_nDPI = 96;
	float m_deviceScaleFactor = 1.f;
	ID2D1HwndRenderTarget* m_pD2DRenderTarget = nullptr;
public:
	CView()
	{

	}

	~CView()
	{
		if (nullptr != m_screenBuff)
			VirtualFree(m_screenBuff, 0, MEM_RELEASE);

		m_screenBuff = nullptr;
		m_screenSize = 0;
	}

public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	END_MSG_MAP()

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		ReleaseUnknown(m_pD2DRenderTarget);
		return 1;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ReleaseUnknown(m_pD2DRenderTarget);

		GetClientRect(&m_rectClient);
#if 0
		ATLASSERT(0 == m_rectClient.left);
		ATLASSERT(0 == m_rectClient.top);
		ATLASSERT(m_rectClient.right > 0);
		ATLASSERT(m_rectClient.bottom > 0);
#endif 
		U32 w = (U32)(m_rectClient.right - m_rectClient.left);
		U32 h = (U32)(m_rectClient.bottom - m_rectClient.top);

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
			DUI_ScreenClear(m_screenBuff, w * h, 0xFF0000FF);
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
};
