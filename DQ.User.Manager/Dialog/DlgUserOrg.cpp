#include "stdafx.h"
#include "DlgUserOrg.h"
#include "resource.h"
#include "Dlg_AddOrg.h"
#include "Dlg_AddUser.h"

#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm>  
using namespace std;

// CDlgUserOrg 对话框

IMPLEMENT_DYNAMIC(CDlgUserOrg, CUserDialogBase)

CDlgUserOrg::CDlgUserOrg(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_USER_ORG, pParent)
{

}

CDlgUserOrg::~CDlgUserOrg()
{
}

void CDlgUserOrg::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_USER_ORG, m_tOrgTree);
}

BEGIN_MESSAGE_MAP(CDlgUserOrg, CUserDialogBase)
	ON_NOTIFY(NM_CLICK, IDC_TREE_USER_ORG, &CDlgUserOrg::OnNMClickTreeUserOrg)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_USER_ORG, &CDlgUserOrg::OnNMRClickTreeUserOrg)
	ON_COMMAND(ID_ADD_ORG, &CDlgUserOrg::OnAddOrg)
	ON_COMMAND(ID_DEL_ORG, &CDlgUserOrg::OnDelOrg)
	ON_COMMAND(ID_UPDATE_ORG_NAME, &CDlgUserOrg::OnUpdateOrgName)
	ON_BN_CLICKED(IDC_BTN_ADD_USER, &CDlgUserOrg::OnBnClickedBtnAddUser)
	ON_BN_CLICKED(IDC_BTN_DEL_USER, &CDlgUserOrg::OnBnClickedBtnDelUser)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_USER_ORG, &CDlgUserOrg::OnTvnSelchangedTreeUserOrg)
	ON_BN_CLICKED(IDC_BTN_UPDATE_USER, &CDlgUserOrg::OnBnClickedBtnUpdateUser)
	ON_BN_CLICKED(IDC_BTN_ALL_DELETE, &CDlgUserOrg::OnBnClickedBtnAllDelete)
END_MESSAGE_MAP()



BOOL CDlgUserOrg::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	UpdateData(FALSE);

	CRect rGridRect;
	GetDlgItem(IDC_STATIC_SHOW_USER)->GetWindowRect(rGridRect);
	ScreenToClient(rGridRect);
	m_pGridCtrl = new CBCGPGridCtrl;

	if (!m_pGridCtrl->Create(WS_CHILD | WS_VISIBLE, rGridRect, this, 100))
		return FALSE;

	m_pGridCtrl->EnableMarkSortedColumn(FALSE);
	m_pGridCtrl->EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	m_pGridCtrl->EnableRowHeader(TRUE);
	m_pGridCtrl->EnableLineNumbers();
	m_pGridCtrl->SetClearInplaceEditOnEnter(FALSE);
	m_pGridCtrl->EnableInvertSelOnCtrl();
	m_pGridCtrl->SetScalingRange(0.1, 4.0);

	m_pGridCtrl->InsertColumn(0, _T("用户ID"), globalUtils.ScaleByDPI(60));
	m_pGridCtrl->InsertColumn(1, _T("部门ID"), globalUtils.ScaleByDPI(100));
	m_pGridCtrl->InsertColumn(2, _T("用户名称"), globalUtils.ScaleByDPI(80));

	m_pGridCtrl->AdjustLayout();

	CDataTableMediator* pTable = CUserManagerDataService::GetInstance()->GetOrgInfo();

	//部门填充树控件
	FillBranchTree(pTable, L"", TVI_ROOT);

	//根据树控件部门的选择情况显示部门人员
	ShowBranchUser();

	return TRUE;  
}


