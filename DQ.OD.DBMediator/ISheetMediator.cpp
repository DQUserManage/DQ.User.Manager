#include "stdafx.h"
#include "ISheetMediator.h"
#include "IRowMediator.h"
#include "ISheet.h"

CISheetMediator::CISheetMediator(void)
{
}


CISheetMediator::~CISheetMediator(void)
{
	if (m_pSheet)
		delete m_pSheet;
	ClearTempRow();
}

/** 获取行数 */
int		CISheetMediator::GetRowCount()
{
	return m_pSheet->GetRowCount();
}
/** 获取列数 */
int		CISheetMediator::GetColCount()
{
	return m_pSheet->GetColCount();
}
/** 获取行 */
CIRowMediator *	CISheetMediator::GetRow(int iIndex)
{
	CIRowMediator *pRow = new CIRowMediator();
	pRow->m_pRow = m_pSheet->GetRow(iIndex);
	m_vRowList.push_back(pRow);
	return pRow;
}
/** 创建行 */
CIRowMediator *	CISheetMediator::CreateRow(int iIndex)
{
	CIRowMediator *pRow = new CIRowMediator();
	pRow->m_pRow = m_pSheet->CreateRow(iIndex);
	m_vRowList.push_back(pRow);
	return pRow;
}
/** 添加合并 */
void	CISheetMediator::AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol)
{
	m_pSheet->AddMergedRegion(firstRow, lastRow, firstCol, lastCol);
}
/** 设置列宽度 */
void	CISheetMediator::SetColumnWidth(int iIndex, int iWidth)
{
	m_pSheet->SetColumnWidth(iIndex, iWidth);
}

/** 清空临时行 */
void	CISheetMediator::ClearTempRow()
{
	for (int i = 0; i < (int)m_vRowList.size(); i++)
	{
		delete m_vRowList[i];
	}
	m_vRowList.clear();
}