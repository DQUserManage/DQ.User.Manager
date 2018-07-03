#include "stdafx.h"
#include "DataReaderMediator.h"
#include "CSharpNameSpace.h"


CDataReaderMediator::CDataReaderMediator(void)
{
	m_pReaderObj = new SDataReader();
}


CDataReaderMediator::~CDataReaderMediator(void)
{
	if (m_pReaderObj)
	{
		m_pReaderObj->s_DataReader->Close();
		delete m_pReaderObj;
		m_pReaderObj = NULL;
	}
}

/** �ر� */
void		CDataReaderMediator::Close()
{
	m_pReaderObj->s_DataReader->Close();
}
/** ��ȡ */
bool		CDataReaderMediator::Read()
{
	return m_pReaderObj->s_DataReader->Read();
}
/** ��ȡstringֵ */
CString		CDataReaderMediator::GetStringVal(int iIndex)
{
	return m_pReaderObj->s_DataReader->GetString(iIndex);
}
CString		CDataReaderMediator::GetStringVal(CString sKey)
{
	DbDataReader^ dbReader = m_pReaderObj->s_DataReader;
	return dbReader[gcnew System::String(sKey)]->ToString();
}
/** ��ȡintֵ */
int			CDataReaderMediator::GetIntVal(int iIndex)
{
	return m_pReaderObj->s_DataReader->GetInt32(iIndex);
}
int			CDataReaderMediator::GetIntVal(CString sKey)
{
	DbDataReader^ dbReader = m_pReaderObj->s_DataReader;
	return _ttoi(CString(dbReader[gcnew System::String(sKey)]->ToString()));
}
/** ��ȡfloatֵ */
float		CDataReaderMediator::GetFloatVal(int iIndex)
{
	return m_pReaderObj->s_DataReader->GetFloat(iIndex);
}
float		CDataReaderMediator::GetFloatVal(CString sKey)
{
	DbDataReader^ dbReader = m_pReaderObj->s_DataReader;
	return (float)_ttof(CString(dbReader[gcnew System::String(sKey)]->ToString()));
}
/** ��ȡ����ֵ */
COleDateTime	CDataReaderMediator::GetOleDateTimeVal(int iIndex)
{
	COleDateTime datevalue;
	datevalue.SetDate(0,0,0);
	DbDataReader^ dbReader = m_pReaderObj->s_DataReader;
	CString value(dbReader[iIndex]->ToString());
	if(value == L"")
		return datevalue;

	datevalue.ParseDateTime(value);
	return datevalue;
}
COleDateTime	CDataReaderMediator::GetOleDateTimeVal(CString sKey)
{
	COleDateTime datevalue;
	datevalue.SetDate(0,0,0);
	DbDataReader^ dbReader = m_pReaderObj->s_DataReader;
	CString value(dbReader[gcnew System::String(sKey)]->ToString());
	if(value == L"")
		return datevalue;

	datevalue.ParseDateTime(value);
	return datevalue;
}