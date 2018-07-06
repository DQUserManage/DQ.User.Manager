#include "stdafx.h"
#include "DlgModeInfo.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CDlgModeInfo, CUserDialogModelBase)

CDlgModeInfo::CDlgModeInfo(CSysMod& mod, bool bEdit,CWnd* pParent /*=NULL*/)
	: CUserDialogModelBase(IDD_MOD_SET, pParent)
	, m_bEdit(bEdit)
	, m_SysMod(mod)
{

}

CDlgModeInfo::~CDlgModeInfo()
{
}

void CDlgModeInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogModelBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_NAME, m_SysMod.m_csName);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_SysMod.m_csModType);
	DDX_Control(pDX, IDC_EDT_RES, m_wndRes);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_wndType);
}


BEGIN_MESSAGE_MAP(CDlgModeInfo, CUserDialogModelBase)
	ON_BN_CLICKED(IDOK, &CDlgModeInfo::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgModeInfo::OnInitDialog()
{
	CUserDialogModelBase::OnInitDialog();

	CString csTitle;
	csTitle.Format(_T("模块信息 - %s"), m_bEdit ? _T("编辑") : _T("新建"));
	SetWindowText(csTitle);

	//
	m_wndRes.m_csResID = m_SysMod.m_csModID;
	m_wndRes.SetWindowText(m_SysMod.m_csResName);
	m_wndRes.EnableBrowseButton();
	m_wndType.SetCurSel(0);
	//
	UpdateData(FALSE);

	return TRUE;  
}

void CDlgModeInfo::OnBnClickedOk()
{
	if (!UpdateData())
	{
		UpdateData(FALSE);
		return;
	}

	if (m_SysMod.m_csName.IsEmpty())
	{
		CUserUtility::ShowMessageBox(_T("模块名称不能为空!"));
		return;
	}

	m_SysMod.m_csResID = m_wndRes.m_csResID;
	m_wndRes.GetWindowText(m_SysMod.m_csResName);
	//
	CUserDialogModelBase::OnOK();
}
