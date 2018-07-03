#include "stdafx.h"
#include "DlgUserOrg.h"
#include "resource.h"

// CDlgUserOrg ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CDlgUserOrg, CUserDialogBase)

CDlgUserOrg::CDlgUserOrg(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_USER_ORG, pParent)
{

}

CDlgUserOrg::~CDlgUserOrg()
{
}

void CDlgUserOrg::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgUserOrg, CUserDialogBase)
END_MESSAGE_MAP()



BOOL CDlgUserOrg::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;  
}