void CDlgUserOrg::FillBranchTree(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot)
{
	vector<CUserInfo> VecUserInfo;
	COrgInfo OrgInfo;
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

	int iCount = pTempTable->GetRowCount();
	for (int i = 0; i < iCount; i++)
	{
		OrgInfo.SetDescription(pTempTable->GetStringField(i, L"DESCRIPTION"));
		OrgInfo.SetLeader(pTempTable->GetStringField(i, L"LEADER"));
		OrgInfo.SetLevel(pTempTable->GetStringField(i, L"LEVEL"));
		OrgInfo.SetOrgID(pTempTable->GetStringField(i, L"ORG_ID"));
		OrgInfo.SetOrgName(pTempTable->GetStringField(i, L"ORG_NAME"));
		OrgInfo.SetParentID(pTempTable->GetStringField(i, L"PARENT_ID"));
		OrgInfo.SetShortName(pTempTable->GetStringField(i, L"SHORT_NAME"));

		m_VecOrgInfo.push_back(OrgInfo);

		HTREEITEM hParent = m_tOrgTree.InsertItem(pTempTable->GetStringField(i, L"ORG_NAME"), hRoot);
		m_tOrgTree.SetItemData(hParent, (DWORD_PTR)new CString(pTempTable->GetStringField(i, L"ORG_ID")));

		FillBranchTree(pTable, pTempTable->GetStringField(i, L"ORG_ID"), hParent);
	}
}

void CDlgUserOrg::ShowBranchUser()
{
	CPoint point;
	UINT uFlag;
	//获取屏幕鼠标坐标
	GetCursorPos(&point);  
	//转化成客户坐标
	m_tOrgTree.ScreenToClient(&point);
	//返回与CtreeCtrl关联的光标的当前位置和句柄
	HTREEITEM SelectItem = m_tOrgTree.HitTest(point, &uFlag);
	CString ItemText = m_tOrgTree.GetItemText(SelectItem);
	//根据选中的节点 获取部门对应的用户
	CDataTableMediator* pTab = CUserManagerDataService::GetInstance()->GetBranchUser(ItemText);
	if (pTab)
	{
		int RowCount = pTab->GetRowCount();
		/*同时删除行和列*/
		m_pGridCtrl->DeleteAllColumns();
		m_pGridCtrl->RemoveAll();

		m_pGridCtrl->InsertColumn(0, _T("用户ID"), globalUtils.ScaleByDPI(60));
		m_pGridCtrl->InsertColumn(1, _T("部门ID"), globalUtils.ScaleByDPI(100));
		m_pGridCtrl->InsertColumn(2, _T("用户名称"), globalUtils.ScaleByDPI(80));

		CBCGPGridRow* pRow;
		for (int i = 0; i < RowCount; i++)
		{
			pRow = m_pGridCtrl->CreateRow(m_pGridCtrl->GetColumnCount());

			/*设置行号*/
			pRow->GetItem(0)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_ID"));
			pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"ORG_ID"));
			pRow->GetItem(2)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_NAME"));

			m_pGridCtrl->AddRow(pRow, FALSE);
		}
		m_pGridCtrl->AdjustLayout();
	}
}


void CDlgUserOrg::OnTvnSelchangedTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}



void CDlgUserOrg::OnNMClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowBranchUser();

	*pResult = 0;
}


void CDlgUserOrg::OnNMRClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	//动态加载菜单  
	CMenu menu;
	menu.LoadMenu(IDR_MENU_ORG_OPERATION);
	CPoint pt;
	GetCursorPos(&pt);
	m_tOrgTree.ScreenToClient(&pt);   //将鼠标的屏幕坐标，转换成树形控件的客户区坐标  
	UINT uFlags = 0;
	HTREEITEM hItem = m_tOrgTree.HitTest(pt, &uFlags); //然后做点击测试  
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))     //如果点击的位置是在节点位置上面  
	{
		m_tOrgTree.SelectItem(hItem);
		//根据不同类型的节点弹出菜单  
		CMenu *psubmenu;
		m_tOrgTree.ClientToScreen(&pt);
		psubmenu = menu.GetSubMenu(0);
		psubmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}


void CDlgUserOrg::OnAddOrg()
{
	CDlg_AddOrg dlg;
	dlg.SetOperateType(0);
	if (dlg.DoModal() == IDOK)
	{
		COrgInfo OrgInfo = dlg.GetOrgInfo();
		HTREEITEM hItem = m_tOrgTree.GetSelectedItem();
		CString TreeNodeName = m_tOrgTree.GetItemText(hItem);

		//通过节点名称遍历vector
		vector<COrgInfo>::iterator it = m_VecOrgInfo.begin();
		for (;it != m_VecOrgInfo.end();it++)
		{
			if (it->GetOrgName() == TreeNodeName)
				break;
		}
		//找到：将部门ID作为新建部门的父节点ID 未找到：将新建部门的父节点置为空
		CString TempOrgID = L"";
		if (it != m_VecOrgInfo.end())
			TempOrgID = it->GetOrgID();

		//设置父节点
		OrgInfo.SetParentID(TempOrgID);

		//将添加的部门 更新至数据库
		//TODO:更新数据库时 部门ID
		OrgInfo.SetOrgID(L"BPpPmn2xDX");
		BOOL Result = CUserManagerDataService::GetInstance()->InsertOrgInfo(OrgInfo);
		if (Result)
		{
			m_tOrgTree.InsertItem(OrgInfo.GetOrgName(), hItem, TVI_LAST);
			m_VecOrgInfo.push_back(OrgInfo);
		}
		else
			MessageBox(L"数据不合理，操作失败");
	}
}


