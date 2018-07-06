
#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     UserManager.h                                                       
///  @brief    用户管理GUI访问接口                                                                             
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.06.28                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
	用户管理GUI访问类（单例模式）
*/
class EXPORT_USER_MANAGER CDQUserManager
{
public:
	~CDQUserManager();

public:
	static CDQUserManager* GetInstance();
	static void DestroyInstance();

public:
	/**  组织机构设置 */
	BOOL DoUserOrgSettings();

	/** 系统资源设置 */
	BOOL DoSysResSettings();

	/** 系统模块设置 */
	BOOL DoSysModSettings();

private:
	CDQUserManager() {}
	CDQUserManager(const CDQUserManager& rhs) { operator=(rhs); }
	CDQUserManager& operator=(const CDQUserManager& rhs) { return *this; }
private:
	static CDQUserManager* m_pInst;   ///<用户管理模块访问实例

};