#pragma once

#include "DBStructPublic.h"
using namespace NPOI;
using namespace NPOI::SS::UserModel;

class CICellStyle;

class CIRow
{
public:
	CIRow();
	~CIRow(void);

public:
	gcroot<NPOI::SS::UserModel::IRow^>		m_IRow;

public:
	/** ����Cell */
	int			CreateCell(int iIndex, CellDataType eType);
	/** ����Cellֵ */
	void		SetCellStringVal(int iIndex, CString &sVal);
	/** ����Cellֵ */
	void		SetCellfloatVal(int iIndex, double &fVal);
	/** ����Cellֵ�������з�� */
	void		SetCellValByWrap(int iIndex, CString &sVal);
	/** ��ȡCellֵ */
	CString		GetCellVal(int iIndex);
	/** ����Cell��� */
	void		SetCellStyle(int iIndex, CICellStyle *pStyle);
	/** ��ȡ������ */
	int			GetColCount();
	/** ��ȡ��һ��Cell���� */
	int			GetFirstIndex();

};

