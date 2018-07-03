#pragma once

#include "DBStructPublic.h"
using namespace NPOI;
using namespace NPOI::SS::UserModel;

class CICellStyle;

class CIRow
{
public:
	CIRow();
	~CIRow(void);

public:
	gcroot<NPOI::SS::UserModel::IRow^>		m_IRow;

public:
	/** 创建Cell */
	int			CreateCell(int iIndex, CellDataType eType);
	/** 设置Cell值 */
	void		SetCellStringVal(int iIndex, CString &sVal);
	/** 设置Cell值 */
	void		SetCellfloatVal(int iIndex, double &fVal);
	/** 设置Cell值（带换行风格） */
	void		SetCellValByWrap(int iIndex, CString &sVal);
	/** 获取Cell值 */
	CString		GetCellVal(int iIndex);
	/** 设置Cell风格 */
	void		SetCellStyle(int iIndex, CICellStyle *pStyle);
	/** 获取总列数 */
	int			GetColCount();
	/** 获取第一个Cell索引 */
	int			GetFirstIndex();

};

