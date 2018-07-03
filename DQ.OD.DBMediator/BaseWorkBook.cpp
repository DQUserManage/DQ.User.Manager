#include "stdafx.h"
#include "BaseWorkBook.h"
#include "ISheet.h"
#include "ICellStyle.h"
#include "CSharpNameSpace.h"


CBaseWorkBook::CBaseWorkBook(bool b2007)
{
	if (b2007)
		m_workBook = gcnew XSSFWorkbook();
	else
		m_workBook = gcnew HSSFWorkbook();
	m_bReadFile = FALSE;
}
CBaseWorkBook::CBaseWorkBook(bool b2007, CString sFileName)
{
	if (b2007)
	{
		m_fsRead = File::OpenRead(gcnew System::String(sFileName));
		m_workBook = gcnew XSSFWorkbook(m_fsRead);
	} 
	else
	{
		m_fsRead = File::OpenRead(gcnew System::String(sFileName));
		m_workBook = gcnew HSSFWorkbook(m_fsRead);
	}
	m_bReadFile = TRUE;
}



CBaseWorkBook::~CBaseWorkBook(void)
{
	if (m_bReadFile)
		m_fsRead->Close();
}

/** ����Sheetҳ */
CISheet *	CBaseWorkBook::CreateSheet(CString sSheetName)
{
	CISheet *pISheet = new CISheet();
	pISheet->m_ISheet = m_workBook->CreateSheet(gcnew System::String(sSheetName));
	return pISheet;
}
/** ��ȡSheetҳ */
CISheet *	CBaseWorkBook::GetSheet(int iIndex)
{
	CISheet *pISheet = new CISheet();
	pISheet->m_ISheet = m_workBook->GetSheetAt(iIndex);
	return pISheet;
}
/** ����Cell��� */
CICellStyle * CBaseWorkBook::CreateICellStyle()
{
	CICellStyle *pStyle = new CICellStyle();
	pStyle->m_ICellStyle = m_workBook->CreateCellStyle();
	return pStyle;
}
/** ������Excel */
void	CBaseWorkBook::ExportToExcel(CString sFilePath, BOOL bOpenFile)
{
	Stream ^ stream;
	try
	{
		stream = File::OpenWrite(gcnew System::String(sFilePath));

		m_workBook->Write(stream);
		stream->Close();

		//Ĭ�ϴ��ļ�
		if (bOpenFile)
			System::Diagnostics::Process::Start(gcnew System::String(sFilePath));
	}
	catch(System::IO::IOException ^ err)
	{
		MessageBox(NULL,CString(err->Message),L"�����ļ�����",MB_ICONERROR);
	}
}