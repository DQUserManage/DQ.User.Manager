#pragma once


class CDlgSysMod : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSysMod)

public:
	CDlgSysMod(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysMod();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_MOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	void InitLayout();

public:
	CBCGPTreeCtrl m_wndMod;
};
