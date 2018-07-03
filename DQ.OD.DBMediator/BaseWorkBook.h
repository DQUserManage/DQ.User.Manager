#pragma once

using namespace NPOI;
using namespace NPOI::HSSF;
using namespace NPOI::HSSF::UserModel;
using namespace NPOI::XSSF;
using namespace NPOI::XSSF::UserModel;
using namespace NPOI::SS::UserModel;
using namespace NPOI::SS::Util;
using namespace System::IO;

class CISheet;
class CICellStyle;

class CBaseWorkBook
{
public:
	CBaseWorkBook(bool b2007);
	CBaseWorkBook(bool b2007, CString sFileName);
	virtual ~CBaseWorkBook(void);

protected:
	gcroot<IWorkbook^>		m_workBook;
	gcroot<FileStream^>		m_fsRead;

	BOOL					m_bReadFile;

public:
	/** ����Sheetҳ */
	CISheet *	CreateSheet(CString sSheetName);
	/** ��ȡSheetҳ */
	CISheet *	GetSheet(int iIndex);
	/** ����Cell��� */
	CICellStyle * CreateICellStyle();
	/** ������Excel */
	void		ExportToExcel(CString sFilePath, BOOL bOpenFile);
	/**  */
	/**  */

};

