#pragma once

class CDlgUserOrg : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgUserOrg)

public:
	CDlgUserOrg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUserOrg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USER_ORG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	
	
};
