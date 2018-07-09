#pragma once


// CDlg_AddRoleInfo 对话框

class CDlg_AddRoleInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_AddRoleInfo)

public:
	CDlg_AddRoleInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_AddRoleInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_ROLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CEdit			m_eRoleName;
	CString			m_RoleName;
	CBCGPTreeCtrl	m_wndMod;
public:
	CString GetRoleName() { return m_RoleName; }

	void FillModeTree(HTREEITEM hParent, const CString& csParent);
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
};
