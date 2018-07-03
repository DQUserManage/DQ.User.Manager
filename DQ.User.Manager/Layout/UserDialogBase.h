#pragma once

#include "ETSLayout.h"

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserDialogBase.h                                                       ///  @brief    �û�����ģ��Ի�������ļ�                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

/** 
	�ɵ�����С�Ի������ �����Զ�̬���пؼ����֣�
*/
class CUserDialogBase : public ETSLayoutDialog
{
	DECLARE_DYNAMIC(CUserDialogBase)

public:
	CUserDialogBase(UINT nID,CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserDialogBase();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

/**
	��ͨ�Ի������
*/
class CUserDialogModelBase : public CBCGPDialog
{
	DECLARE_DYNAMIC(CUserDialogModelBase)

public:
	CUserDialogModelBase(UINT nID,CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserDialogModelBase();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
