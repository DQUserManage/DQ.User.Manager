// Dlg_RoleInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_RoleInfo.h"
#include "resource.h"
#include "Dlg_AddRoleInfo.h"


// CDlg_RoleInfo 对话框

IMPLEMENT_DYNAMIC(CDlg_RoleInfo, CUserDialogBase)

CDlg_RoleInfo::CDlg_RoleInfo(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ROLE_INFO, pParent)
{

}

CDlg_RoleInfo::~CDlg_RoleInfo()
{
}

void CDlg_RoleInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_RoleInfo, CUserDialogBase)
	ON_BN_CLICKED(IDC_BTN_ADD_ROLE, &CDlg_RoleInfo::OnBnClickedBtnAddRole)
	ON_BN_CLICKED(IDC_BTN_DEL_ROLE, &CDlg_RoleInfo::OnBnClickedBtnDelRole)
	ON_BN_CLICKED(IDC_BTN_UPDATE_ROLE_INFO, &CDlg_RoleInfo::OnBnClickedBtnUpdateRoleInfo)
END_MESSAGE_MAP()


// CDlg_RoleInfo 消息处理程序
BOOL CDlg_RoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	CRect rGridRect;
	GetDlgItem(IDC_STATIC_SHOW_ROLE)->GetWindowRect(rGridRect);
	ScreenToClient(rGridRect);

	if (!m_GridCtrl.Create(WS_CHILD | WS_VISIBLE, rGridRect, this, 100))
		return FALSE;

	m_GridCtrl.EnableMarkSortedColumn(FALSE);
	m_GridCtrl.EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	m_GridCtrl.EnableRowHeader(TRUE);
	m_GridCtrl.EnableLineNumbers();
	m_GridCtrl.SetClearInplaceEditOnEnter(FALSE);
	m_GridCtrl.EnableInvertSelOnCtrl();
	m_GridCtrl.SetScalingRange(0.1, 4.0);

	m_GridCtrl.InsertColumn(0, _T("选择"), globalUtils.ScaleByDPI(40));
	m_GridCtrl.InsertColumn(1, _T("角色ID"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(2, _T("角色"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(3, _T("备注"), globalUtils.ScaleByDPI(100));

	//查询数据库获取用户信息
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetRoleInfo());

	CBCGPGridRow* pRow;
	for (int i = 0; i < pTab->GetRowCount(); i++)
	{
		pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

		/*设置行号*/
		pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
		pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"ROLE_ID"));
		pRow->GetItem(2)->SetValue((_variant_t)pTab->GetStringField(i, L"ROLE_NAME"));
		pRow->GetItem(3)->SetValue((_variant_t)pTab->GetStringField(i, L"DESCRIPTION"));

		m_GridCtrl.AddRow(pRow, FALSE);
	}

	m_GridCtrl.AdjustLayout();

	return TRUE;
}


void CDlg_RoleInfo::OnBnClickedBtnAddRole()
{
	CDlg_AddRoleInfo dlg;
	dlg.SetOperateType(0);
	if (dlg.DoModal() == IDOK)
	{
		vector<CString> RolePower = dlg.GetRolePower();
		CString RoleID = CUserUtility::GenerateUniqueStr(10);
		CString RoleName = dlg.GetRoleName();
		CString Description = dlg.GetRoleDescription();
		CRoleInfo RoleInfo;
		RoleInfo.SetRoleName(RoleName);
		RoleInfo.SetRoleID(RoleID);
		RoleInfo.SetRemark(Description);

		//添加角色表数据
		BOOL Result = CUserManagerDataService::GetInstance()->InsertRoleInfo(RoleInfo);

		//添加角色--权限 TODO:
		for (int i = 0; i < RolePower.size(); i++)
		{
			Result = CUserManagerDataService::GetInstance()->InsertPowerRoleInfo(RoleInfo, RolePower[i]);
			if (!Result)
				break;
		}

		if (Result)
		{
			CBCGPGridRow* pRow;
			pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

			/*设置行号*/
			pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
			pRow->GetItem(1)->SetValue((_variant_t)RoleInfo.GetRoleID());
			pRow->GetItem(2)->SetValue((_variant_t)RoleInfo.GetRoleName());
			pRow->GetItem(3)->SetValue((_variant_t)RoleInfo.GetRemark());

			m_GridCtrl.AddRow(pRow, FALSE);
			m_GridCtrl.AdjustLayout();
		}
		else
			MessageBox(L"数据不合理，操作失败");
	}
}


