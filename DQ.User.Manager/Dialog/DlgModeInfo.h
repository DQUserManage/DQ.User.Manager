#pragma once
#include "afxwin.h"

class CDlgModeInfo : public CUserDialogModelBase
{
	DECLARE_DYNAMIC(CDlgModeInfo)

public:
	CDlgModeInfo(CSysMod& mod, bool bEdit = false,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgModeInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOD_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CResBrowserEdit m_wndRes;
	CBCGPComboBox m_wndType;
private:
	bool  m_bEdit;   ///<是否编辑
	CSysMod& m_SysMod;  ///<模块信息
};
