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
	m_OperateType = -1;
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
	ON_NOTIFY(NM_CLICK, IDC_TREE_ROLE_POWER, &CDlg_AddRoleInfo::OnNMClickTreeRolePower)
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
	}


	//修改角色信息时 初始化选中
	if (m_OperateType == 1)
	{
		this->SetWindowText(_T("修改角色信息"));

		m_eRoleName.SetWindowText(m_RoleInfo.GetRoleName());
		m_eDescription.SetWindowText(m_RoleInfo.GetRemark());
		
		//查询角色对应模块
		std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetSysModeInfoUseRoleId(m_RoleInfo.GetRoleID()));

		if (pTab->GetRowCount() > 0)
		{
			m_wndMod.ModifyStyle(TVS_CHECKBOXES, 0);
			m_wndMod.ModifyStyle(0, TVS_CHECKBOXES);

			HTREEITEM hParent = m_wndMod.GetFirstVisibleItem();
			SetTreeNodeSel(pTab.get(), L"", hParent);
		}
	}
	else
		this->SetWindowText(_T("添加角色信息"));

	return TRUE;
}


/** 设置树节点选中 */
void	CDlg_AddRoleInfo::SetTreeNodeSel(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot)
{
	if (!pTable)
		return;
	CString sFilter = L"";
	if (sParentID.Trim() == "")
		sFilter = L"Isnull(PARENT_ID,'')=''";
	else
		sFilter = L"PARENT_ID='" + sParentID + L"'";

	CDataTableMediator *pTempTable = pTable->FilterReturnTable(sFilter);
	if (!pTempTable)
		return;

	CString sName = L"";
	CString sItemText = L"";
	int iCount = pTempTable->GetRowCount();
	for (int i = 0; i < iCount; i++)
	{
		sName = pTempTable->GetStringField(i, L"RES_NAME");
		HTREEITEM hTemp = hRoot;
		while (hTemp)
		{
			sItemText = m_wndMod.GetItemText(hTemp);
			if (sName == sItemText)
			{
				BOOL bCheck = m_wndMod.GetCheck(hTemp);     //获取当前复选状态
				m_wndMod.SetCheck(hTemp);
				bCheck = m_wndMod.GetCheck(hTemp);     //获取当前复选状态

				SetTreeNodeSel(pTable, pTempTable->GetStringField(i, L"NODE_ID"), m_wndMod.GetChildItem(hTemp));
				break;
			}
			hTemp = m_wndMod.GetNextSiblingItem(hTemp);
		}
	}
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
	CString RoleName, Description;

	m_eRoleName.GetWindowText(RoleName);
	m_eDescription.GetWindowText(Description);

	m_RoleInfo.SetRoleName(RoleName);
	m_RoleInfo.SetRemark(Description);

	HTREEITEM pRoot = m_wndMod.GetFirstVisibleItem();
	GetSelChildNode(&m_pCurRola, pRoot);

	CUserDialogBase::OnOK();
}

/** 获取选中的叶节点 */
void	CDlg_AddRoleInfo::GetSelChildNode(vector<CString>* pRola, HTREEITEM pRoot)
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
					pRola->push_back(*pData);
				}
			}
		}
		else
			GetSelChildNode(pRola, pChild);
		// 获取下一个兄弟节点
		pRoot = m_wndMod.GetNextSiblingItem(pRoot);
	}
}


void CDlg_AddRoleInfo::OnNMClickTreeRolePower(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	UINT uFlag;   //接收有关点击测试的信息的整数
	HTREEITEM hTree;
	BOOL bCheck;
	GetCursorPos(&point);    //获取屏幕鼠标坐标
	m_wndMod.ScreenToClient(&point);           //转化成客户坐标
	hTree = m_wndMod.HitTest(point, &uFlag);    //返回与CtreeCtrl关联的光标的当前位置和句柄

	if (hTree && (TVHT_ONITEMSTATEICON & uFlag))	//点中复选框
	{
		m_wndMod.SelectItem(hTree);
		BOOL bCheckParent = TRUE;
		bCheck = m_wndMod.GetCheck(hTree);     //获取当前复选状态
		if (bCheck)
		{
			HTREEITEM hSiblingItem = m_wndMod.GetNextSiblingItem(hTree);
			while (hSiblingItem)
			{
				if (m_wndMod.GetCheck(hSiblingItem))
				{
					bCheckParent = FALSE;
					break;
				}
				hSiblingItem = m_wndMod.GetNextSiblingItem(hSiblingItem);
			}
			if (bCheckParent)
			{
				hSiblingItem = m_wndMod.GetPrevSiblingItem(hTree);
				while (hSiblingItem)
				{
					if (m_wndMod.GetCheck(hSiblingItem))
					{
						bCheckParent = FALSE;
						break;
					}
					hSiblingItem = m_wndMod.GetPrevSiblingItem(hSiblingItem);
				}
			}
		}
		if (bCheckParent)
			SetParentCheck(hTree, !bCheck);				// 设置父项复选
		SetChildCheck(hTree, !bCheck);               //设置子项复选状态
	}

	*pResult = 0;
}


/** 设置父节点选中 */
void	CDlg_AddRoleInfo::SetParentCheck(HTREEITEM hTree, BOOL bCheck)
{
	hTree = m_wndMod.GetParentItem(hTree);  //获取子项句柄
	if (hTree)
	{
		m_wndMod.SetCheck(hTree, bCheck);
		SetParentCheck(hTree, bCheck);     //递归调用
	}
}

/** 设置子节点选中 */
void	CDlg_AddRoleInfo::SetChildCheck(HTREEITEM hTree, BOOL bCheck)
{
	hTree = m_wndMod.GetChildItem(hTree);  //获取子项句柄
	while (hTree)
	{
		m_wndMod.SetCheck(hTree, bCheck);
		SetChildCheck(hTree, bCheck);     //递归调用
		hTree = m_wndMod.GetNextSiblingItem(hTree);    //获取兄弟的句柄
	}
}

