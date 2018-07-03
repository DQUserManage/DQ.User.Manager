#pragma once

#include "DBStructPublic.h"

class CIRow;
class CICellStyleMediator;


class AFX_EXT_CLASS CIRowMediator
{
public:
	CIRowMediator(void);
	~CIRowMediator(void);

public:
	CIRow *		m_pRow;

public:
	/** 创建Cell */
	int			CreateCell(int iIndex, CellDataType eType);
	/** 设置Cell值 */
	void		SetCellStringVal(int iIndex, CString &sVal);
	/** 设置Cell值 */
	void		SetCellfloatVal(int iIndex, double fVal);
	/** 设置Cell值（带换行风格） */
	void		SetCellValByWrap(int iIndex, CString &sVal);
	/** 获取Cell值 */
	CString		GetCellVal(int iIndex);
	/** 设置Cell风格 */
	void		SetCellStyle(int iIndex, CICellStyleMediator *pStyle);
	/** 获取总列数 */
	int			GetColCount();
	/** 获取第一个Cell索引 */
	int			GetFirstIndex();
};

