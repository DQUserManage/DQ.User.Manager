#include "stdafx.h"
#include "DlgSysMod.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CDlgSysMod, CUserDialogBase)

CDlgSysMod::CDlgSysMod(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_SYS_MOD, pParent)
{

}

CDlgSysMod::~CDlgSysMod()
{
}

void CDlgSysMod::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOD_TREE, m_wndMod);
}


BEGIN_MESSAGE_MAP(CDlgSysMod, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlgSysMod::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgSysMod::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	InitLayout();

	UpdateData(FALSE);

	return TRUE;  
}

void CDlgSysMod::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_wndMod)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE));

	UpdateLayout(layout);
}

void CDlgSysMod::OnBnClickedOk()
{
	CUserDialogBase::OnOK();
}
