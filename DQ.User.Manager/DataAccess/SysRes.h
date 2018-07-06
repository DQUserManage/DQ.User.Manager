
#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     SysRes.h                                                       
///  @brief    ϵͳ��Դ���ݷ����ļ�                                                                     
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.04                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
   ϵͳ��Դ���ݷ�����
*/

class EXPORT_USER_MANAGER CSysRes
{
public:
	CSysRes();
	~CSysRes();

public:
	/** �������캯�� */
	CSysRes(const CSysRes& rhs);
	/** ��ֵ������*/
	CSysRes& operator=(const CSysRes& rhs);
public:
	CString  m_csResID;  ///<��ԴID
	CString  m_csName;   ///<��Դ����
	CString  m_csResClass;    ///<��Դ����(��Чѭ����ͼ����)
	CString  m_csContentType;    ///<��������(��Чѭ���ڵ�ͼ��)
	CString  m_csFileName;       ///<�ļ���(��Чѭ������ID)
	COleDateTime  m_dtDevelop;  ///<��������
	CString   m_csAuthor;     ///<����
	CString   m_csVersion;    ///<�汾
	CString   m_csOrgID;      ///<����ID
	CString   m_csOrgName;    ///<��������
};