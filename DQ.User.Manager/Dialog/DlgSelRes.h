#pragma once

class CDlgSelRes : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSelRes)

public:
	CDlgSelRes(const CString& csResID,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelRes();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEL_RES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	LRESULT OnDblClk(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void InitLayout();
	void InitControl();
	void InitData();

public:
	CString m_csResID;  ///<选择的资源ID
	CString m_csResName;   ///<选择的资源名称

private:
	CBCGPGridCtrl  m_wndRes; ///<系统资源列表
	CBCGPGridRow*  m_pSelRow;  ///<要选择的行
public:
	afx_msg void OnBnClickedOk();
};
