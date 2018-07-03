/**
* @defgroup 
* @author   张宪顺
* @version  1.0
* @date     2017-03-15
* @{
*/


/**
* @file
* @brief
* @author   张宪顺
* @date     2017-03-15
* @version  1.0
* @note
* @{
*/
#pragma once

#include "CSharpNameSpace.h"
#include "DBStructPublic.h"

/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 张宪顺
* 创建日期： 2017-03-15
* 功能描述： 参数列表类
*
********************************************************************/
class CParameterList
{
public:
	CParameterList(void);
	~CParameterList(void);
public:
	gcroot<DbUtility^> m_db;	///<数据库连接对象
private:
	CArray <ParameterInfo, ParameterInfo> m_ParameterList;	///<参数列表
public:	
	/** 清空参数 */
	void		Clear();
	/** 获取参数个数 */
	int			GetCount();
	/** 添加参数 */
	void		AddParameter(CString mParameterName,COleVariant  mParameterValue);
	void		AddParameter(CString mParameterName, byte *pByte, int iByteSize);
	/** 获取参数列表 */
	List<DbParameter^>^ GetList();
};

/** @}*/
/** @}*/