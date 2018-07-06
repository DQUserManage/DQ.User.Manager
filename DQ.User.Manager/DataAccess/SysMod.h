
#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     SysMod.h                                                       
///  @brief    系统模块数据访问文件                                                                     
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.06                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
   系统模块数据访问类
*/

class EXPORT_USER_MANAGER CSysMod
{
public:
	CSysMod();
	~CSysMod();

public:
	/** 拷贝构造函数 */
	CSysMod(const CSysMod& rhs);
	/** 赋值操作符*/
	CSysMod& operator=(const CSysMod& rhs);
public:
	CString  m_csModID;  ///<模块ID
	CString  m_csName;   ///<模块名称
	CString  m_csModType;    ///<模块类型(上下文、面板、按钮、下拉框、树节点)
	CString   m_csResID;      ///<系统资源ID
	CString   m_csResName;    ///<系统资源名称

	int  m_nOrder;  ///节点序号
};