#pragma once

class CIRowMediator;
class CISheet;

class AFX_EXT_CLASS CISheetMediator
{
public:
	CISheetMediator(void);
	~CISheetMediator(void);

public:
	CISheet *	m_pSheet;

private:
	vector<CIRowMediator *>		m_vRowList;

private:
	/** 清空临时行 */
	void		ClearTempRow();

public:
	/** 获取行数 */
	int			GetRowCount();
	/** 获取列数 */
	int			GetColCount();
	/** 获取行 */
	CIRowMediator *		GetRow(int iIndex);
	/** 创建行 */
	CIRowMediator *		CreateRow(int iIndex);
	/** 添加合并 */
	void		AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol);
	/** 设置列宽度 */
	void		SetColumnWidth(int iIndex, int iWidth);
	/**  */

};