#pragma once

#define S8      int8_t
#define S16     int16_t
#define S32     int32_t
#define S64     int64_t

#define U8      uint8_t
#define U16     uint16_t
#define U32     uint32_t
#define U64     uint64_t

/* DUI_ALIGN() is only to be used to align on a power of 2 boundary */
#define DUI_ALIGN(size, boundary)   (((size) + ((boundary) -1)) & ~((boundary) - 1))
#define DUI_ALIGN_DEFAULT32(size)   DUI_ALIGN(size, 4)
#define DUI_ALIGN_DEFAULT64(size)   DUI_ALIGN(size, 8)      /** Default alignment */
#define DUI_ALIGN_PAGE(size)        DUI_ALIGN(size, (1<<16))
#define DUI_ALIGN_TRUETYPE(size)    DUI_ALIGN(size, 64)    

#define TAB_WINDOW_HEIGHT		32

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

extern ID2D1Factory* g_pD2DFactory;
extern IDWriteFactory* g_pDWriteFactory;

/// Find a function in a DLL and convert to a function pointer.
/// This avoids undefined and conditionally defined behaviour.
template<typename T>
inline T DLLFunction(HMODULE hModule, LPCSTR lpProcName) noexcept
{
	if (!hModule)
	{
		return nullptr;
	}
	FARPROC function = ::GetProcAddress(hModule, lpProcName);
	static_assert(sizeof(T) == sizeof(function));

	T fp{};
	memcpy(&fp, &function, sizeof(T));

	return fp;
}

// Release an IUnknown* and set to nullptr.
// While IUnknown::Release must be noexcept, it isn't marked as such so produces
// warnings which are avoided by the catch.
template <class T>
inline void ReleaseUnknown(T*& ppUnknown) noexcept
{
	if (ppUnknown)
	{
		try
		{
			ppUnknown->Release();
		}
		catch (...)
		{
			// Never occurs
		}
		ppUnknown = nullptr;
	}
}
