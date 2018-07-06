#include "stdafx.h"
#include "DlgDeptTree.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CDlgDeptTree, CUserDialogBase)

CDlgDeptTree::CDlgDeptTree(const CString& csOrgID,CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DEPT_TREE, pParent)
	,m_csOrgID(csOrgID)
{
	m_hSelItem = nullptr;
}

CDlgDeptTree::~CDlgDeptTree()
{
}

void CDlgDeptTree::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEPT_TREE, m_deptTree);
}


BEGIN_MESSAGE_MAP(CDlgDeptTree, CUserDialogBase)
	ON_NOTIFY(NM_DBLCLK, IDC_DEPT_TREE, &CDlgDeptTree::OnNMDblclkDeptTree)
END_MESSAGE_MAP()

BOOL CDlgDeptTree::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	InitControl();
	InitLayout();

	return TRUE;  
}

void CDlgDeptTree::InitControl()
{
	m_deptTree.SetRedraw(FALSE);

	m_vIDs.RemoveAll();
	m_deptTree.DeleteAllItems();
	m_hSelItem = nullptr;

	//1. 初始化根部门
	std::vector<COrgInfo> depts;
	CUserManagerDataService::GetInstance()->GetDeptNode(_T(""), depts);
	for (size_t i = 0; i < depts.size(); i++)
	{
		COrgInfo& info = depts[i];

		HTREEITEM hRoot = m_deptTree.InsertItem(info.GetOrgName(), -1, -1,NULL);
		m_vIDs[hRoot] = info.GetOrgID();
		if (info.GetOrgID().CompareNoCase(m_csOrgID) == 0)
			m_hSelItem = hRoot;

		//2.初始化子树
		FillChildTree(hRoot, info.GetOrgID());

		m_deptTree.Expand(hRoot, TVE_EXPAND);
	}

	if (m_hSelItem)
		m_deptTree.SelectItem(m_hSelItem);

	m_deptTree.SetRedraw(TRUE);
}

void CDlgDeptTree::FillChildTree(HTREEITEM hRoot, const CString& csParentID)
{
	std::vector<COrgInfo> depts;
	CUserManagerDataService::GetInstance()->GetDeptNode(csParentID, depts);
	for (size_t i = 0; i < depts.size(); i++)
	{
		COrgInfo& info = depts[i];

		HTREEITEM hItem = m_deptTree.InsertItem(info.GetOrgName(), -1, -1, hRoot);
		m_vIDs[hItem] = info.GetOrgID();
		if (info.GetOrgID().CompareNoCase(m_csOrgID) == 0)
			m_hSelItem = hItem;

		//2.初始化子树
		FillChildTree(hItem, info.GetOrgID());
	}
}

void CDlgDeptTree::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_deptTree);

	UpdateLayout(layout);
}


void CDlgDeptTree::OnNMDblclkDeptTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	UINT uFlags = 0;
	HTREEITEM hItem = m_deptTree.HitTest(pt, &uFlags);
													  
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		m_vIDs.Lookup(hItem, m_csOrgID);
		m_csOrgName = m_deptTree.GetItemText(hItem);
		//
		OnOK();
	}

	*pResult = 0;
}
