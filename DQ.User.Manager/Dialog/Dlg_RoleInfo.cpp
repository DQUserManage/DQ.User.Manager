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
	m_GridCtrl.InsertColumn(1, _T("角色"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(2, _T("备注"), globalUtils.ScaleByDPI(100));

	//查询数据库获取用户信息
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetRoleInfo());

	CBCGPGridRow* pRow;
	for (int i = 0; i < pTab->GetRowCount(); i++)
	{
		pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

		/*设置行号*/
		pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
		pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"ROLE_NAME"));
		pRow->GetItem(2)->SetValue((_variant_t)pTab->GetStringField(i, L"DESCRIPTION"));

		m_GridCtrl.AddRow(pRow, FALSE);
	}

	m_GridCtrl.AdjustLayout();

	return TRUE;
}


void CDlg_RoleInfo::OnBnClickedBtnAddRole()
{
	CDlg_AddRoleInfo dlg;
	if (dlg.DoModal() == IDOK)
	{
		//添加权限表数据

		//添加角色--权限 TODO:
	}
}


void CDlg_RoleInfo::OnBnClickedBtnDelRole()
{
	// TODO: 在此添加控件通知处理程序代码
}
