#include "stdafx.h"
#include "UserManager.h"
#include "../Utility/UserManagerRes.h"

#include "../Dialog/Dlg_UserInfo.h"
#include "../Dialog/Dlg_OrgInfo.h"
#include "../Dialog/DlgSysRes.h"
#include "../Dialog/DlgSysMod.h"
#include "../Dialog/Dlg_RoleInfo.h"

CDQUserManager* CDQUserManager::m_pInst = nullptr;

CDQUserManager* CDQUserManager::GetInstance()
{
	if (!m_pInst)
		m_pInst = new CDQUserManager;

	return m_pInst;
}

void CDQUserManager::DestroyInstance()
{
	if (m_pInst)
	{
		delete m_pInst;
		m_pInst = nullptr;
	}
}

CDQUserManager::~CDQUserManager()
{

}

//----------------------------
BOOL CDQUserManager::DoUserSettings()
{
	CUserManagerResLock res(gInst);

	CDlg_UserInfo dlg;
	return dlg.DoModal() == IDOK;
}

BOOL CDQUserManager::DoOrgSettings()
{
	CUserManagerResLock res(gInst);

	CDlg_OrgInfo dlg;
	return dlg.DoModal() == IDOK;
}

BOOL CDQUserManager::DoRoleSettings()
{
	CUserManagerResLock res(gInst);

	CDlg_RoleInfo dlg;
	return dlg.DoModal() == IDOK;
}

BOOL CDQUserManager::DoSysResSettings()
{
	CUserManagerResLock res(gInst);

	CDlgSysRes dlg;
	return dlg.DoModal() == IDOK;
}

BOOL CDQUserManager::DoSysModSettings()
{
	CUserManagerResLock res(gInst);

	CDlgSysMod dlg;
	return dlg.DoModal() == IDOK;
}

