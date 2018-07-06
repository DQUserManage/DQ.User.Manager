#include "stdafx.h"
#include "CustomControl.h"

#include "Dialog/DlgDeptTree.h"
#include "Dialog/DlgSelRes.h"

void CDeptBrowserEdit::OnBrowse()
{
	CUserManagerResLock res(gInst);

	CDlgDeptTree dlg(m_csDeptID);
	if (dlg.DoModal() != IDOK)
		return;

	m_csDeptID = dlg.m_csOrgID;
	SetWindowText(dlg.m_csOrgName);
}

//----------------------------------------
void CResBrowserEdit::OnBrowse()
{
	CUserManagerResLock res(gInst);

	CDlgSelRes dlg(m_csResID);
	if (dlg.DoModal() != IDOK)
		return;

	m_csResID = dlg.m_csResID;
	SetWindowText(dlg.m_csResName);
}