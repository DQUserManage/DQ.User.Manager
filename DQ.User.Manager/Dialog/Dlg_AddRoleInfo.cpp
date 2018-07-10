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
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_eDescription);
}


BEGIN_MESSAGE_MAP(CDlg_AddRoleInfo, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddRoleInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddRoleInfo 消息处理程序
BOOL CDlg_AddRoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	//初始化角色权限
	std::vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(_T(""), vMode);
	for (size_t i = 0; i < vMode.size(); i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hRoot = m_wndMod.InsertItem(info.m_csName, TVI_ROOT);

		m_wndMod.SetItemData(hRoot, (DWORD_PTR)new CString(info.m_csModID));
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

		m_wndMod.SetItemData(hItem, (DWORD_PTR)new CString(info.m_csModID));
		FillModeTree(hItem, info.m_csModID);
	}
}


void CDlg_AddRoleInfo::OnBnClickedOk()
{
	m_eRoleName.GetWindowText(m_RoleName);
	m_eDescription.GetWindowText(m_Description);

	HTREEITEM pRoot = m_wndMod.GetFirstVisibleItem();
	GetSelChildNode(m_pCurRola, pRoot);

	CUserDialogBase::OnOK();
}

/** 获取选中的叶节点 */
void	CDlg_AddRoleInfo::GetSelChildNode(vector<CString> pRola, HTREEITEM pRoot)
{
	CString *pData = NULL;
	while (pRoot)
	{
		HTREEITEM pChild = m_wndMod.GetChildItem(pRoot);
		if (!pChild)
		{
			if (m_wndMod.GetCheck(pRoot) == 1)
			{
				pData = (CString *)m_wndMod.GetItemData(pRoot);
				if (pData)
				{
					pRola.push_back(*pData);
				}
			}
		}
		else
			GetSelChildNode(pRola, pChild);
		// 获取下一个兄弟节点
		pRoot = m_wndMod.GetNextSiblingItem(pRoot);
	}
}
