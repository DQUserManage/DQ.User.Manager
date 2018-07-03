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
	/** 关闭 */
	void		Close();
	/** 读取 */
	bool		Read();
	/** 获取string值 */
	CString		GetStringVal(int iIndex);
	CString		GetStringVal(CString sKey);
	/** 获取int值 */
	int			GetIntVal(int iIndex);
	int			GetIntVal(CString sKey);
	/** 获取float值 */
	float		GetFloatVal(int iIndex);
	float		GetFloatVal(CString sKey);
	/** 获取日期值 */
	COleDateTime	GetOleDateTimeVal(int iIndex);
	COleDateTime	GetOleDateTimeVal(CString sKey);
};

