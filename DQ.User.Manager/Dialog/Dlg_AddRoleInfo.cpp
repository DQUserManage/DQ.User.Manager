// Dlg_AddRoleInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_AddRoleInfo.h"
#include "resource.h"


// CDlg_AddRoleInfo 对话框

IMPLEMENT_DYNAMIC(CDlg_AddRoleInfo, CUserDialogBase)

CDlg_AddRoleInfo::CDlg_AddRoleInfo(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ADD_ROLE, pParent)
{

}

CDlg_AddRoleInfo::~CDlg_AddRoleInfo()
{
}

void CDlg_AddRoleInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROLE_NAME, m_eRoleName);
}


BEGIN_MESSAGE_MAP(CDlg_AddRoleInfo, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddRoleInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddRoleInfo 消息处理程序
BOOL CDlg_AddRoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	//初始化角色权限
	std::shared_ptr<CDataTableMediator> pTable = CUserManagerDataService::GetInstance()->GetOrgInfo();

	//部门填充树控件
	FillPowerTree(pTable.get(), L"", TVI_ROOT);

	return TRUE;
}


void CDlg_AddRoleInfo::OnBnClickedOk()
{
	m_eRoleName.GetWindowText(m_RoleName);

	CUserDialogBase::OnOK();
}


void CDlg_AddRoleInfo::FillPowerTree(CDataTableMediator* pTable, CString sParentID, HTREEITEM hRoot)
{

}
