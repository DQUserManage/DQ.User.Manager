#pragma once
#include "../Layout/UserDialogBase.h"

#include "CUserInfo.h"

// CDlg_AddUser �Ի���

class CDlg_AddUser : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_AddUser)

public:
	CDlg_AddUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_AddUser();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CEdit		m_eOrgName;
	CEdit		m_eUserID;
	CEdit		m_eUserName;
	CEdit		m_eUserSex;
	CEdit		m_eUserPwd;
	CEdit		m_eUserEmail;
	CEdit		m_eUserTelephone;
	CEdit		m_eUserFax;
	CEdit		m_eUserMobile;
	CEdit		m_eUserQQ;
	CEdit		m_eUserMsn;
	CEdit		m_eUserDescription;

	CUserInfo	m_UserInfo;				
	CString		m_OrgName;				///< �û�������������
	CString		m_OrgID;				///< �û���������ID
	int			m_OperatorType;			///< �������� 0������û� 1���޸��û�
public:
	void SetOrgName(CString OrgName) {m_OrgName = OrgName;}
	void SetOrgID(CString OrgID) { m_OrgID = OrgID; }
	void SetUserInfo(CUserInfo UserInfo) { m_UserInfo = UserInfo; }
	CUserInfo GetUserInfo() { return m_UserInfo; }
	void SetOperatorType(int OperatorType) { m_OperatorType = OperatorType; }

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
};
