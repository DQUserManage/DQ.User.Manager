//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2016 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPRibbonEdit.h: interface for the CBCGPRibbonEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPRIBBONEDIT_H__FE5913DD_04A0_45EC_A7AF_DA1EA9090D39__INCLUDED_)
#define AFX_BCGPRIBBONEDIT_H__FE5913DD_04A0_45EC_A7AF_DA1EA9090D39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPRibbonButton.h"
#include "BCGPToolBarImages.h"
#include "BCGPButton.h"

#ifndef BCGP_EXCLUDE_RIBBON

class CBCGPRibbonEditCtrl;
class CBCGPRibbonSpinButtonCtrl;

class BCGCBPRODLLEXPORT CBCGPRibbonEdit : public CBCGPRibbonButton  
{
	friend class CBCGPRibbonEditCtrl;
	friend class CBCGPClearButton;
	friend class CBCGPRibbonSpinButtonCtrl;
	friend class CBCGPRibbonCollector;

	DECLARE_DYNCREATE(CBCGPRibbonEdit)

// Construction:
public:
	CBCGPRibbonEdit(UINT nID, int nWidth, LPCTSTR lpszLabel = NULL, int nImage = -1);
	virtual ~CBCGPRibbonEdit();

	enum BCGPRIBBON_EDIT_RECENT_CHANGE_EVENT
	{
		BCGPRIBBON_EDIT_NOT_CHANGED,
		BCGPRIBBON_EDIT_CHANGED_BY_ENTER_KEY,
		BCGPRIBBON_EDIT_CHANGED_BY_FOCUS,
		BCGPRIBBON_EDIT_CHANGED_BY_SPIN_BUTTON,
		BCGPRIBBON_EDIT_CHANGED_FROM_DROPDOWN,
	};

protected:
	CBCGPRibbonEdit();

// Attributes:
public:
	CString GetEditText () const
	{
		return m_strEdit;
	};

	void SetEditText (CString strText);

	void EnableSpinButtons (int nMin, int nMax);
	
	void SetTextAlign (int nAlign);	// ES_LEFT, ES_CENTER or ES_RIGHT
	int GetTextAlign () const
	{
		return m_nAlign;
	}

	int GetWidth (BOOL bInFloatyMode = FALSE) const
	{
		return bInFloatyMode ? m_nWidthFloaty : m_nWidth;
	}

	void SetWidth (int nWidth, BOOL bInFloatyMode = FALSE);

	int GetRangeMin () const
	{
		return m_nMin;
	}
	int GetRangeMax () const
	{
		return m_nMax;
	}

	void SetPrompt(LPCTSTR lpszPrompt);

	void EnableSearchMode(BOOL bEnable, LPCTSTR lpszPrompt);
	BOOL IsSearchMode() const
	{
		return m_bSearchMode;
	}
	
	CString GetPrompt() const
	{
		return m_strSearchPrompt;
	};

	CString GetSearchPrompt () const
	{
		return GetPrompt();
	};

	BCGPRIBBON_EDIT_RECENT_CHANGE_EVENT	GetRecentChangeEvent() const
	{
		return m_RecentChangeEvt;
	}

	void SetMaxWidth(int nMaxWidth);

	int GetMaxWidth() const
	{
		return m_nMaxWidth;
	}

	void SetLimitText(int nChars);
	
	int GetLimitText() const
	{
		return m_nLimitText;
	}

// Overrides
public:
	virtual BOOL HasLargeMode () const
	{
		return FALSE;
	}

	virtual BOOL HasCompactMode () const
	{
		return TRUE;
	}

	virtual CSize GetIntermediateSize (CDC* pDC);
	virtual CSize GetCompactSize (CDC* pDC);

	virtual void Redraw ();
	virtual void OnHighlight (BOOL bHighlight);
	virtual void OnSetFocus (BOOL bSet);
	virtual BOOL PreLMouseDown (CPoint point);

	virtual BOOL IsHighlighted () const
	{
		return m_bIsHighlighted || m_bIsEditFocused;
	}

	virtual BOOL HasFocus () const
	{
		return m_bIsEditFocused;
	}
	
	virtual BOOL HasSpinButtons () const
	{
		return m_bHasSpinButtons;
	}

	virtual void OnDraw (CDC* pDC);
	virtual void OnDrawOnList (CDC* pDC, CString strText, int nTextOffset, CRect rect, BOOL bIsSelected, BOOL bHighlighted);

	virtual void OnDrawLabelAndImage (CDC* pDC);

	virtual void OnLButtonDown (CPoint point);
	virtual void OnLButtonUp (CPoint point);

	virtual void CopyFrom (const CBCGPBaseRibbonElement& src);

	virtual BOOL CanBeStretched ()
	{
		return FALSE;
	}

	virtual void OnAfterChangeRect (CDC* pDC);
	virtual void OnShow (BOOL bShow);

	virtual CBCGPRibbonEditCtrl* CreateEdit (CWnd* pWndParent, DWORD dwEditStyle);

	virtual void OnEnable (BOOL bEnable);
	virtual BOOL OnKey (BOOL bIsMenuKey);
	virtual void DropDownList () {}

	virtual void OnRTLChanged (BOOL bIsRTL);

	virtual void DestroyCtrl();
	virtual void OnChangeRibbonFont();

	virtual BOOL SetACCData (CWnd* pParent, CBCGPAccessibilityData& data);

	virtual BOOL OnEditChange ()
	{
		return FALSE;
	}

	virtual BOOL IsCommandsCombo() const 
	{ 
		return FALSE; 
	
	}
	virtual BOOL CanBeSeparated() const			{	return FALSE;	}
	virtual BOOL IsCustomIconAllowed() const	{	return FALSE;	}

