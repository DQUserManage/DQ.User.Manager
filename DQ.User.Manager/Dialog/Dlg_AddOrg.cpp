// Dlg_AddOrg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_AddOrg.h"
#include "resource.h"


// CDlg_AddOrg 对话框

IMPLEMENT_DYNAMIC(CDlg_AddOrg, CUserDialogModelBase)

CDlg_AddOrg::CDlg_AddOrg(CWnd* pParent /*=NULL*/)
	: CUserDialogModelBase(IDD_DLG_ADD_ORG, pParent)
{
	m_OperateType = -1;
}

CDlg_AddOrg::~CDlg_AddOrg()
{
}

void CDlg_AddOrg::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogModelBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORG_NAME, m_OrgName);
	DDX_Control(pDX, IDC_EDIT_SHORT_NAME, m_ShortName);
	DDX_Control(pDX, IDC_CMB_ORG_LEVEL, m_Level);
	DDX_Control(pDX, IDC_EDIT_ORG_LEADER, m_Leader);
	DDX_Control(pDX, IDC_EDIT_ORG_DESCRIPTION, m_Description);
}


BEGIN_MESSAGE_MAP(CDlg_AddOrg, CUserDialogModelBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddOrg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_AddOrg 消息处理程序
BOOL CDlg_AddOrg::OnInitDialog()
{
	CUserDialogModelBase::OnInitDialog();

	InitLayout();
	//初始化级别下拉框
	m_Level.AddString(L"");
	m_Level.AddString(L"10");
	m_Level.AddString(L"20");
	m_Level.AddString(L"30");
	m_Level.AddString(L"40");

	//根据操作类型 设置标题
	if (m_OperateType == 0)
		this->SetWindowText(L"添加部门信息");
	else if (m_OperateType == 1)
	{
		this->SetWindowText(L"修改部门信息");

		//填充信息
		m_OrgName.SetWindowText(m_OrgInfo.GetOrgName());
		m_ShortName.SetWindowText(m_OrgInfo.GetShortName());
		m_Level.SetWindowText(m_OrgInfo.GetLevel());
		m_Leader.SetWindowText(m_OrgInfo.GetLeader());
		m_Description.SetWindowText(m_OrgInfo.GetDescription());

	}

	return TRUE;
}


void CDlg_AddOrg::InitLayout()
{
	/*CPane layout = pane(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(IDC_STATIC_ORG_NAME, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_EDIT_ORG_NAME, NORESIZE))
		<< itemGrowing(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(IDC_STATIC_ORG_SHORT_NAME, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_EDIT_SHORT_NAME, NORESIZE))
		<< itemGrowing(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(IDC_STATIC_ORG_LEVEL, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_CMB_ORG_LEVEL, NORESIZE))
		<< itemGrowing(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(IDC_STATIC_ORG_LEADER, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_EDIT_ORG_LEADER, NORESIZE))
		<< itemGrowing(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(IDC_STATIC_ORG_DESCRIPTION, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_EDIT_ORG_DESCRIPTION, NORESIZE))
		<< itemGrowing(VERTICAL)
		<< (pane(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDCANCEL, NORESIZE));

	UpdateLayout(layout);*/
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

	//点击确定 获取界面信息
	m_OrgInfo.SetOrgName(OrgName);
	m_OrgInfo.SetShortName(ShortName);
	m_OrgInfo.SetLevel(Level);
	m_OrgInfo.SetLeader(Leader);
	m_OrgInfo.SetDescription(Description);

	CUserDialogModelBase::OnOK();
}



