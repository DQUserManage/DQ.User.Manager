#pragma once


class CDlgSysMod : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSysMod)

public:
	CDlgSysMod(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSysMod();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_MOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	void InitLayout();

public:
	CBCGPTreeCtrl m_wndMod;
};
