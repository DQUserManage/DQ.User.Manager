#include "stdafx.h"
#include "DataSetMediator.h"
#include "DataTableMediator.h"
#include "DataSet.h"

//
//CDataSetMediator::CDataSetMediator(CString sDataSetName)
//{
//	m_pDataSet = new CDataSet(sDataSetName);
//}
//
//
//CDataSetMediator::~CDataSetMediator(void)
//{
//	if (m_pDataSet)
//		delete m_pDataSet;
//}
//
///** 表集合名称 */
//CString CDataSetMediator::GetDataSetName()
//{
//	return m_pDataSet->GetDataSetName();
//}
///** 根据索引获取表名 */
//CString CDataSetMediator::GetTableName(int index)
//{
//	return m_pDataSet->GetTableName(index);
//}
///** 获取表个数 */
//int CDataSetMediator::GetTableCount()
//{
//	return m_pDataSet->GetTableCount();
//}
///** 获取表行数 */
//int CDataSetMediator::GetTableRowCount(CString TableName)
//{
//	return m_pDataSet->GetTableRowCount(TableName);
//}
///** 关闭 */
//void CDataSetMediator::Close()
//{ 
//	delete m_pDataSet;
//}
///** 添加表 */
//void CDataSetMediator::AddDataTable(CDataTableMediator* pDataTable)
//{
//	m_pDataSet->AddDataTable(pDataTable->GetDataTable());
//}
///** 根据表名移除表 */
//void CDataSetMediator::RemoveDataTable(CString TableName)
//{
//	m_pDataSet->RemoveDataTable(TableName);
//}
///** 根据索引获取数据表 */
//CDataTableMediator* CDataSetMediator::GetDataTable(int index)
//{
//	return new CDataTableMediator(m_pDataSet->GetDataTable(index));
//}
///** 根据表名获取数据表 */
//CDataTableMediator* CDataSetMediator::GetDataTable(CString TableName)
//{
//	return new CDataTableMediator(m_pDataSet->GetDataTable(TableName));
//}
///** 根据列名获取字段值 */
//CString CDataSetMediator::GetStringField(CString TableFieldName)
//{
//	return m_pDataSet->GetStringField(TableFieldName);
//}
///** 根据列名获取字段值 */
//int CDataSetMediator::GetIntField(CString TableFieldName)
//{
//	return m_pDataSet->GetIntField(TableFieldName);
//}
///** 根据列名获取字段值 */
//float CDataSetMediator::GetFloatField(CString TableFieldName)
//{
//	return m_pDataSet->GetFloatField(TableFieldName);
//}
///** 根据列名获取字段值 */
//double CDataSetMediator::GetDoubleField(CString TableFieldName)
//{
//	return m_pDataSet->GetDoubleField(TableFieldName);
//}
///** 根据列名获取字段值 */
//COleDateTime CDataSetMediator::GetDateField(CString TableFieldName)
//{
//	return m_pDataSet->GetDateField(TableFieldName);
//}
///** 根据列名获取字段值 */
//byte* CDataSetMediator::GetBlobField(CString TableFieldName,int &size)
//{
//	return m_pDataSet->GetBlobField(TableFieldName, size);
//}
