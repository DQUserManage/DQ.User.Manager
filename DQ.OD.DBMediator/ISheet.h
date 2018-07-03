#pragma once

using namespace NPOI;
using namespace NPOI::SS::UserModel;

class CIRow;

class CISheet
{
public:
	CISheet(void);
	~CISheet(void);

public:
	gcroot<ISheet ^>	m_ISheet;

public:
	/** ��ȡ���� */
	int			GetRowCount();
	/** ��ȡ���� */
	int			GetColCount();
	/** ��ȡ�� */
	CIRow *		GetRow(int iIndex);
	/** ������ */
	CIRow *		CreateRow(int iIndex);
	/** ��Ӻϲ� */
	void		AddMergedRegion(int firstRow, int lastRow, int firstCol, int lastCol);
	/** �����п�� */
	void		SetColumnWidth(int iIndex, int iWidth);

};

