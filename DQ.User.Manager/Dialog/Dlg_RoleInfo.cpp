// Dlg_RoleInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_RoleInfo.h"
#include "resource.h"
#include "Dlg_AddRoleInfo.h"


// CDlg_RoleInfo �Ի���

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


// CDlg_RoleInfo ��Ϣ�������
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

	m_GridCtrl.InsertColumn(0, _T("ѡ��"), globalUtils.ScaleByDPI(40));
	m_GridCtrl.InsertColumn(1, _T("��ɫ"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(2, _T("��ע"), globalUtils.ScaleByDPI(100));

	//��ѯ���ݿ��ȡ�û���Ϣ
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetRoleInfo());

	CBCGPGridRow* pRow;
	for (int i = 0; i < pTab->GetRowCount(); i++)
	{
		pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

		/*�����к�*/
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
		//���Ȩ�ޱ�����

		//��ӽ�ɫ--Ȩ�� TODO:
	}
}


void CDlg_RoleInfo::OnBnClickedBtnDelRole()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
