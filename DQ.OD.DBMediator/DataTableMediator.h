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


class SDataTable;

/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 张宪顺
* 创建日期： 2017-03-15
* 功能描述： DataTable中介类，外部全部使用该类，可以避免每一个类都要用CLR模式
*
********************************************************************/
class AFX_EXT_CLASS CDataTableMediator
{
public:
	CDataTableMediator(CString sTableName = L"table1");
	~CDataTableMediator(void);

public:
	SDataTable *					m_pDataTable;
private:
	//vector<byte *>					m_vByteList;
	vector<CDataTableMediator *>	m_vTableList;

public:
	/** 清空临时的Byte对象 */
	//void		ClearTempByte();
	/** 清空临时的table对象 */
	void		ClearTempTable();

public:
	/** 设置表名 */
	void		SetTableName(CString m_TableName);
	/** 获取表名 */
	CString		GetTableName();
	/** 过滤 */
	CDataTableMediator * FilterReturnTable(CString sFilter);
	/** 获取列名称 */
	CString		GetsFieldName(int iIndex);
	/** 获取列数据烈性 */
	CString		GetColDataType(int iIndex);
	/** 获取列个数 */
	int			GetColCount();
	/** 获取行个数 */
	int			GetRowCount();
	/** 添加行 */
	int			AddRow();
	/** 添加列 */
	int			AddCol(CString sColName);
	 
public:
	/** 设置数值 */
	void		SetFieldValue(int iRowIndex, int iColIndex, COleVariant val);
	void		SetFieldValue(int iRowIndex, CString sFiledName, COleVariant val);
	/** 获取字符型数值 */
	CString		GetStringField(int iRowIndex, CString sFieldName);
	CString		GetStringField(int iRowIndex, int iColIndex);
	/** 获取整型数值 */
	int			GetIntField(int iRowIndex, int iColIndex);
	int			GetIntField(int iRowIndex, CString sFieldName);
	/** 获取浮点数值 */
	float		GetFloatField(int iRowIndex, int iColIndex);
	float		GetFloatField(int iRowIndex, CString sFieldName);
	/** 获取日期数值 */
	COleDateTime GetDateField(int iRowIndex, int iColIndex);	
	COleDateTime GetDateField(int iRowIndex, CString sFieldName);	
	/** 获取BLOB数值 */
	byte*		GetBlobField(int iRowIndex, int iColIndex,int &size);
	CString		GetBlobField(int iRowIndex, CString sFieldName);
	byte*		GetBlobField(int iRowIndex, CString sFieldName,int &size);

};

/** @}*/
/** @}*/