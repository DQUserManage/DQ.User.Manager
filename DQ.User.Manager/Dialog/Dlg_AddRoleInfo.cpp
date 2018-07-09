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
	DDX_Control(pDX, IDC_TREE_ROLE_POWER, m_wndMod);
}


BEGIN_MESSAGE_MAP(CDlg_AddRoleInfo, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddRoleInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddRoleInfo 消息处理程序
BOOL CDlg_AddRoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	//初始化角色权限
	vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(_T(""), vMode);
	for (size_t i = 0; i < vMode.size(); i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hRoot = m_wndMod.InsertItem(info.m_csName, TVI_ROOT);

		FillModeTree(hRoot, info.m_csModID);

		m_wndMod.Expand(hRoot, TVE_EXPAND);
	}

	m_wndMod.SetRedraw(TRUE);

	return TRUE;
}


void CDlg_AddRoleInfo::FillModeTree(HTREEITEM hParent, const CString& csParent)
{
	std::vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(csParent, vMode);
	for (size_t i = 0; i < vMode.size(); i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hItem = m_wndMod.InsertItem(info.m_csName, hParent);

		FillModeTree(hItem, info.m_csModID);

		m_wndMod.Expand(hItem, TVE_EXPAND);
	}
}


void CDlg_AddRoleInfo::OnBnClickedOk()
{
	m_eRoleName.GetWindowText(m_RoleName);

	CUserDialogBase::OnOK();
}


