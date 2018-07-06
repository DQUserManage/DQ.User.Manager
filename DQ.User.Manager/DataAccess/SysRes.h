
#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     SysRes.h                                                       
///  @brief    系统资源数据访问文件                                                                     
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.07.04                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

/**
   系统资源数据访问类
*/

class EXPORT_USER_MANAGER CSysRes
{
public:
	CSysRes();
	~CSysRes();

public:
	/** 拷贝构造函数 */
	CSysRes(const CSysRes& rhs);
	/** 赋值操作符*/
	CSysRes& operator=(const CSysRes& rhs);
public:
	CString  m_csResID;  ///<资源ID
	CString  m_csName;   ///<资源名称
	CString  m_csResClass;    ///<资源分类(无效循环视图类型)
	CString  m_csContentType;    ///<内容类型(无效循环节点图标)
	CString  m_csFileName;       ///<文件名(无效循环报表ID)
	COleDateTime  m_dtDevelop;  ///<开发日期
	CString   m_csAuthor;     ///<作者
	CString   m_csVersion;    ///<版本
	CString   m_csOrgID;      ///<部门ID
	CString   m_csOrgName;    ///<部门名称
};