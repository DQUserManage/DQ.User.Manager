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

/** ��ȡ���� */
int		CISheet::GetRowCount()
{
	return m_ISheet->LastRowNum;
}
/** ��ȡ���� */
int		CISheet::GetColCount()
{
	return m_ISheet->GetRow(0)->LastCellNum;
}
/** ��ȡ�� */
CIRow *	CISheet::GetRow(int iIndex)
{
	CIRow *pRow = new CIRow();
	pRow->m_IRow = m_ISheet->GetRow(iIndex);
	return pRow;
}
/** ������ */
CIRow *	CISheet::CreateRow(int iIndex)
{
	CIRow *pRow = new CIRow();
	pRow->m_IRow = m_ISheet->CreateRow(iIndex);
	return pRow;
}
/** ��Ӻϲ� */
void	CISheet::AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol)
{
	m_ISheet->AddMergedRegion(gcnew CellRangeAddress(firstRow, lastRow, firstCol, lastCol));
}
/** �����п�� */
void	CISheet::SetColumnWidth(int iIndex, int iWidth)
{
	m_ISheet->SetColumnWidth(iIndex, iWidth);
}