	const CBCGPRibbonEditCtrl* GetEditCtrl () const	{	return m_pWndEdit;	}
	const CBCGPRibbonSpinButtonCtrl* GetSpinButtonCtrl () const	{	return m_pWndSpin;	}

	virtual int FindItemByPrefix(LPCTSTR /*lpszPrefix*/, CString& /*strResult*/) const	{	return -1;	}

	virtual BOOL CanBePlacedOnNonCollapsiblePanel() const
	{
		return FALSE;
	}

	virtual void OnGetPopupDlgText(CString& strOut) 
	{
		strOut = GetEditText();
	}

	virtual void OnSetPopupDlgText(const CString& strResult)
	{
		SetEditText(strResult);
	}

	virtual CWnd* GetEmbeddedWnd() { return (CWnd*)m_pWndEdit; }
	
	virtual void OnUpdateToolTips();

	virtual BOOL QueryElements(const CStringArray& /*arWords*/, CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*>& /*arButtons*/, int /*nMaxResults*/, BOOL /*bDescription*/, BOOL /*bAll*/) { return FALSE; }
	
	virtual void OnDeltaPos(LPNMUPDOWN pUpDown);

// Operations:
protected:
	BOOL CreateSpinButton (CBCGPRibbonEditCtrl* pWndEdit, CWnd* pWndParent);
	void CommonInit ();
	void ReposEditCtrl ();

	void AddTooltip(CBCGPRibbonEditCtrl* pWndEdit);
	void DelTooltip();

// Attributes:
protected:
	BOOL						m_bIsEditFocused;
	CString						m_strEdit;
	CBCGPRibbonEditCtrl*		m_pWndEdit;
	CBCGPRibbonSpinButtonCtrl*	m_pWndSpin;
	CBCGPButton*				m_pBtnClear;
	int							m_nWidth;
	int							m_nWidthFloaty;
	BOOL						m_bHasDropDownList;
	BOOL						m_bHasSpinButtons;
	int							m_nMin;
	int							m_nMax;
	int							m_nAlign;
	int							m_nLabelImageWidth;
	BOOL						m_bNotifyCommand;
	BOOL						m_bSearchMode;
	CString						m_strSearchPrompt;
	CBCGPToolBarImages			m_ImageSearch;
	CBCGPToolBarImages			m_ImageLight;
	COLORREF					m_clrLight;
	BOOL						m_bDontScaleInHighDPI;
	BOOL						m_bIsAutoComplete;
	COLORREF					m_clrCustomText;
	int							m_nMaxWidth;
	int							m_nLimitText;

	BCGPRIBBON_EDIT_RECENT_CHANGE_EVENT	m_RecentChangeEvt;
};

/////////////////////////////////////////////////////////////////////////////
// CBCGPRibbonCommandsComboBox

class BCGCBPRODLLEXPORT CBCGPRibbonCommandsComboBox : public CBCGPRibbonEdit
{
	DECLARE_DYNCREATE(CBCGPRibbonCommandsComboBox)
		
// Construction:
public:
	CBCGPRibbonCommandsComboBox(
		UINT nID, LPCTSTR lpszPrompt = _T("Tell me what you want to do..."), int nWidth = -1);
	
	virtual ~CBCGPRibbonCommandsComboBox();
	
protected:
	CBCGPRibbonCommandsComboBox();
	
// Operations:
public:
	void CleanUp();
	
// Overrides
protected:
	virtual BOOL OnEditChange();
	virtual BOOL OnProcessKey(UINT nChar);
	virtual BOOL IsCommandsCombo() const { return TRUE; }
	virtual BOOL NotifyCommand (BOOL /*bWithDelay*/ = FALSE)	{ return FALSE; }
	
// Attributes:
protected:
	CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> m_arSearchResultsFiltered;
	CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> m_arSearchResultsRecent;
};

/////////////////////////////////////////////////////////////////////////////
// CBCGPRibbonEditCtrl

class BCGCBPRODLLEXPORT CBCGPRibbonEditCtrl : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CBCGPRibbonEditCtrl)

	friend class CBCGPRibbonEdit;
	friend class CBCGPRibbonSpinButtonCtrl;

// Construction
public:
	CBCGPRibbonEditCtrl(CBCGPRibbonEdit& edit);

// Attributes
public:
	CBCGPRibbonEdit& GetOwnerRibbonEdit ()
	{
		return m_edit;
	}

protected:
	CBCGPRibbonEdit&	m_edit;
	BOOL				m_bTracked;
	BOOL				m_bIsHighlighted;
	BOOL				m_bIsContextMenu;
	CString				m_strOldText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPRibbonEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

    //Accessibility
	virtual HRESULT get_accName(VARIANT varChild, BSTR *pszName);
	virtual HRESULT get_accRole(VARIANT varChild, VARIANT *pvarRole);
	virtual HRESULT get_accValue(VARIANT varChild, BSTR *pszValue);
	virtual HRESULT get_accKeyboardShortcut(VARIANT varChild, BSTR* pszKeyboardShortcut);
	virtual HRESULT get_accDescription(VARIANT varChild, BSTR FAR* pszDescription);

// Implementation
public:
	virtual ~CBCGPRibbonEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPRibbonEditCtrl)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnChange();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()

	BOOL ProcessClipboardAccelerators (UINT nChar);
};

//////////////////////////////////////
// CBCGPRibbonCommandsMenuCustomItems

struct BCGCBPRODLLEXPORT CBCGPRibbonCommandsMenuCustomItems
{
	CString m_strInput;
	CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> m_arCustomItems;
};

#endif // BCGP_EXCLUDE_RIBBON

#endif // !defined(AFX_BCGPRIBBONEDIT_H__FE5913DD_04A0_45EC_A7AF_DA1EA9090D39__INCLUDED_)
