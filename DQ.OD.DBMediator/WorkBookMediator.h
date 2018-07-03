#pragma once

class CBaseWorkBook;
class CISheetMediator;
class CICellStyleMediator;

class AFX_EXT_CLASS CWorkBookMediator
{
public:
	CWorkBookMediator(bool b2007);
	CWorkBookMediator(bool b2007, CString sFileName);
	~CWorkBookMediator(void);

private:
	CBaseWorkBook *		m_pWorkBook;

	vector<CISheetMediator *>	m_vSheetList;
	vector<CICellStyleMediator *>	m_vCellStyleList;

private:
	/** �����ʱSheetҳ */
	void		ClearTempSheet();
	/** �����ʱCell��� */
	void		ClearTempCellType();

public:
	/** ����Sheetҳ */
	CISheetMediator *	CreateSheet(CString sSheetName);
	/** ��ȡSheetҳ */
	CISheetMediator *	GetSheet(int iIndex);
	/** ����Cell��� */
	CICellStyleMediator * CreateICellStyle();
	/** ������Excel */
	void		ExportToExcel(CString sFilePath, BOOL bOpenFile = TRUE);
};

