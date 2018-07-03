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
	/** 清空临时Sheet页 */
	void		ClearTempSheet();
	/** 清空临时Cell风格 */
	void		ClearTempCellType();

public:
	/** 创建Sheet页 */
	CISheetMediator *	CreateSheet(CString sSheetName);
	/** 获取Sheet页 */
	CISheetMediator *	GetSheet(int iIndex);
	/** 创建Cell风格 */
	CICellStyleMediator * CreateICellStyle();
	/** 导出到Excel */
	void		ExportToExcel(CString sFilePath, BOOL bOpenFile = TRUE);
};

