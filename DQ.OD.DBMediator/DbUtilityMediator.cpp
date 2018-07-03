#include "stdafx.h"
#include "DbUtilityMediator.h"
#include "CSharpNameSpace.h"
#include "ParameterListMediator.h"
#include "DataTableMediator.h"
#include "ParameterList.h"
#include "DataReaderMediator.h"


CDbUtilityMediator::CDbUtilityMediator(CString sConnect, DBConnectType eType)
{
	m_pDbUtility = new SDbUtility(sConnect, eType);
}


CDbUtilityMediator::~CDbUtilityMediator(void)
{
	if (m_pDbUtility)
		delete m_pDbUtility;
	ClearParameterList();
}

/** 清空临时参数列表 */
void	CDbUtilityMediator::ClearParameterList()
{
	for (int i = 0; i < (int)m_vParameterList.size(); i++)
	{
		delete m_vParameterList[i];
	}
	m_vParameterList.clear();
}

/** 创建参数列表 */
CParameterListMediator * CDbUtilityMediator::CreateParameterList()
{
	CParameterList *pParameter = new CParameterList();
	pParameter->m_db = m_pDbUtility->s_DbUtility;
	CParameterListMediator *pList = new CParameterListMediator(pParameter);
	m_vParameterList.push_back(pList);
	return pList;
}
/** 打开数据表 */
CDataTableMediator*	CDbUtilityMediator::ExecuteTable(CString SQL)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return(NULL);
	}
	DataTable ^table = m_pDbUtility->s_DbUtility->ExecuteDataTable(gcnew System::String(SQL), nullptr);
	if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
	{
		MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return NULL;
	}
	CDataTableMediator *pDataTable=new CDataTableMediator();
	pDataTable->m_pDataTable->s_DataTable = table;
	return pDataTable;
}
/** 打开数据表 */
CDataTableMediator*	CDbUtilityMediator::ExecuteTable(CString SQL,CParameterListMediator* pList)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return(NULL);
	}
	DataTable ^table = m_pDbUtility->s_DbUtility->ExecuteDataTable(gcnew System::String(SQL), pList->GetParameterList()->GetList());
	if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
	{
		MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return NULL;
	}
	CDataTableMediator *pDataTable=new CDataTableMediator();
	pDataTable->m_pDataTable->s_DataTable = table;
	return pDataTable;
}
/** 打开数据表 */
CDataTableMediator*	CDbUtilityMediator::ExecuteOrclTable(CString SQL)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return(NULL);
	}
	DataTable ^table = m_pDbUtility->s_DbUtility->ExecuteOrclDataTable(gcnew System::String(SQL), nullptr);
	if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
	{
		MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return NULL;
	}
	CDataTableMediator *pDataTable=new CDataTableMediator();
	pDataTable->m_pDataTable->s_DataTable = table;
	return pDataTable;
}
/** 打开数据表 */
CDataTableMediator*	CDbUtilityMediator::ExecuteOrclTable(CString SQL,CParameterListMediator* pList)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return(NULL);
	}
	DataTable ^table = m_pDbUtility->s_DbUtility->ExecuteOrclDataTable(gcnew System::String(SQL), pList->GetParameterList()->GetList());
	if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
	{
		MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return NULL;
	}
	CDataTableMediator *pDataTable=new CDataTableMediator();
	pDataTable->m_pDataTable->s_DataTable = table;
	return pDataTable;
}
/** 执行SQL */
int 	CDbUtilityMediator::ExecuteQuery(CString SQL)
{
	int iCount = 0;
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return 0;
	}
	try
	{
		iCount = m_pDbUtility->s_DbUtility->ExecuteNonQuery(gcnew System::String(SQL), nullptr);
		if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
			MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
	}
	catch(CDBException *e)
	{
		MessageBox(NULL, e->m_strError, L"错误", MB_ICONERROR);
	}
	return iCount;
}
/** 执行SQL */
int 	CDbUtilityMediator::ExecuteQuery(CString SQL,CParameterListMediator* pList)
{
	int iCount = 0;
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return 0;
	}
	try
	{
		iCount = m_pDbUtility->s_DbUtility->ExecuteNonQuery(gcnew System::String(SQL),pList->GetParameterList()->GetList());
		if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
			MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
	}
	catch(CDBException *e)
	{
		MessageBox(NULL, e->m_strError, L"错误", MB_ICONERROR);
	}
	return iCount;
}
/** 执行SQL */
int 	CDbUtilityMediator::ExecuteQuery(CStringArray* SQLList)
{
	int iCount = 0;
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return 0;
	}
	try
	{
		List<String^> ^ list = gcnew List<String^>();
		for(int i=0;i<SQLList->GetSize();i++)
			list->Add(gcnew System::String(SQLList->GetAt(i)));
		iCount = m_pDbUtility->s_DbUtility->ExecuteNonQuery(list);
		if(m_pDbUtility->s_DbUtility->ErrorMessage != L"")
			MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
	}
	catch(CDBException *e)
	{
		MessageBox(NULL, e->m_strError, L"错误", MB_ICONERROR);
	}
	return iCount;
}
/** 执行SQL */
int		CDbUtilityMediator::ExecuteScalar(CString SQL)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return 0;
	}
	int result = 0;
	try
	{
		result = _ttoi(CString(m_pDbUtility->s_DbUtility->ExecuteScalar(gcnew System::String(SQL))->ToString()));
		if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
			MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
	}
	catch(CDBException *e)
	{
		MessageBox(NULL, e->m_strError, L"错误", MB_ICONERROR);
	}
	return result;
}
/** 执行存储过程 */
void	CDbUtilityMediator::ExecuteProcedure(CString sProcedureName, CParameterListMediator* pList)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return;
	}
	if (sProcedureName.IsEmpty())
	{
		MessageBox(NULL, L"存储过程名称不能为空！", L"错误", MB_ICONERROR);
		return;
	}
	try
	{
		m_pDbUtility->s_DbUtility->ExecuteProcedure(gcnew System::String(sProcedureName), pList->GetParameterList()->GetList());
		if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
			MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
	}
	catch (CDBException* e)
	{
		MessageBox(NULL, e->m_strError, L"错误", MB_ICONERROR);
	}
}

/** 执行Sql读取结果集 */
CDataReaderMediator* CDbUtilityMediator::ExecuteReader(CString SQL)
{
	if(!m_pDbUtility->s_DbUtility->CheckLink())
	{
		MessageBox(NULL, L"数据库链接配置错误:" + CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return(NULL);
	}
	DbDataReader ^table = m_pDbUtility->s_DbUtility->ExecuteReader(gcnew System::String(SQL), nullptr);
	if(m_pDbUtility->s_DbUtility->ErrorMessage != "")
	{
		MessageBox(NULL, CString(m_pDbUtility->s_DbUtility->ErrorMessage->ToString()), L"错误", MB_ICONERROR);
		return NULL;
	}
	CDataReaderMediator *pReader = new CDataReaderMediator();
	pReader->m_pReaderObj->s_DataReader = table;
	return pReader;
}