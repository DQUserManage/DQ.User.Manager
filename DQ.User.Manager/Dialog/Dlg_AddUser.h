#pragma once

#include "WzComboBox.h"
// CDlg_AddUser �Ի���

typedef struct RoleITEMDATA
{
	CString RoleName;
	CString RoleID;
}DATA, *ROLEITEMDATA;

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
	CCheckListBox			m_lUserRole;			///<�û���ɫ
	int						m_rSexSelect;			///<�Ա�ѡ��ť
	CWzComboBox				m_cOrgName;
	CEdit					m_eUserID;
	CEdit					m_eUserName;
	CEdit					m_eUserPwd;
	CEdit					m_eUserEmail;
	CEdit					m_eUserTelephone;
	CEdit					m_eUserFax;
	CEdit					m_eUserMobile;
	CEdit					m_eUserQQ;
	CEdit					m_eUserMsn;
	CEdit					m_eUserDescription;

	CUserInfo				m_UserInfo;				
	CString					m_UserID;
	CDataTableMediator*		m_OrgInfo;				///< �û���������ID
	int						m_OperatorType;			///< �������� 0������û� 1���޸��û�
	int						m_NodeNum;
	CString					m_OrgName;				///<��������
	vector<CString>			m_UserRole;
public:
	void SetUserID(CString UserId) { m_UserID = UserId; };
	void SetOrgInfo(CDataTableMediator* OrgInfo) { m_OrgInfo = OrgInfo; }
	void SetUserInfo(CUserInfo UserInfo) { m_UserInfo = UserInfo; }
	CUserInfo GetUserInfo() { return m_UserInfo; }
	void SetOperatorType(int OperatorType) { m_OperatorType = OperatorType; }
	void InitTreeComboBox(CDataTableMediator* OrgInfo);
	void AddChildNode(CString ParentID, int NodeNum, WORD ParentNode);
	void SetOrgName(CString OrgName) { m_OrgName = OrgName; }
	void InitListBox();
	vector<CString> GetUserRoleId() { return m_UserRole; }
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
};
