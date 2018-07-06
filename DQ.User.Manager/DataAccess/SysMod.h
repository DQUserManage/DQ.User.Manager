
#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     SysMod.h                                                       
///  @brief    ϵͳģ�����ݷ����ļ�                                                                     
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.06                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
   ϵͳģ�����ݷ�����
*/

class EXPORT_USER_MANAGER CSysMod
{
public:
	CSysMod();
	~CSysMod();

public:
	/** �������캯�� */
	CSysMod(const CSysMod& rhs);
	/** ��ֵ������*/
	CSysMod& operator=(const CSysMod& rhs);
public:
	CString  m_csModID;  ///<ģ��ID
	CString  m_csName;   ///<ģ������
	CString  m_csModType;    ///<ģ������(�����ġ���塢��ť�����������ڵ�)
	CString   m_csResID;      ///<ϵͳ��ԴID
	CString   m_csResName;    ///<ϵͳ��Դ����

	int  m_nOrder;  ///�ڵ����
};