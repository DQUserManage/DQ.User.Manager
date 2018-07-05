// Dlg_AddUser.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_AddUser.h"
#include "resource.h"


// CDlg_AddUser 对话框

IMPLEMENT_DYNAMIC(CDlg_AddUser, CUserDialogBase)

CDlg_AddUser::CDlg_AddUser(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ADD_USER, pParent)
{
	m_OperatorType = -1;
}

CDlg_AddUser::~CDlg_AddUser()
{
}

void CDlg_AddUser::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_ORG_NAME, m_eOrgName);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_ID, m_eUserID);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_NAME, m_eUserName);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_SEX, m_eUserSex);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_PWD, m_eUserPwd);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_EMAIL, m_eUserEmail);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_TELEPHONE, m_eUserTelephone);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_FAX, m_eUserFax);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_MOBILE, m_eUserMobile);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_QQ, m_eUserQQ);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_MSN, m_eUserMsn);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_DESCRIPTION, m_eUserDescription);
}


BEGIN_MESSAGE_MAP(CDlg_AddUser, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddUser::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddUser 消息处理程序
BOOL CDlg_AddUser::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	m_eOrgName.SetWindowText(m_OrgName);
	m_UserInfo.SetOrgID(m_OrgID);

	if (m_OperatorType == 0)
		this->SetWindowText(L"添加用户");
	else
	{
		this->SetWindowText(L"修改用户");
		m_eUserID.SetWindowText(m_UserInfo.GetUserID());
		m_eUserName.SetWindowText(m_UserInfo.GetUserNames());
		m_eUserSex.SetWindowText(m_UserInfo.GetUserSex());
		m_eUserPwd.SetWindowText(m_UserInfo.GetUserPw());
		m_eUserEmail.SetWindowText(m_UserInfo.GetUserEmail());
		m_eUserTelephone.SetWindowText(m_UserInfo.GetUserTelephone());
		m_eUserFax.SetWindowText(m_UserInfo.GetUserFax());
		m_eUserMobile.SetWindowText(m_UserInfo.GetUserMobile());
		m_eUserQQ.SetWindowText(m_UserInfo.GetUserQQ());
		m_eUserMsn.SetWindowText(m_UserInfo.GetUserMSN());
		m_eUserDescription.SetWindowText(m_UserInfo.GetDescription());
	}

	

	return TRUE;
}





void CDlg_AddUser::OnBnClickedOk()
{
	CString eUserID, eUserName, eUserSex, eUserPwd, eUserEmail, eUserTelephone, eUserFax, eUserMobile, eUserQQ, eUserMsn, eUserDescription;

	m_eUserID.GetWindowText(eUserID);
	m_eUserName.GetWindowText(eUserName);
	m_eUserSex.GetWindowText(eUserSex);
	m_eUserPwd.GetWindowText(eUserPwd);
	m_eUserEmail.GetWindowText(eUserEmail);
	m_eUserTelephone.GetWindowText(eUserTelephone);
	m_eUserFax.GetWindowText(eUserFax);
	m_eUserMobile.GetWindowText(eUserMobile);
	m_eUserQQ.GetWindowText(eUserQQ);
	m_eUserMsn.GetWindowText(eUserMsn);
	m_eUserDescription.GetWindowText(eUserDescription);

	m_UserInfo.SetDescription(eUserDescription);
	m_UserInfo.SetUserEmail(eUserEmail);
	m_UserInfo.SetUserFax(eUserFax);
	m_UserInfo.SetUserID(eUserID);
	m_UserInfo.SetUserMobile(eUserMobile);
	m_UserInfo.SetUserMSN(eUserMsn);
	m_UserInfo.SetUserName(eUserName);
	m_UserInfo.SetUserPw(eUserPwd);
	m_UserInfo.SetUserQQ(eUserQQ);
	m_UserInfo.SetUserSex(eUserSex);
	m_UserInfo.SetUserTelephone(eUserTelephone);

	CUserDialogBase::OnOK();
}
