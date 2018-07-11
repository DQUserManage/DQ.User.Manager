// Dlg_AddUser.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_AddUser.h"
#include "resource.h"


// CDlg_AddUser 对话框

IMPLEMENT_DYNAMIC(CDlg_AddUser, CUserDialogModelBase)

CDlg_AddUser::CDlg_AddUser(CWnd* pParent /*=NULL*/)
	: CUserDialogModelBase(IDD_DLG_ADD_USER, pParent), m_rSexSelect(0)
{
	m_UserID = _T("");
	m_OperatorType = -1;
}

CDlg_AddUser::~CDlg_AddUser()
{
}

void CDlg_AddUser::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogModelBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER_ROLE, m_lUserRole);
	DDX_Radio(pDX, IDC_RADIO_USER_SEX_MAN, m_rSexSelect);
	DDX_Control(pDX, IDC_COMBO_ORG_NAME, m_cOrgName);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_ID, m_eUserID);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_NAME, m_eUserName);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_PWD, m_eUserPwd);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_EMAIL, m_eUserEmail);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_TELEPHONE, m_eUserTelephone);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_FAX, m_eUserFax);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_MOBILE, m_eUserMobile);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_QQ, m_eUserQQ);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_MSN, m_eUserMsn);
	DDX_Control(pDX, IDC_EDIT_ADD_USER_DESCRIPTION, m_eUserDescription);
}


BEGIN_MESSAGE_MAP(CDlg_AddUser, CUserDialogModelBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddUser::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddUser 消息处理程序
BOOL CDlg_AddUser::OnInitDialog()
{
	CUserDialogModelBase::OnInitDialog();

	m_lUserRole.SetCheckStyle(BS_AUTOCHECKBOX);

	///初始化下拉框树
	InitTreeComboBox(m_OrgInfo);

	//初始化ListBox
	InitListBox();

	m_eUserID.SetWindowText(m_UserID);
	m_UserInfo.SetUserID(m_UserID);

	if (m_OperatorType == 0)
		this->SetWindowText(L"添加用户");
	else
	{
		this->SetWindowText(L"修改用户");

		if (m_UserInfo.GetUserSex() == _T("女"))
			m_rSexSelect = 1;
		else
			m_rSexSelect = 0;
		
		int OrgLine = m_cOrgName.FindString(-1, m_OrgName);
		m_cOrgName.SetCurSel(OrgLine);

		m_eUserName.SetWindowText(m_UserInfo.GetUserNames());
		m_eUserPwd.SetWindowText(m_UserInfo.GetUserPw());
		m_eUserEmail.SetWindowText(m_UserInfo.GetUserEmail());
		m_eUserTelephone.SetWindowText(m_UserInfo.GetUserTelephone());
		m_eUserFax.SetWindowText(m_UserInfo.GetUserFax());
		m_eUserMobile.SetWindowText(m_UserInfo.GetUserMobile());
		m_eUserQQ.SetWindowText(m_UserInfo.GetUserQQ());
		m_eUserMsn.SetWindowText(m_UserInfo.GetUserMSN());
		m_eUserDescription.SetWindowText(m_UserInfo.GetDescription());

		//初始化选中ListBox
		CString RoleId;
		for (int i = 0;i < m_lUserRole.GetCount();i++)
		{
			ROLEITEMDATA pData = new DATA;
			pData = (ROLEITEMDATA)m_lUserRole.GetItemData(i);

			for(int j = 0; j< m_UserRole.size();j++)
				if (pData->RoleID == m_UserRole[j])
				{
					m_lUserRole.SetCheck(i,TRUE);
					break;
				}
		}
	}

	UpdateData(FALSE);

	return TRUE;
}


void CDlg_AddUser::InitListBox()
{
	int RowID;
	//查询角色信息
	std::shared_ptr<CDataTableMediator> pTable = CUserManagerDataService::GetInstance()->GetRoleInfo();
	for (int i = 0; i < pTable->GetRowCount(); i++)
	{
		ROLEITEMDATA pData = new DATA;
		ASSERT(pData != NULL);

		RowID = m_lUserRole.AddString(pTable->GetStringField(i, _T("ROLE_NAME")));

		pData->RoleID = pTable->GetStringField(i, _T("ROLE_ID"));
		pData->RoleName = pTable->GetStringField(i, _T("ROLE_NAME"));

		m_lUserRole.SetItemData(RowID, (DWORD)pData);
	}
	
}


void CDlg_AddUser::InitTreeComboBox(CDataTableMediator* OrgInfo)
{
	//节点级数
	m_NodeNum = 0;

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TREE_NODE);
	m_NodeNum = m_cOrgName.AddIcon(hIcon);
	::DestroyIcon(hIcon);

	m_cOrgName.SetBkGndColor(RGB(244, 244, 244));
	m_cOrgName.SetHiLightBkGndColor(RGB(157, 206, 255));
	m_cOrgName.SetTextColor(RGB(0, 128, 255));
	m_cOrgName.SetHiLightTextColor(RGB(255, 255, 0));
	m_cOrgName.SetHiLightFrameColor(RGB(255, 0, 255));

	//查找根节点
	vector<COrgInfo> RootOrgInfo;
	CUserManagerDataService::GetInstance()->GetDeptNode(_T(""), RootOrgInfo);

	for (int i = 0;i < RootOrgInfo.size();i++)
	{
		WORD wParentIdx1 = m_cOrgName.AddCTString(nRootIndex, m_NodeNum, RootOrgInfo[i].GetOrgName(), RootOrgInfo[i].GetOrgID());

		//添加子节点
		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TREE_NODE);
		m_NodeNum = m_cOrgName.AddIcon(hIcon);
		::DestroyIcon(hIcon);
		AddChildNode(RootOrgInfo[i].GetOrgID(), (m_NodeNum), wParentIdx1);
		
	}

	m_cOrgName.SetCurSel(0);
}


