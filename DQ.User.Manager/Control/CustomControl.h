#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     CustomEdit.h                                                       
///  @brief    �Զ���༭�����ļ�                                                                             
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.05                                                                               
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
      ѡ���ű༭�ؼ�
*/
class EXPORT_USER_MANAGER CDeptBrowserEdit : public CBCGPEdit
{
public:
	/** ������������ʾ����*/
	virtual void OnBrowse();

public:
	CString m_csDeptID;  ///<����ID
};

/**
	ѡ��ϵͳ��Դ�༭�ؼ�
*/
class EXPORT_USER_MANAGER CResBrowserEdit : public CBCGPEdit
{
public:
	/** ����ϵͳ��Դ��ʾ����*/
	virtual void OnBrowse();

public:
	CString m_csResID;  ///<��ԴID
};