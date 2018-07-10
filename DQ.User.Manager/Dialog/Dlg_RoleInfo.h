#pragma once


// CDlg_RoleInfo �Ի���

class CDlg_RoleInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_RoleInfo)

public:
	CDlg_RoleInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_RoleInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ROLE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CBCGPGridCtrl					m_GridCtrl;				///<����Grid�ؼ�����

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAddRole();
	afx_msg void OnBnClickedBtnDelRole();
	afx_msg void OnBnClickedBtnUpdateRoleInfo();
};
