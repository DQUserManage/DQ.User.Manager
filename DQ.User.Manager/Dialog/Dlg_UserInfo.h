#pragma once


// CDlg_UserInfo 对话框

class CDlg_UserInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_UserInfo)

public:
	CDlg_UserInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_UserInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USER_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CBCGPGridCtrl					m_GridCtrl;				///<定义Grid控件变量
public:
	virtual BOOL OnInitDialog();

public:
	/** 添加用户信息 */
	afx_msg void OnBnClickedBtnAddUser();
	/** 删除用户信息 */
	afx_msg void OnBnClickedBtnDelUser();
	/** 修改用户信息 */
	afx_msg void OnBnClickedBtnUpdateUser();
};
