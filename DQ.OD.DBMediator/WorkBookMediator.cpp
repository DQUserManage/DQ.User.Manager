#include "stdafx.h"
#include "WorkBookMediator.h"
#include "ISheetMediator.h"
#include "ICellStyleMediator.h"
#include "BaseWorkBook.h"


CWorkBookMediator::CWorkBookMediator(bool b2007)
{
	m_pWorkBook = new CBaseWorkBook(b2007);
}
CWorkBookMediator::CWorkBookMediator(bool b2007, CString sFileName)
{
	m_pWorkBook = new CBaseWorkBook(b2007, sFileName);
}


CWorkBookMediator::~CWorkBookMediator(void)
{
	if (m_pWorkBook)
		delete m_pWorkBook;
	ClearTempSheet();
	ClearTempCellType();
}

/** ����Sheetҳ */
CISheetMediator *	CWorkBookMediator::CreateSheet(CString sSheetName)
{
	CISheetMediator *pSheet = new CISheetMediator();
	pSheet->m_pSheet = m_pWorkBook->CreateSheet(sSheetName);
	m_vSheetList.push_back(pSheet);
	return pSheet;
}
/** ��ȡSheetҳ */
CISheetMediator *	CWorkBookMediator::GetSheet(int iIndex)
{
	CISheetMediator *pSheet = new CISheetMediator();
	pSheet->m_pSheet = m_pWorkBook->GetSheet(iIndex);
	m_vSheetList.push_back(pSheet);
	return pSheet;
}
/** ����Cell��� */
CICellStyleMediator * CWorkBookMediator::CreateICellStyle()
{
	CICellStyleMediator *pStyle = new CICellStyleMediator();
	pStyle->m_pCellStyle = m_pWorkBook->CreateICellStyle();
	m_vCellStyleList.push_back(pStyle);
	return pStyle;
}
/** ������Excel */
void	CWorkBookMediator::ExportToExcel(CString sFilePath, BOOL bOpenFile)
{
	m_pWorkBook->ExportToExcel(sFilePath, bOpenFile);
}

/** �����ʱSheetҳ */
void	CWorkBookMediator::ClearTempSheet()
{
	for (int i = 0; i < (int)m_vSheetList.size(); i++)
	{
		delete m_vSheetList[i];
	}
	m_vSheetList.clear();
}
/** �����ʱCell��� */
void	CWorkBookMediator::ClearTempCellType()
{
	for (int i = 0; i < (int)m_vCellStyleList.size(); i++)
	{
		delete m_vCellStyleList[i];
	}
	m_vCellStyleList.clear();
}