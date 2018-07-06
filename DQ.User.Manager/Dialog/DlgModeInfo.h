#pragma once
#include "afxwin.h"

class CDlgModeInfo : public CUserDialogModelBase
{
	DECLARE_DYNAMIC(CDlgModeInfo)

public:
	CDlgModeInfo(CSysMod& mod, bool bEdit = false,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgModeInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOD_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CResBrowserEdit m_wndRes;
	CBCGPComboBox m_wndType;
private:
	bool  m_bEdit;   ///<�Ƿ�༭
	CSysMod& m_SysMod;  ///<ģ����Ϣ
};
