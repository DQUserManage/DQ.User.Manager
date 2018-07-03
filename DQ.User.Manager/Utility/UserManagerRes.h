#pragma once

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserManagerRes.h                                                       ///  @brief    资源管理文件                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

/**
	用户管理资源锁（用于应用程序和dll之间资源切换）
*/
class CUserManagerResLock
{
public:
	/** 资源切换
	@param hInst 设置为当前资源的有效句柄
	*/
	CUserManagerResLock(HINSTANCE hInst);

	/** 恢复原先的资源句柄*/
	~CUserManagerResLock(void);
private:
	HINSTANCE m_hInst;  ///<旧的资源句柄
};