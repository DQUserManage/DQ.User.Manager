#include "stdafx.h"
#include "IRowMediator.h"
#include "IRow.h"
#include "ICellStyleMediator.h"


CIRowMediator::CIRowMediator(void)
{
}


CIRowMediator::~CIRowMediator(void)
{
	if (m_pRow)
		delete m_pRow;
}

/** 创建Cell */
int		CIRowMediator::CreateCell(int iIndex, CellDataType eType)
{
	return m_pRow->CreateCell(iIndex, eType);
}
/** 设置Cell值 */
void	CIRowMediator::SetCellStringVal(int iIndex, CString &sVal)
{
	m_pRow->SetCellStringVal(iIndex, sVal);
}
/** 设置Cell值 */
void	CIRowMediator::SetCellfloatVal(int iIndex, double fVal)
{
	m_pRow->SetCellfloatVal(iIndex, fVal);
}
/** 设置Cell值（带换行风格） */
void	CIRowMediator::SetCellValByWrap(int iIndex, CString &sVal)
{
	m_pRow->SetCellValByWrap(iIndex, sVal);
}
/** 获取Cell值 */
CString	CIRowMediator::GetCellVal(int iIndex)
{
	return m_pRow->GetCellVal(iIndex);
}
/** 设置Cell风格 */
void	CIRowMediator::SetCellStyle(int iIndex, CICellStyleMediator *pStyle)
{
	m_pRow->SetCellStyle(iIndex, pStyle->m_pCellStyle);
}
/** 获取总列数 */
int		CIRowMediator::GetColCount()
{
	return m_pRow->GetColCount();
}
/** 获取第一个Cell索引 */
int		CIRowMediator::GetFirstIndex()
{
	return m_pRow->GetFirstIndex();
}