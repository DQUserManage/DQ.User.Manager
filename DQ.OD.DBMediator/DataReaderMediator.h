#pragma once

class SDataReader;


class AFX_EXT_CLASS CDataReaderMediator
{
public:
	CDataReaderMediator(void);
	~CDataReaderMediator(void);

public:
	SDataReader *			m_pReaderObj;

public:
	/** �ر� */
	void		Close();
	/** ��ȡ */
	bool		Read();
	/** ��ȡstringֵ */
	CString		GetStringVal(int iIndex);
	CString		GetStringVal(CString sKey);
	/** ��ȡintֵ */
	int			GetIntVal(int iIndex);
	int			GetIntVal(CString sKey);
	/** ��ȡfloatֵ */
	float		GetFloatVal(int iIndex);
	float		GetFloatVal(CString sKey);
	/** ��ȡ����ֵ */
	COleDateTime	GetOleDateTimeVal(int iIndex);
	COleDateTime	GetOleDateTimeVal(CString sKey);
};