void CDlgUserOrg::OnDelOrg()
{
	CString TreeNodeName = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());

	vector<COrgInfo>::iterator it = m_VecOrgInfo.begin();
	for (; it != m_VecOrgInfo.end(); it++)
	{
		if (it->GetOrgName() == TreeNodeName)
			break;
	}
	if (it != m_VecOrgInfo.end())
	{
		//删除数据库数据
		BOOL Result1 = CUserManagerDataService::GetInstance()->DeleteOrgInfo(it->GetOrgID());
		CUserManagerDataService::GetInstance()->DeleteChildOrgInfo(it->GetOrgID());
		if (Result1)
		{
			m_tOrgTree.DeleteItem(m_tOrgTree.GetSelectedItem());
			m_VecOrgInfo.erase(it);
		}
		else
			MessageBox(L"数据不合理，操作失败");
	}
}


void CDlgUserOrg::OnUpdateOrgName()
{
	CDlg_AddOrg dlg;
	dlg.SetOperateType(1);
	//根据节点名称 获取节点信息
	CString TreeNodeName = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());
	vector<COrgInfo>::iterator it = m_VecOrgInfo.begin();
	for (; it != m_VecOrgInfo.end(); it++)
	{
		if (it->GetOrgName() == TreeNodeName)
			break;
	}
	if (it != m_VecOrgInfo.end())
	{
		dlg.SetOrgInfo(*it);
		if (dlg.DoModal() == IDOK)
		{
			COrgInfo OrgInfo = dlg.GetOrgInfo();

			//TODO:
			//更新数据库数据
			BOOL Result = CUserManagerDataService::GetInstance()->UpdateOrgInfo(OrgInfo);
			if (Result)
			{
				m_tOrgTree.SetFocus();
				HTREEITEM hSel = m_tOrgTree.GetSelectedItem();
				CEdit* pEdit = m_tOrgTree.EditLabel(hSel);
				pEdit->SetWindowText(OrgInfo.GetOrgName());
				m_tOrgTree.SetItemText(hSel, OrgInfo.GetOrgName());
				*it = OrgInfo;
			}
			else
				MessageBox(L"数据不合理，操作失败");
		}
	}
}


void CDlgUserOrg::OnBnClickedBtnAddUser()
{
	CDlg_AddUser dlg;
	CString TreeNodeName = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());
	CDataTableMediator* pTab = CUserManagerDataService::GetInstance()->GetOrgInfoUseOrgName(TreeNodeName);

	dlg.SetOperatorType(0);
	dlg.SetOrgName(TreeNodeName);
	if(pTab)
		dlg.SetOrgID(pTab->GetStringField(0, L"ORG_ID"));
	if (dlg.DoModal() == IDOK)
	{
		CUserInfo UserInfo = dlg.GetUserInfo();

		//TODO:测试用
		UserInfo.SetUserID(UserInfo.GetUserNames());

		///添加用户信息
		BOOL Result = CUserManagerDataService::GetInstance()->InsertUserInfo(UserInfo);

		if (Result)
		{
			CBCGPGridRow* pRow;
			pRow = m_pGridCtrl->CreateRow(m_pGridCtrl->GetColumnCount());

			pRow->GetItem(0)->SetValue((_variant_t)UserInfo.GetUserID());
			pRow->GetItem(1)->SetValue((_variant_t)UserInfo.GetOrgID());
			pRow->GetItem(2)->SetValue((_variant_t)UserInfo.GetUserNames());

			m_pGridCtrl->AddRow(pRow, FALSE);
			m_pGridCtrl->AdjustLayout();
		}
		else
			MessageBox(L"数据不合理，操作失败");
	}
}


