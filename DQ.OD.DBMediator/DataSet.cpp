#include "stdafx.h"
#include "DataSet.h"

// 
// CDataSet::CDataSet(CString sDataSetName)
// {
// 	m_strDataSetName = sDataSetName;
// 	m_DataSet = gcnew DataSet(gcnew System::String(sDataSetName));
// }
// 
// 
// CDataSet::~CDataSet(void)
// {
// 	delete m_DataSet;
// }
// 
// /** �������� */
// CString CDataSet::GetDataSetName()
// {
// 	return(m_strDataSetName);
// }
// /** ����������ȡ���� */
// CString CDataSet::GetTableName(int index)
// {
// 	if(index<m_TableArray.GetSize())
// 	{
// 		CDataTable* pDataTable=m_TableArray.GetAt(index);
// 		return(pDataTable->m_DataTable->TableName);
// 	}
// 	return(L"");
// }
// /** ��ȡ����� */
// int CDataSet::GetTableCount()
// {
// 	return (int)m_TableArray.GetSize();
// }
// /** ��ȡ������ */
// int CDataSet::GetTableRowCount(CString TableName)
// {
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return (pTable->GetCount());
// }
// /** �ر� */
// void CDataSet::Close()
// { 
// 	delete m_DataSet;
// }
// /** ��ӱ� */
// void CDataSet::AddDataTable(CDataTable* pDataTable)
// {
// 	m_TableArray.Add(pDataTable);
// }
// /** ���ݱ����Ƴ��� */
// void CDataSet::RemoveDataTable(CString TableName)
// {
// 	for(int i=0;i<m_TableArray.GetSize();i++)
// 	{
// 		CDataTable* pDataTable=m_TableArray.GetAt(i);
// 		if(pDataTable->m_DataTable->TableName==TableName)
// 		{
// 			m_TableArray.RemoveAt(i);
// 			m_TableArray.FreeExtra();
// 			break;
// 		}
// 	}
// }
// /** ����������ȡ���ݱ� */
// CDataTable* CDataSet::GetDataTable(int index)
// {
// 	if(index<m_TableArray.GetSize())
// 	{
// 		CDataTable* pDataTable=m_TableArray.GetAt(index);
// 		return(pDataTable);
// 	}
// 	return(NULL);
// }
// /** ���ݱ�����ȡ���ݱ� */
// CDataTable* CDataSet::GetDataTable(CString TableName)
// {
// 	for(int i=0;i<m_TableArray.GetSize();i++)
// 	{
// 		CDataTable* pDataTable=m_TableArray.GetAt(i);
// 		if(pDataTable->m_DataTable->TableName==TableName)
// 		{
// 			return(pDataTable);
// 		}
// 	}
// 	return(NULL);
// }
// /** ����������ȡ�ֶ�ֵ */
// CString CDataSet::GetStringField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetStringField(FieldName));
// }
// /** ����������ȡ�ֶ�ֵ */
// int CDataSet::GetIntField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetIntField(FieldName));
// }
// /** ����������ȡ�ֶ�ֵ */
// float CDataSet::GetFloatField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetFloatField(FieldName));
// }
// /** ����������ȡ�ֶ�ֵ */
// double CDataSet::GetDoubleField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetDoubleField(FieldName));
// }
// /** ����������ȡ�ֶ�ֵ */
// COleDateTime CDataSet::GetDateField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetDateField(FieldName));
// }
// /** ����������ȡ�ֶ�ֵ */
// byte* CDataSet::GetBlobField(CString TableFieldName,int &size)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetBlobField(FieldName,size));
// }
