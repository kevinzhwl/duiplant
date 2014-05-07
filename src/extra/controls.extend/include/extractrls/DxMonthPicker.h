#ifndef __DXMINICALENDAR_H__
#define __DXMINICALENDAR_H__

#include <atltime.h>
#include <atlcomtime.h>

#include <dui/DxWindow.h>
#include <dui/DxCommonCtrl.h>

class CDxMonthPicker;
//---------------------------------------------------------------------------
const UINT XTP_NC_DATEPICKER_BUTTON_CLICK      = (NM_FIRST - 50);  // Notify ID to parent window.
const UINT XTP_NC_DATEPICKER_SELECTION_CHANGED = (NM_FIRST - 51);  // Notify ID to parent window.

class CDxDatePickerMonth;
// ----------------------------------------------------------------------
class CDxDatePickerButton
{
    friend class CDxMonthPicker;

public:
    CDxDatePickerButton();
    virtual ~CDxDatePickerButton()
    {
    }

    virtual CString     GetCaption() const;
    virtual void        SetCaption(LPCTSTR pcszCaption);

public:
    //  This member variable is used to specify the identifier of the button. Also it used as resource ID for a caption string.
    int                 m_nID;
    //  This member variable is used to specify the bounding rectangle coordinates of a button.
    CRect               m_rcButton;

    BOOL                m_bVisible;        // This member variable is used to indicate if a button is visible.

    BOOL                m_bPressed;        // This member variable is used to indicate if a button is pressed.

    BOOL                m_bHighlight;      // This member variable is used to indicate if a button is highlighted.

protected:
    //  This member variable is used to specify the caption of the button.
    CString             m_strCaption;
};

//===========================================================================
class CDxDatePickerDay
{
public:
    CDxDatePickerDay(CDxMonthPicker* pControl, CDxDatePickerMonth* pMonth, COleDateTime dtDay);
    virtual ~CDxDatePickerDay();

    virtual void        Draw(CDCHandle dc);
    BOOL                DrawDay(CDCHandle dc);
    void                SetRect(const CRect& rcDay);
    CRect               GetRect() const;
    COleDateTime        GetDate() const;
    BOOL                IsVisible() const;
    BOOL                IsToday(COleDateTime &dt) const;

    CDxDatePickerMonth* GetMonth() const;
    CDxMonthPicker*      GetDatePicker() const;

protected:
    CDxMonthPicker*      m_pControl;
    CDxDatePickerMonth* m_pMonth;
    COleDateTime        m_dtDay;
    CRect               m_rcDay;
    BOOL                m_bVisible;

protected:
    friend class CDxMonthPicker;
};

//===========================================================================
class CDxDatePickerMonth
{
    friend class CDxMonthPicker;

public:
    CDxDatePickerMonth(CDxMonthPicker* pControl, COleDateTime dtMonth);
    virtual ~CDxDatePickerMonth();

    void                AdjustLayout(CRect rcClient);
    virtual void        Draw(CDCHandle dc);
    COleDateTime        GetMonth() const;
    BOOL                GetShowDaysBefore() const;

    BOOL                GetShowDaysAfter() const;
    void                SetShowDaysBefore(BOOL bShow);
    void                SetShowDaysAfter(BOOL bShow);
    BOOL                GetShowLeftScroll() const;
    BOOL                GetShowRightScroll() const;
    void                SetShowScrolling(BOOL bLeftScroll, BOOL bRightScroll);
    CDxDatePickerDay*   GetDay(int nIndex) const;
    int                 GetDayCount() const;
    void                DrawMonthHeader(CDCHandle dc);
    void                DrawDaysOfWeek(CDCHandle dc);
    CDxDatePickerDay*   HitTest(CPoint point, BOOL bCheckVisible = TRUE) const;

protected:
    void                DrawScrollTriangle(CDCHandle dc, CRect rcSpot, BOOL bLeftDirection, COLORREF clrColor = 0, BOOL bYears = FALSE);
    void                Triangle(CDCHandle dc, CPoint pt0, CPoint pt1, CPoint pt2, COLORREF clrColor);

    void                ClearDays();
    void                PopulateDays();
    void                OnLButtonDown(UINT nFlags, CPoint point);
    void                OnLButtonUp(UINT nFlags, CPoint point);
    void                AutoAdjustLayout(CRect rcClient);

protected:
    typedef CAtlArray<CDxDatePickerDay*> ArrayDays;

    CDxMonthPicker*      m_pControl;

    COLORREF            m_clrStaticBorder;
    COLORREF            m_clrDaysOfWeekBack;
    COLORREF            m_clrDaysOfWeekText;
    COLORREF            m_clrMonthBorder;
    COLORREF            m_clrWeekNumbersBack;
    COLORREF            m_clrWeekNumbersText;
    COLORREF            m_clrMonthHeaderBack;
    COLORREF            m_clrMonthHeaderText;
    COLORREF            m_clrMonthHeaderButton;

