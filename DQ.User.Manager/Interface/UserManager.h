
#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     UserManager.h                                                       
///  @brief    �û�����GUI���ʽӿ�                                                                             
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.06.28                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
	�û�����GUI�����ࣨ����ģʽ��
*/
class EXPORT_USER_MANAGER CDQUserManager
{
public:
	~CDQUserManager();

public:
	static CDQUserManager* GetInstance();
	static void DestroyInstance();

public:
	/** �û���Ϣ���� */
	BOOL DoUserSettings();

	/** ������Ϣ���� */
	BOOL DoOrgSettings();

	/** ��ɫ��Ϣ���� */
	BOOL DoRoleSettings();

	/** ϵͳ��Դ���� */
	BOOL DoSysResSettings();

	/** ϵͳģ������ */
	BOOL DoSysModSettings();

private:
	CDQUserManager() {}
	CDQUserManager(const CDQUserManager& rhs) { operator=(rhs); }
	CDQUserManager& operator=(const CDQUserManager& rhs) { return *this; }
private:
	static CDQUserManager* m_pInst;   ///<�û�����ģ�����ʵ��

};