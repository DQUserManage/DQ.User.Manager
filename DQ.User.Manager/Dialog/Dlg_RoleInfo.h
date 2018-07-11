#pragma once


// CDlg_RoleInfo 对话框

class CDlg_RoleInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_RoleInfo)

public:
	CDlg_RoleInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_RoleInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ROLE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CBCGPGridCtrl					m_GridCtrl;				///<定义Grid控件变量
public:
	virtual BOOL OnInitDialog();
	void InitLayout();
	void EditInfo(CBCGPGridRow* pRow);
public:
	afx_msg void OnBnClickedBtnAddRole();
	afx_msg void OnBnClickedBtnDelRole();
	afx_msg void OnBnClickedBtnUpdateRoleInfo();
	afx_msg void OnBnClickedBtnRoleAllSelect();
	afx_msg void OnBnClickedBtnRoleRevert();
	LRESULT OnDblClk(WPARAM wParam, LPARAM lParam);
};