void CDlg_RoleInfo::OnBnClickedBtnDelRole()
{
	CString RoleID = L"";
	CBCGPGridRow* pCurSelRow = m_GridCtrl.GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"删除错误，没有选定删除对象");
	}
	else
	{
		for (int i = m_GridCtrl.GetRowCount() - 1; i >= 0; i--)
		{
			pCurSelRow = m_GridCtrl.GetRow(i);
			if (((CBCGPGridCheckItem*)pCurSelRow->GetItem(0))->GetState() == 1)
			{
				RoleID = m_GridCtrl.GetRow(i)->GetItem(1)->GetValue();

				BOOL Result = CUserManagerDataService::GetInstance()->DeleteRoleInfo(RoleID);
				if (Result)
					m_GridCtrl.RemoveRow(i);
				else
					MessageBox(L"数据不合理，操作失败");
			}
		}
	}
}


void CDlg_RoleInfo::OnBnClickedBtnUpdateRoleInfo()
{
	CBCGPGridRow* pRow = NULL;
	CString RoleID = L"";
	CBCGPGridRow* pCurSelRow = m_GridCtrl.GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"删除错误，没有选定删除对象");
	}
	else
	{
		for (int i = m_GridCtrl.GetRowCount() - 1; i >= 0; i--)
		{
			pCurSelRow = m_GridCtrl.GetRow(i);
			if (((CBCGPGridCheckItem*)pCurSelRow->GetItem(0))->GetState() == 1)
			{
				RoleID = m_GridCtrl.GetRow(i)->GetItem(1)->GetValue();
				pRow = m_GridCtrl.GetRow(i);
				break;
			}
		}
	}

	CDlg_AddRoleInfo dlg;
	dlg.SetOperateType(1);
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetRoleInfoUseID(RoleID));
	dlg.SerRoleID(pTab->GetStringField(0, L"ROLE_ID"));
	if (dlg.DoModal() == IDOK)
	{
		//更新数据
		vector<CString> RolePower = dlg.GetRolePower();
		CString RoleID = dlg.GetRoleID();
		CString RoleName = dlg.GetRoleName();
		CString Description = dlg.GetRoleDescription();
		CRoleInfo RoleInfo;
		RoleInfo.SetRoleName(RoleName);
		RoleInfo.SetRoleID(RoleID);
		RoleInfo.SetRemark(Description);

		//更新角色信息
		BOOL Result = CUserManagerDataService::GetInstance()->UpdateRoleInfo(RoleInfo);

		//更新角色--权限 用户角色:
		for (int i = 0; i < RolePower.size(); i++)
		{
			//先删除后更新
			Result = CUserManagerDataService::GetInstance()->DelPowerRoleInfo(RoleInfo);
			Result = CUserManagerDataService::GetInstance()->InsertPowerRoleInfo(RoleInfo, RolePower[i]);
			if (!Result)
				break;
		}

		if (Result)
		{
			/*设置行号*/
			pRow->ReplaceItem(0, new CBCGPGridCheckItem(TRUE));
			pRow->GetItem(1)->SetValue((_variant_t)RoleInfo.GetRoleID());
			pRow->GetItem(2)->SetValue((_variant_t)RoleInfo.GetRoleName());
			pRow->GetItem(3)->SetValue((_variant_t)RoleInfo.GetRemark());

			m_GridCtrl.AdjustLayout();
		}
		else
			MessageBox(L"数据不合理，操作失败");

	}
}
