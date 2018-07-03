#include "stdafx.h"
#include "ISheet.h"
#include "IRow.h"
using namespace NPOI::SS::Util;

CISheet::CISheet(void)
{
}


CISheet::~CISheet(void)
{
	delete m_ISheet;
}

/** 获取行数 */
int		CISheet::GetRowCount()
{
	return m_ISheet->LastRowNum;
}
/** 获取列数 */
int		CISheet::GetColCount()
{
	return m_ISheet->GetRow(0)->LastCellNum;
}
/** 获取行 */
CIRow *	CISheet::GetRow(int iIndex)
{
	CIRow *pRow = new CIRow();
	pRow->m_IRow = m_ISheet->GetRow(iIndex);
	return pRow;
}
/** 创建行 */
CIRow *	CISheet::CreateRow(int iIndex)
{
	CIRow *pRow = new CIRow();
	pRow->m_IRow = m_ISheet->CreateRow(iIndex);
	return pRow;
}
/** 添加合并 */
void	CISheet::AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol)
{
	m_ISheet->AddMergedRegion(gcnew CellRangeAddress(firstRow, lastRow, firstCol, lastCol));
}
/** 设置列宽度 */
void	CISheet::SetColumnWidth(int iIndex, int iWidth)
{
	m_ISheet->SetColumnWidth(iIndex, iWidth);
}