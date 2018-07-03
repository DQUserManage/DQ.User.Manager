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
#include "DBStructPublic.h"

class SDbUtility;
class CParameterListMediator;
class CDataTableMediator;
class CDataReaderMediator;

/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 张宪顺
* 创建日期： 2017-03-15
* 功能描述： 数据库操作中介类
*
********************************************************************/
class AFX_EXT_CLASS CDbUtilityMediator
{
public:
	CDbUtilityMediator(CString sConnect, DBConnectType eType);
	~CDbUtilityMediator(void);

private:
	SDbUtility *		m_pDbUtility;
	CString				m_sErrorMessage;		///<

	vector<CParameterListMediator *> m_vParameterList;

private:
	/** 清空临时参数列表 */
	void		ClearParameterList();
public:
	/** 创建参数列表 */
	CParameterListMediator * CreateParameterList();
	/** 打开数据表 */
	CDataTableMediator*	ExecuteTable(CString SQL);
	/** 打开数据表 */
	CDataTableMediator*	ExecuteTable(CString SQL,CParameterListMediator* pList);
	/** 打开数据表 */
	CDataTableMediator*	ExecuteOrclTable(CString SQL);
	/** 打开数据表 */
	CDataTableMediator*	ExecuteOrclTable(CString SQL,CParameterListMediator* pList);
	/** 执行SQL */
	int 				ExecuteQuery(CString SQL);
	/** 执行SQL */
	int 				ExecuteQuery(CString SQL,CParameterListMediator* pList);
	/** 执行SQL */
	int 				ExecuteQuery(CStringArray* SQLList);
	/** 执行SQL */
	int					ExecuteScalar(CString SQL);
	/** 执行存储过程 */
	void				ExecuteProcedure(CString sProcedureName, CParameterListMediator* pList);
	/** 执行Sql读取结果集 */
	CDataReaderMediator*ExecuteReader(CString SQL);

};

/** @}*/
/** @}*/