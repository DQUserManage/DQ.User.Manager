// Dlg_AddOrg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_AddOrg.h"
#include "resource.h"


// CDlg_AddOrg �Ի���

IMPLEMENT_DYNAMIC(CDlg_AddOrg, CUserDialogBase)

CDlg_AddOrg::CDlg_AddOrg(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ADD_ORG, pParent)
{
	m_OperateType = -1;
}

CDlg_AddOrg::~CDlg_AddOrg()
{
}

void CDlg_AddOrg::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORG_NAME, m_OrgName);
	DDX_Control(pDX, IDC_EDIT_SHORT_NAME, m_ShortName);
	DDX_Control(pDX, IDC_CMB_ORG_LEVEL, m_Level);
	DDX_Control(pDX, IDC_EDIT_ORG_LEADER, m_Leader);
	DDX_Control(pDX, IDC_EDIT_ORG_DESCRIPTION, m_Description);
}


BEGIN_MESSAGE_MAP(CDlg_AddOrg, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddOrg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddOrg ��Ϣ�������
BOOL CDlg_AddOrg::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	//��ʼ������������
	m_Level.AddString(L"");
	m_Level.AddString(L"10");
	m_Level.AddString(L"20");
	m_Level.AddString(L"30");
	m_Level.AddString(L"40");

	//���ݲ������� ���ñ���
	if (m_OperateType == 0)
		this->SetWindowText(L"��Ӳ�����Ϣ");
	else if (m_OperateType == 1)
	{
		this->SetWindowText(L"�޸Ĳ�����Ϣ");

		//�����Ϣ
		m_OrgName.SetWindowText(m_OrgInfo.GetOrgName());
		m_ShortName.SetWindowText(m_OrgInfo.GetShortName());
		m_Level.SetWindowText(m_OrgInfo.GetLevel());
		m_Leader.SetWindowText(m_OrgInfo.GetLeader());
		m_Description.SetWindowText(m_OrgInfo.GetDescription());

	}

	return TRUE;
}


void CDlg_AddOrg::OnBnClickedOk()
{
	CString OrgName = L"" , ShortName = L"", Level = L"", Leader = L"", Description = L"";
	m_OrgName.GetWindowText(OrgName);
	m_ShortName.GetWindowText(ShortName);

	int index = m_Level.GetCurSel();
	if(index != -1)
		m_Level.GetLBText(index,Level);
	m_Leader.GetWindowText(Leader);
	m_Description.GetWindowText(Description);

	//���ȷ�� ��ȡ������Ϣ
	m_OrgInfo.SetOrgName(OrgName);
	m_OrgInfo.SetShortName(ShortName);
	m_OrgInfo.SetLevel(Level);
	m_OrgInfo.SetLeader(Leader);
	m_OrgInfo.SetDescription(Description);

	CUserDialogBase::OnOK();
}



