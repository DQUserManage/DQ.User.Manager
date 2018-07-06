#pragma once

class CDlgDeptTree : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgDeptTree)

public:
	CDlgDeptTree(const CString& csOrgID = _T(""),CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDeptTree();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPT_TREE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkDeptTree(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	void InitControl();
	void InitLayout();
	void FillChildTree(HTREEITEM hRoot, const CString& csParentID);
public:
	CBCGPTreeCtrl m_deptTree;

private:
	CMap<HTREEITEM, HTREEITEM, CString, CString> m_vIDs;
	HTREEITEM m_hSelItem;
public:
	CString m_csOrgID;
	CString m_csOrgName;
};
