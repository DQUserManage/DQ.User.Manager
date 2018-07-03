
// DQ.User.Test.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "DQ.User.Test.h"
#include "DQ.User.TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDQUserTestApp

BEGIN_MESSAGE_MAP(CDQUserTestApp, CBCGPWinApp)
	ON_COMMAND(ID_HELP, &CBCGPWinApp::OnHelp)
END_MESSAGE_MAP()


// CDQUserTestApp 构造

CDQUserTestApp::CDQUserTestApp()
{
	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;

	SetVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLUE);

	m_hRes = NULL;
}

CDQUserTestApp theApp;


// CDQUserTestApp 初始化

BOOL CDQUserTestApp::InitInstance()
{
	CBCGPWinApp::InitInstance();

	SetRegistryKey(_T("BYSoft"));
	SetRegistryBase(_T("Settings"));

	m_hRes = ::LoadLibrary(_T("BCGCBProResCHS.dll"));
	if (!m_hRes)
		return FALSE;

	BCGCBProSetResourceHandle(m_hRes);

	CDQUserTestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	return FALSE;
}

int CDQUserTestApp::ExitInstance()
{
	if (m_hRes)
		::FreeLibrary(m_hRes);

	return CBCGPWinApp::ExitInstance();
}
