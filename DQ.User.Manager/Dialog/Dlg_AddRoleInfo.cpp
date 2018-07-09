// Dlg_AddRoleInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_AddRoleInfo.h"
#include "resource.h"


// CDlg_AddRoleInfo �Ի���

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


// CDlg_AddRoleInfo ��Ϣ�������
BOOL CDlg_AddRoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	//��ʼ����ɫȨ��
	std::shared_ptr<CDataTableMediator> pTable = CUserManagerDataService::GetInstance()->GetOrgInfo();

	//����������ؼ�
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
