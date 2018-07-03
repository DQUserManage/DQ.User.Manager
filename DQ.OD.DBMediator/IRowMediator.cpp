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

/** ����Cell */
int		CIRowMediator::CreateCell(int iIndex, CellDataType eType)
{
	return m_pRow->CreateCell(iIndex, eType);
}
/** ����Cellֵ */
void	CIRowMediator::SetCellStringVal(int iIndex, CString &sVal)
{
	m_pRow->SetCellStringVal(iIndex, sVal);
}
/** ����Cellֵ */
void	CIRowMediator::SetCellfloatVal(int iIndex, double fVal)
{
	m_pRow->SetCellfloatVal(iIndex, fVal);
}
/** ����Cellֵ�������з�� */
void	CIRowMediator::SetCellValByWrap(int iIndex, CString &sVal)
{
	m_pRow->SetCellValByWrap(iIndex, sVal);
}
/** ��ȡCellֵ */
CString	CIRowMediator::GetCellVal(int iIndex)
{
	return m_pRow->GetCellVal(iIndex);
}
/** ����Cell��� */
void	CIRowMediator::SetCellStyle(int iIndex, CICellStyleMediator *pStyle)
{
	m_pRow->SetCellStyle(iIndex, pStyle->m_pCellStyle);
}
/** ��ȡ������ */
int		CIRowMediator::GetColCount()
{
	return m_pRow->GetColCount();
}
/** ��ȡ��һ��Cell���� */
int		CIRowMediator::GetFirstIndex()
{
	return m_pRow->GetFirstIndex();
}