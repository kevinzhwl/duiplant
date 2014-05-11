#pragma once

#include <assert.h>

namespace DuiEngine
{
	void DUI_EXP DuiHiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix);
	void DUI_EXP DuiPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric);
	void DUI_EXP DuiTraceA(LPCSTR pstrFormat, ...);
	void DUI_EXP DuiTraceW(LPCWSTR pstrFormat, ...);
}//end of namespace DuiEngine

#ifdef _UNICODE
#define DUITRACE DuiTraceW
#else
#define DUITRACE DuiTraceA
#endif

#define DUIASSERT(x) assert(x)
#define DUIASSERT_NE(a,b) DUIASSERT(a!=b)

#ifdef _DUI_DISABLE_NO_VTABLE
#define DUI_NO_VTABLE
#else
#define DUI_NO_VTABLE __declspec(novtable)
#endif