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
///** �������� */
//CString CDataSetMediator::GetDataSetName()
//{
//	return m_pDataSet->GetDataSetName();
//}
///** ����������ȡ���� */
//CString CDataSetMediator::GetTableName(int index)
//{
//	return m_pDataSet->GetTableName(index);
//}
///** ��ȡ����� */
//int CDataSetMediator::GetTableCount()
//{
//	return m_pDataSet->GetTableCount();
//}
///** ��ȡ������ */
//int CDataSetMediator::GetTableRowCount(CString TableName)
//{
//	return m_pDataSet->GetTableRowCount(TableName);
//}
///** �ر� */
//void CDataSetMediator::Close()
//{ 
//	delete m_pDataSet;
//}
///** ��ӱ� */
//void CDataSetMediator::AddDataTable(CDataTableMediator* pDataTable)
//{
//	m_pDataSet->AddDataTable(pDataTable->GetDataTable());
//}
///** ���ݱ����Ƴ��� */
//void CDataSetMediator::RemoveDataTable(CString TableName)
//{
//	m_pDataSet->RemoveDataTable(TableName);
//}
///** ����������ȡ���ݱ� */
//CDataTableMediator* CDataSetMediator::GetDataTable(int index)
//{
//	return new CDataTableMediator(m_pDataSet->GetDataTable(index));
//}
///** ���ݱ�����ȡ���ݱ� */
//CDataTableMediator* CDataSetMediator::GetDataTable(CString TableName)
//{
//	return new CDataTableMediator(m_pDataSet->GetDataTable(TableName));
//}
///** ����������ȡ�ֶ�ֵ */
//CString CDataSetMediator::GetStringField(CString TableFieldName)
//{
//	return m_pDataSet->GetStringField(TableFieldName);
//}
///** ����������ȡ�ֶ�ֵ */
//int CDataSetMediator::GetIntField(CString TableFieldName)
//{
//	return m_pDataSet->GetIntField(TableFieldName);
//}
///** ����������ȡ�ֶ�ֵ */
//float CDataSetMediator::GetFloatField(CString TableFieldName)
//{
//	return m_pDataSet->GetFloatField(TableFieldName);
//}
///** ����������ȡ�ֶ�ֵ */
//double CDataSetMediator::GetDoubleField(CString TableFieldName)
//{
//	return m_pDataSet->GetDoubleField(TableFieldName);
//}
///** ����������ȡ�ֶ�ֵ */
//COleDateTime CDataSetMediator::GetDateField(CString TableFieldName)
//{
//	return m_pDataSet->GetDateField(TableFieldName);
//}
///** ����������ȡ�ֶ�ֵ */
//byte* CDataSetMediator::GetBlobField(CString TableFieldName,int &size)
//{
//	return m_pDataSet->GetBlobField(TableFieldName, size);
//}
