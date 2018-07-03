#pragma once

using namespace NPOI;
using namespace NPOI::SS::UserModel;

class CIRow;

class CISheet
{
public:
	CISheet(void);
	~CISheet(void);

public:
	gcroot<ISheet ^>	m_ISheet;

public:
	/** 获取行数 */
	int			GetRowCount();
	/** 获取列数 */
	int			GetColCount();
	/** 获取行 */
	CIRow *		GetRow(int iIndex);
	/** 创建行 */
	CIRow *		CreateRow(int iIndex);
	/** 添加合并 */
	void		AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol);
	/** 设置列宽度 */
	void		SetColumnWidth(int iIndex, int iWidth);

};

