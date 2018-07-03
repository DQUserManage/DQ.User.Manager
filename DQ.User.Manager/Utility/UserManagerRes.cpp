#include "stdafx.h"
#include "UserManagerRes.h"

CUserManagerResLock::CUserManagerResLock(HINSTANCE hInst)
{
	m_hInst = AfxGetResourceHandle();
	if (NULL != hInst)
		AfxSetResourceHandle(hInst);
}


CUserManagerResLock::~CUserManagerResLock(void)
{
	AfxSetResourceHandle(m_hInst);
}