void CDlgUserOrg::OnBnClickedBtnDelUser()
{
	CString UserID = L"";
	CBCGPGridRow* pCurSelRow = m_pGridCtrl->GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"删除错误，没有选定删除对象");
	}
	else
	{
		for (int i = m_pGridCtrl->GetRowCount() - 1; i >= 0; i--)
		{
			if (m_pGridCtrl->IsRowSelected(i))
			{
				UserID = m_pGridCtrl->GetRow(i)->GetItem(0)->GetValue();

				BOOL Result = CUserManagerDataService::GetInstance()->DeleteUserInfo(UserID);
				if(Result)
					m_pGridCtrl->RemoveRow(i);
				else
					MessageBox(L"数据不合理，操作失败");
			}
		}
	}
}


void CDlgUserOrg::OnBnClickedBtnUpdateUser()
{
	CDlg_AddUser dlg;

	CBCGPGridRow* pRow = NULL;
	CUserInfo UserInfo;
	CString UserID = L"";
	CBCGPGridRow* pCurSelRow = m_pGridCtrl->GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"没有选定删除对象");
	}
	else
	{
		for (int i = m_pGridCtrl->GetRowCount() - 1; i >= 0; i--)
		{
			if (m_pGridCtrl->IsRowSelected(i))
			{
				UserID = m_pGridCtrl->GetRow(i)->GetItem(0)->GetValue();
				pRow = m_pGridCtrl->GetRow(i);
				break;
			}
		}
	}

	CDataTableMediator* pTab = CUserManagerDataService::GetInstance()->GetUserInfoUserUserID(UserID);
	if (pTab)
	{
		UserInfo.SetUserID(pTab->GetStringField(0, L"USER_ID"));
		UserInfo.SetOrgID(pTab->GetStringField(0, L"ORG_ID"));
		UserInfo.SetUserName(pTab->GetStringField(0, L"USER_NAME"));
		UserInfo.SetUserSex(pTab->GetStringField(0, L"USER_SEX"));
		UserInfo.SetUserPw(pTab->GetStringField(0, L"USER_PASSWORD"));
		UserInfo.SetUserEmail(pTab->GetStringField(0, L"USER_EMAIL"));
		UserInfo.SetUserTelephone(pTab->GetStringField(0, L"USER_TELEPHONE"));
		UserInfo.SetUserFax(pTab->GetStringField(0, L"USER_FAX"));
		UserInfo.SetUserMobile(pTab->GetStringField(0, L"USER_MOBILE"));
		UserInfo.SetUserQQ(pTab->GetStringField(0, L"USER_QQ"));
		UserInfo.SetUserMSN(pTab->GetStringField(0, L"USER_MSN"));
		UserInfo.SetDescription(pTab->GetStringField(0, L"DESCRIPTION"));

	}
	
	CString TreeNodeName = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());
	dlg.SetOperatorType(1);
	dlg.SetOrgName(TreeNodeName);
	dlg.SetUserInfo(UserInfo);
	dlg.SetOrgID(UserInfo.GetOrgID());

	if (dlg.DoModal() == IDOK)
	{
		CUserInfo UserInfo = dlg.GetUserInfo();

		///更新用户信息
		BOOL Result = CUserManagerDataService::GetInstance()->UpdateUserInfo(UserInfo);

		if (Result)
		{
			pRow->GetItem(0)->SetValue((_variant_t)UserInfo.GetUserID());
			pRow->GetItem(1)->SetValue((_variant_t)UserInfo.GetOrgID());
			pRow->GetItem(2)->SetValue((_variant_t)UserInfo.GetUserNames());

			m_pGridCtrl->AdjustLayout();
		}
		else
			MessageBox(L"数据不合理，操作失败");
	}


}


void CDlgUserOrg::OnBnClickedBtnAllDelete()
{
	CString UserID;
	for (int i = m_pGridCtrl->GetRowCount(); i >= 0; i--)
	{
		CBCGPGridRow* pCurSelRow = m_pGridCtrl->GetRow(i);
		UserID = pCurSelRow->GetItem(0)->GetValue();

		BOOL Result = CUserManagerDataService::GetInstance()->DeleteUserInfo(UserID);
		if (Result)
			m_pGridCtrl->RemoveRow(i);
		else
			MessageBox(L"数据不合理，操作失败");
	}
}
