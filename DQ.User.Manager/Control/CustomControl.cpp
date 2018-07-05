#include "stdafx.h"
#include "CustomControl.h"

#include "Dialog/DlgDeptTree.h"

void CDeptBrowserEdit::OnBrowse()
{
	CUserManagerResLock res(gInst);

	CDlgDeptTree dlg(m_csDeptID);
	if (dlg.DoModal() != IDOK)
		return;

	m_csDeptID = dlg.m_csOrgID;
	SetWindowText(dlg.m_csOrgName);
}