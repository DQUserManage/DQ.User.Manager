#pragma once


// CDlg_UserInfo �Ի���

class CDlg_UserInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_UserInfo)

public:
	CDlg_UserInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_UserInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USER_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CBCGPGridCtrl					m_GridCtrl;				///<����Grid�ؼ�����
public:
	virtual BOOL OnInitDialog();

public:
	/** ����û���Ϣ */
	afx_msg void OnBnClickedBtnAddUser();
	/** ɾ���û���Ϣ */
	afx_msg void OnBnClickedBtnDelUser();
	/** �޸��û���Ϣ */
	afx_msg void OnBnClickedBtnUpdateUser();
};
