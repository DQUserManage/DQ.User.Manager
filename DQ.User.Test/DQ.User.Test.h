
// DQ.User.Test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDQUserTestApp: 
// �йش����ʵ�֣������ DQ.User.Test.cpp
//

class CDQUserTestApp : public CBCGPWinApp
{
public:
	CDQUserTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	HINSTANCE  m_hRes;
	virtual int ExitInstance();
};

extern CDQUserTestApp theApp;