    COleDateTime        m_dtMonth;
    BOOL                m_bShowDaysBefore;
    BOOL                m_bShowDaysAfter;
    BOOL                m_bShowLeftScroll;
    BOOL                m_bShowRightScroll;
    CRect               m_rcMonth;
    CRect               m_rcHeader;
    CRect               m_rcDaysOfWeek;
    CRect               m_rcWeekNumbers;
    CRect               m_rcDaysArea;
    CRect               m_rcLeftScroll;
    CRect               m_rcRightScroll;
    ArrayDays           m_arrDays;

private:
    static void         Swap(COleDateTime& dtFirst, COleDateTime& dtSecond);
};

/////////////////////////////////////////////////////////////////////////////
//  CDxMonthPicker window
class CDxMonthPicker : public CDxWindow
{
    DXOBJ_DECLARE_CLASS_NAME(CDxMonthPicker, "monthpicker")

    friend class CDxDatePickerMonth;

public:
    enum DatePickerMouseMode
    {
        mouseNothing,            // No mouse activity by the user.
        mouseScrollingLeft,      // User pressed left scroll triangle and is holding the button.
        mouseScrollingRight,     // User pressed right scroll triangle and is holding the button.
        mouseSelecting,          // User pressed left mouse down on unselected day item and is now selecting a range of day items.
        mouseDeselecting,        // User pressed left mouse down on selected day item and is now de-selecting a range of day items.
        mouseTrackingHeaderList  // User is tracking pop-up month list window.
    };

public:
    CDxMonthPicker();
    virtual ~CDxMonthPicker();

    void                SetFirstDayOfWeek(int nDay);
    int                 GetFirstDayOfWeek() const;
    void                SetFirstWeekOfYearDays(int nDays);
    int                 GetFirstWeekOfYearDays() const;

    virtual void        ScrollLeft(int nMonthCount = 1);
    virtual void        ScrollRight(int nMonthCount = 1);

    virtual BOOL        IsSelected(const COleDateTime& dtDay) const;
    virtual void        Select(const COleDateTime& dtDay);
    virtual void        EnsureVisible(const COleDateTime& dtDate);

    CString             GetMonthName(int nMonth) const;
    CString             GetDayOfWeekName(int nDayOfWeek) const;

    int                 GetMonthDelta() const;
    virtual BOOL        GetCurSel(COleDateTime& refDateTime) const;
    virtual BOOL        SetCurSel(const COleDateTime& refDateTime);
    virtual BOOL        GetToday(COleDateTime& refDateTime) const;
    virtual void        SetToday(const COleDateTime& refDateTime);
    virtual void        AddButton();
    virtual void        AdjustLayout();

protected:
    virtual void        InitNames();
    virtual void        Populate();
    virtual void        CreateMonth();
    virtual void        DrawButtons(CDCHandle dc);
    virtual void        AdjustLayout(CRect rcClient);
    virtual CSize       CalcButtonSize() const;
    virtual void        SetButtonRect();
    virtual void        CalcButtonBandRect();
    virtual void        ProcessButtons(CPoint point);
    static BOOL         ShiftDate(COleDateTime &refDate, int nMonthCount);
    virtual void        OnButtonClick(UINT nID);

protected:
    void                OnLButtonDown(UINT nFlags, CPoint point);
    void                OnLButtonUp(UINT nFlags, CPoint point);
    void                OnPaint(CDCHandle dc);
    int                 OnCreate(LPVOID);
    void                OnSize(UINT nType, CSize);

public:
    COLORREF            m_clrControlBack;
    //  This member variable is used to specify the current Mouse operating mode.
    DatePickerMouseMode m_mouseMode;

    int                 m_nTimerID;                 // This member variable is used to specify the control timer ID.

    CRect               m_rcControl;  // This data member is used to store the control drawing coordinates.

    COleDateTime        m_dtMinRange;      // This member variable specifies the minimum allowable date for a date picker control.
    COleDateTime        m_dtMaxRange;      // This member variable specifies the maximum allowable date for a date picker control.
    COleDateTime        m_dtToday;         // This member variable is used to specify the "Today" date for a date picker control.
    COleDateTime        m_dtFirstMonth;    // This member variable is used to specify the first month in the grid.
    int                 m_nFirstDayOfWeek;          // This member variable is used to specify the first day of the week to display (1-Sunday, 2-Monday ... etc).
    int                 m_nFirstWeekOfYearDays;     // This member variable is used to specify the number of days of the new year in the first week of this year.

    int                 m_nMonthDelta;          // This member variable is used to specify the number of months set

    // before starting the mouse selection.
    BOOL                m_bSelectWeek;         // TRUE when user is started selecting the whole week.