void CDlg_AddUser::AddChildNode(CString ParentID,int NodeNum,WORD ParentNode)
{
	vector<COrgInfo> RootOrgInfo;
	CUserManagerDataService::GetInstance()->GetDeptNode(ParentID, RootOrgInfo);

	for (int i = 0;i < RootOrgInfo.size();i++)
	{
		WORD wChildlevel = m_cOrgName.AddCTString(ParentNode, NodeNum, RootOrgInfo[i].GetOrgName(), RootOrgInfo[i].GetOrgID());

		//添加子节点
		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TREE_NODE);
		m_NodeNum = m_cOrgName.AddIcon(hIcon);
		::DestroyIcon(hIcon);
		AddChildNode(RootOrgInfo[i].GetOrgID(), (m_NodeNum), wChildlevel);
	}
	
}


void CDlg_AddUser::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_UserRole.clear();
	ROLEITEMDATA UserRole;
	//获取选中的角色ID
	for (int i = 0;i < m_lUserRole.GetCount();i++)
	{
		if (m_lUserRole.GetCheck(i))
		{
			UserRole = (ROLEITEMDATA)m_lUserRole.GetItemData(i);
			m_UserRole.push_back(UserRole->RoleID);
		}
	}

	CString eUserID, eUserName, eUserSex, eUserPwd, eUserEmail, eUserTelephone, eUserFax, eUserMobile, eUserQQ, eUserMsn, eUserDescription;

	if (m_rSexSelect)
		eUserSex = _T("女");
	else
		eUserSex = _T("男");
	m_eUserID.GetWindowText(eUserID);
	m_eUserName.GetWindowText(eUserName);
	m_eUserPwd.GetWindowText(eUserPwd);
	m_eUserEmail.GetWindowText(eUserEmail);
	m_eUserTelephone.GetWindowText(eUserTelephone);
	m_eUserFax.GetWindowText(eUserFax);
	m_eUserMobile.GetWindowText(eUserMobile);
	m_eUserQQ.GetWindowText(eUserQQ);
	m_eUserMsn.GetWindowText(eUserMsn);
	m_eUserDescription.GetWindowText(eUserDescription);

	LPITEMDATA OrgInfo = (LPITEMDATA)m_cOrgName.GetItemData(m_cOrgName.GetCurSel());
	m_UserInfo.SetOrgID(OrgInfo->NodeID);
	CString OrgName;
	m_cOrgName.GetLBText(m_cOrgName.GetCurSel(),OrgName);
	m_UserInfo.SetOrgName(OrgName);
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

	CUserDialogModelBase::OnOK();
}
