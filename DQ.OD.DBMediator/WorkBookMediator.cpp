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

/** 创建Sheet页 */
CISheetMediator *	CWorkBookMediator::CreateSheet(CString sSheetName)
{
	CISheetMediator *pSheet = new CISheetMediator();
	pSheet->m_pSheet = m_pWorkBook->CreateSheet(sSheetName);
	m_vSheetList.push_back(pSheet);
	return pSheet;
}
/** 获取Sheet页 */
CISheetMediator *	CWorkBookMediator::GetSheet(int iIndex)
{
	CISheetMediator *pSheet = new CISheetMediator();
	pSheet->m_pSheet = m_pWorkBook->GetSheet(iIndex);
	m_vSheetList.push_back(pSheet);
	return pSheet;
}
/** 创建Cell风格 */
CICellStyleMediator * CWorkBookMediator::CreateICellStyle()
{
	CICellStyleMediator *pStyle = new CICellStyleMediator();
	pStyle->m_pCellStyle = m_pWorkBook->CreateICellStyle();
	m_vCellStyleList.push_back(pStyle);
	return pStyle;
}
/** 导出到Excel */
void	CWorkBookMediator::ExportToExcel(CString sFilePath, BOOL bOpenFile)
{
	m_pWorkBook->ExportToExcel(sFilePath, bOpenFile);
}

/** 清空临时Sheet页 */
void	CWorkBookMediator::ClearTempSheet()
{
	for (int i = 0; i < (int)m_vSheetList.size(); i++)
	{
		delete m_vSheetList[i];
	}
	m_vSheetList.clear();
}
/** 清空临时Cell风格 */
void	CWorkBookMediator::ClearTempCellType()
{
	for (int i = 0; i < (int)m_vCellStyleList.size(); i++)
	{
		delete m_vCellStyleList[i];
	}
	m_vCellStyleList.clear();
}