    CDxDatePickerMonth* m_monthPicker;

    COleDateTime        m_dtFSelBase;  // This member variable is used to specify start day of the continuous selection. Used only for keyboard navigation and selecting.

    CString*            m_arMonthNames;    // This member variable contains the localized month names values.
    CString*            m_arDayOfWeekNames;// This member variable contains the day abbreviation for drawing in the month header.

    CRect               m_rcGrid;             // Months grid rect.

    CDxDatePickerButton* m_btnToday;  // Pointer to a date picker button
    CDxDatePickerButton* m_btnCaptured;  // Pointer to a date picker button

    BOOL                m_bYearsTriangle;          //use extra button for 1 year jump
    CString             m_strYearMonthFormat;   //The year month format.

protected:
    DXWIN_BEGIN_MSG_MAP()
        MSG_WM_CREATE(OnCreate)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_SIZE(OnSize)
    DXWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
inline void CDxMonthPicker::SetFirstDayOfWeek(int nDay)
{
    ATLASSERT(nDay >= 1 && nDay <= 7);
    if (nDay >= 1 && nDay <= 7 && nDay != m_nFirstDayOfWeek)
    {
        m_nFirstDayOfWeek = nDay;
        Populate();
    }
}

inline int CDxMonthPicker::GetFirstDayOfWeek() const
{
    return m_nFirstDayOfWeek;
}

inline void CDxMonthPicker::SetFirstWeekOfYearDays(int nDays)
{
    ATLASSERT(nDays >= 1 && nDays <= 7);
    if (nDays >= 1 && nDays <= 7 && nDays != m_nFirstWeekOfYearDays)
    {
        m_nFirstWeekOfYearDays = nDays;
        NotifyInvalidate();
    }
}

inline int CDxMonthPicker::GetFirstWeekOfYearDays() const
{
    return m_nFirstWeekOfYearDays;
}

inline CString CDxMonthPicker::GetMonthName(int nMonth) const
{
    return nMonth >= 1 && nMonth <= 12 ? m_arMonthNames[nMonth - 1] : _T("");
}

inline CString CDxMonthPicker::GetDayOfWeekName(int nDayOfWeek) const
{
    return nDayOfWeek >= 1 && nDayOfWeek <= 7 ? m_arDayOfWeekNames[nDayOfWeek - 1] : _T("");
}

inline int CDxMonthPicker::GetMonthDelta() const
{
    return 1;
}

inline BOOL CDxMonthPicker::GetToday(COleDateTime& refDateTime) const
{
    refDateTime = m_dtToday;
    return TRUE;
}

inline void CDxMonthPicker::AdjustLayout()
{
    InitNames();
    AdjustLayout(m_rcControl);
}

inline COleDateTime CDxDatePickerMonth::GetMonth() const
{
    return m_dtMonth;
}

inline BOOL CDxDatePickerMonth::GetShowDaysBefore() const
{
    return m_bShowDaysBefore;
}

inline BOOL CDxDatePickerMonth::GetShowDaysAfter() const
{
    return m_bShowDaysAfter;
}

inline void CDxDatePickerMonth::SetShowDaysBefore(BOOL bShow)
{
    m_bShowDaysBefore = bShow;
}

inline void CDxDatePickerMonth::SetShowDaysAfter(BOOL bShow)
{
    m_bShowDaysAfter = bShow;
}

inline BOOL CDxDatePickerMonth::GetShowLeftScroll() const
{
    return m_bShowLeftScroll;
}

inline BOOL CDxDatePickerMonth::GetShowRightScroll() const
{
    return m_bShowRightScroll;
}

inline void CDxDatePickerMonth::SetShowScrolling(BOOL bLeftScroll, BOOL bRightScroll)
{
    m_bShowLeftScroll = bLeftScroll;
    m_bShowRightScroll = bRightScroll;
}

inline void CDxDatePickerMonth::Swap(COleDateTime& dtFirst, COleDateTime& dtSecond)
{
    COleDateTime dtTemp = dtFirst;
    dtFirst = dtSecond;
    dtSecond = dtTemp;
}

inline void CDxDatePickerDay::SetRect(const CRect& rcDay)
{
    m_rcDay = rcDay;
}

inline CRect CDxDatePickerDay::GetRect() const
{
    return m_rcDay;
}

inline COleDateTime CDxDatePickerDay::GetDate() const
{
    return m_dtDay;
}

inline BOOL CDxDatePickerDay::IsVisible() const
{
    return m_bVisible;
}

inline CDxDatePickerMonth* CDxDatePickerDay::GetMonth() const
{
    return m_pMonth;
}

inline CDxMonthPicker* CDxDatePickerDay::GetDatePicker() const
{
    return m_pControl;
}

#endif  //  __DXMINICALENDAR_H__

