#pragma once

#include "DBStructPublic.h"

class CIRow;
class CICellStyleMediator;


class AFX_EXT_CLASS CIRowMediator
{
public:
	CIRowMediator(void);
	~CIRowMediator(void);

public:
	CIRow *		m_pRow;

public:
	/** ����Cell */
	int			CreateCell(int iIndex, CellDataType eType);
	/** ����Cellֵ */
	void		SetCellStringVal(int iIndex, CString &sVal);
	/** ����Cellֵ */
	void		SetCellfloatVal(int iIndex, double fVal);
	/** ����Cellֵ�������з�� */
	void		SetCellValByWrap(int iIndex, CString &sVal);
	/** ��ȡCellֵ */
	CString		GetCellVal(int iIndex);
	/** ����Cell��� */
	void		SetCellStyle(int iIndex, CICellStyleMediator *pStyle);
	/** ��ȡ������ */
	int			GetColCount();
	/** ��ȡ��һ��Cell���� */
	int			GetFirstIndex();
};

