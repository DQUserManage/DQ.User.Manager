#pragma once

#include "WzComboBox.h"
// CDlg_AddUser 对话框

typedef struct RoleITEMDATA
{
	CString RoleName;
	CString RoleID;
}DATA, *ROLEITEMDATA;

class CDlg_AddUser : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_AddUser)

public:
	CDlg_AddUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_AddUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CCheckListBox			m_lUserRole;			///<用户角色
	int						m_rSexSelect;			///<性别单选按钮
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
	CDataTableMediator*		m_OrgInfo;				///< 用户所属部门ID
	int						m_OperatorType;			///< 操作类型 0：添加用户 1：修改用户
	int						m_NodeNum;
	CString					m_OrgName;				///<部门名称
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
