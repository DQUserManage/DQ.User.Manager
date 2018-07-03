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
// /** 表集合名称 */
// CString CDataSet::GetDataSetName()
// {
// 	return(m_strDataSetName);
// }
// /** 根据索引获取表名 */
// CString CDataSet::GetTableName(int index)
// {
// 	if(index<m_TableArray.GetSize())
// 	{
// 		CDataTable* pDataTable=m_TableArray.GetAt(index);
// 		return(pDataTable->m_DataTable->TableName);
// 	}
// 	return(L"");
// }
// /** 获取表个数 */
// int CDataSet::GetTableCount()
// {
// 	return (int)m_TableArray.GetSize();
// }
// /** 获取表行数 */
// int CDataSet::GetTableRowCount(CString TableName)
// {
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return (pTable->GetCount());
// }
// /** 关闭 */
// void CDataSet::Close()
// { 
// 	delete m_DataSet;
// }
// /** 添加表 */
// void CDataSet::AddDataTable(CDataTable* pDataTable)
// {
// 	m_TableArray.Add(pDataTable);
// }
// /** 根据表名移除表 */
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
// /** 根据索引获取数据表 */
// CDataTable* CDataSet::GetDataTable(int index)
// {
// 	if(index<m_TableArray.GetSize())
// 	{
// 		CDataTable* pDataTable=m_TableArray.GetAt(index);
// 		return(pDataTable);
// 	}
// 	return(NULL);
// }
// /** 根据表名获取数据表 */
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
// /** 根据列名获取字段值 */
// CString CDataSet::GetStringField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetStringField(FieldName));
// }
// /** 根据列名获取字段值 */
// int CDataSet::GetIntField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetIntField(FieldName));
// }
// /** 根据列名获取字段值 */
// float CDataSet::GetFloatField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetFloatField(FieldName));
// }
// /** 根据列名获取字段值 */
// double CDataSet::GetDoubleField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetDoubleField(FieldName));
// }
// /** 根据列名获取字段值 */
// COleDateTime CDataSet::GetDateField(CString TableFieldName)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetDateField(FieldName));
// }
// /** 根据列名获取字段值 */
// byte* CDataSet::GetBlobField(CString TableFieldName,int &size)
// {
// 	CString TableName,FieldName;
// 	int length=TableFieldName.GetLength();
// 	int mid=TableFieldName.Find(L",");
// 	FieldName=TableFieldName.Right(length-mid+1);
// 	CDataTable* pTable=GetDataTable(TableName);
// 	return(pTable->GetBlobField(FieldName,size));
// }
