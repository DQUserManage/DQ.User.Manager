#pragma once

#include "ETSLayout.h"

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserDialogBase.h                                                       ///  @brief    用户管理模块对话框基类文件                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

/** 
	可调整大小对话框基类 （可以动态进行控件布局）
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
	普通对话框基类
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
