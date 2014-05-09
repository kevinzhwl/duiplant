#pragma once

#include <ATLComTime.h>
#include <dui/extractrls/DxRichEdit.h>

//===========================================================================
// Summary:
//     CDxMaskEdit is a CXTPEdit derived class. It allows text masking to be
//     applied to the control to format it for special editing restrictions.
//===========================================================================
class CDxMaskEdit : public CDxLineEdit
{
    DXOBJ_DECLARE_CLASS_NAME(CDxMaskEdit, "maskedit")

public:
    CDxMaskEdit();

    BOOL            CanUseMask() const;
    void            SetUseMask(BOOL bUseMask);

    BOOL            CanOverType() const;
    void            SetOverType(BOOL bOverType);

    BOOL            PosInRange(int nPos) const;

    TCHAR           GetPromptChar() const;
    CString         GetPromptString(int nLength) const;
    void            SetPromptChar(TCHAR ch, BOOL bAutoReplace = TRUE);

    BOOL            MaskCut();
    BOOL            MaskCopy();
    void            MaskReplaceSel(LPCTSTR lpszNewText);
    BOOL            MaskPaste();
    void            MaskDeleteSel();
    BOOL            MaskClear();
    void            MaskSelectAll();
    BOOL            IsModified() const;
    void            SetMaskedText(LPCTSTR lpszMaskedText, int nPos = 0, BOOL bUpdateWindow = TRUE);
    virtual BOOL    SetEditMask(LPCTSTR lpszMask, LPCTSTR lpszLiteral, LPCTSTR lpszDefault=NULL);
    TCHAR           ConvertUnicodeAlpha(TCHAR nChar, BOOL bUpperCase) const;
    virtual BOOL    CheckChar(TCHAR& nChar, int nPos);
    virtual BOOL    ProcessMask(TCHAR& nChar, int nEndPos);

    void            DeleteCharAt(int nPos);
    void            InsertCharAt(int nPos, TCHAR nChar);

    CString         GetMaskedText(int nStartPos = 0, int nEndPos = -1) const;

    void            GetMaskState(BOOL bCorrectSelection = TRUE);
    void            SetMaskState();

    void            MaskGetSel();

    BOOL            CopyToClipboard(const CString& strText);

    BOOL            IsPromptPos(int nPos) const;
    BOOL            IsPromptPos(const CString& strLiteral, int nPos) const;

    BOOL            CorrectPosition(int& nPos, BOOL bForward = TRUE);

    void            CorrectWindowText();

    virtual BOOL    IsPrintChar(TCHAR nChar);
    virtual BOOL    IsAlphaChar(TCHAR nChar);
    virtual void    NotifyPosNotInRange();
    virtual void    NotifyInvalidCharacter(TCHAR /*nChar*/, TCHAR /*chMask*/);
    void            ProcessChar(TCHAR nChar);

protected:
    int             OnCreate(LPVOID);
    void            OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    void            OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    void            OnSetDxFocus();

protected:
    int             m_nStartChar;       // Current position of the first character in the current selection.
    int             m_nEndChar;         // Current position of the first non-selected character past the end of the current selection.
    BOOL            m_bUseMask;         // TRUE to use the edit mask.
    BOOL            m_bOverType;        // TRUE to over type the text, set with VK_INSERT key press.
    BOOL            m_bModified;        // TRUE if mask edit has been modified.
    TCHAR           m_chPrompt;         // Prompt character used to identify the text entry.
    CString         m_strMask;          // Buffer that holds the actual edit mask value.
    CString         m_strDefault;       // Contains the edit controls default display text.
    CString         m_strWindowText;    // Buffer that holds the actual edit text.
    CString         m_strLiteral;       // Literal format that restricts where the user can enter text.

protected:
    DXWIN_BEGIN_MSG_MAP()
        MSG_WM_CREATE(OnCreate)
        MSG_WM_CHAR(OnChar)
        MSG_WM_KEYDOWN(OnKeyDown)
        MSG_WM_SETFOCUS_EX(OnSetDxFocus)
    DXWIN_END_MSG_MAP()
};

//===========================================================================
//  CDxDateEdit
class CDxDateEdit : public CDxMaskEdit
{
    DXOBJ_DECLARE_CLASS_NAME(CDxDateEdit, "dateedit")

public:
    CDxDateEdit();

    virtual void    SetDateTime(COleDateTime& dt);
    virtual void    SetDateTime(LPCTSTR strDate);

    virtual COleDateTime GetDateTime();
    virtual CString GetWindowDateTime();
    virtual COleDateTime ReadOleDateTime(LPCTSTR lpszData);
    virtual BOOL    ProcessMask(TCHAR& nChar, int nEndPos);
    virtual void    FormatOleDateTime(CString& strData, COleDateTime dt);

protected:
    int             OnCreate(LPVOID);

protected:
    DXWIN_BEGIN_MSG_MAP()
        MSG_WM_CREATE(OnCreate)
    DXWIN_END_MSG_MAP()
};

//===========================================================================
//  CDxTimeEdit
class CDxTimeEdit : public CDxDateEdit
{
    DXOBJ_DECLARE_CLASS_NAME(CDxTimeEdit, "timeedit")

public:
    CDxTimeEdit();

public:
    virtual void    SetHours(int nHours);
    virtual void    SetMins(int nMins);
    virtual void    SetTime(int nHours, int nMins);
    int             GetHours() const;
    int             GetMins() const;
    virtual BOOL    ProcessMask(TCHAR& nChar, int nEndPos);
    virtual void    FormatOleDateTime(CString& strData, COleDateTime dt);
    void            SetMilitary(BOOL bMilitary = TRUE);

protected:
    int             m_nHours;
    int             m_nMins;
    BOOL            m_bMilitary;

protected:
    int             OnCreate(LPVOID);

protected:
    DXWIN_BEGIN_MSG_MAP()
        MSG_WM_CREATE(OnCreate)
    DXWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////
inline int CDxTimeEdit::GetHours() const
{
    return m_nHours;
}

inline int CDxTimeEdit::GetMins() const
{
    return m_nMins;
}

inline void CDxTimeEdit::SetMilitary(BOOL bMilitary)
{
    m_bMilitary = bMilitary;

}


