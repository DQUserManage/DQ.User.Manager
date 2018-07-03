#pragma once

class CIRowMediator;
class CISheet;

class AFX_EXT_CLASS CISheetMediator
{
public:
	CISheetMediator(void);
	~CISheetMediator(void);

public:
	CISheet *	m_pSheet;

private:
	vector<CIRowMediator *>		m_vRowList;

private:
	/** �����ʱ�� */
	void		ClearTempRow();

public:
	/** ��ȡ���� */
	int			GetRowCount();
	/** ��ȡ���� */
	int			GetColCount();
	/** ��ȡ�� */
	CIRowMediator *		GetRow(int iIndex);
	/** ������ */
	CIRowMediator *		CreateRow(int iIndex);
	/** ��Ӻϲ� */
	void		AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol);
	/** �����п�� */
	void		SetColumnWidth(int iIndex, int iWidth);
	/**  */

};