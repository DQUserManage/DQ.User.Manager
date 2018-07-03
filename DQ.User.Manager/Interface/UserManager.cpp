#include "stdafx.h"
#include "UserManager.h"
#include "../Utility/UserManagerRes.h"

#include "../Dialog/DlgUserOrg.h"

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
BOOL CDQUserManager::DoUserOrgSettings()
{
	CUserManagerResLock res(gInst);

	CDlgUserOrg dlg;
	return dlg.DoModal() == IDOK;
}

