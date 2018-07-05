#include "stdafx.h"
#include "UserManagerDataAccess.h"

#include <memory>


CUserManagerDataService* CUserManagerDataService::m_pSingleton = nullptr;

CUserManagerDataService* CUserManagerDataService::GetInstance()
{
	if (m_pSingleton == nullptr)
		m_pSingleton = new CUserManagerDataService;

	return m_pSingleton;
}

void CUserManagerDataService::DestoryInstance()
{
	if (m_pSingleton)
	{
		delete m_pSingleton;
		m_pSingleton = nullptr;
	}
}


CUserManagerDataService::CUserManagerDataService()
{
	m_pDB = nullptr;
}

CUserManagerDataService::~CUserManagerDataService()
{
	FreeDB();
}

//----------------------------------------
void CUserManagerDataService::FreeDB()
{
	if (m_pDB)
	{
		delete m_pDB;
		m_pDB = nullptr;
	}
}

bool CUserManagerDataService::DBInit(const CString& csConn, int nType)
{
	FreeDB();
	//
	m_pDB = new CDbUtilityMediator(csConn, DBConnectType(nType));
	
	return true;
}

//--------------------------------------
bool CUserManagerDataService::DoTest()
{
	ASSERT(m_pDB!=NULL);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(_T("SELECT * FROM PC_BASIC_WELL_INFO")));
	if (!pTab)
		return false;

	int nRows = pTab->GetRowCount();
	int nCols = pTab->GetColCount();

	for (int i = 0;i < nRows;i++)
	{
		for (int j = 0;j < nCols;j++)
		{
			CString csVal  = pTab->GetStringField(i, pTab->GetsFieldName(j));

			int temp = 0;
		}
	}
	return true;
}

//---------------------------------------------
bool CUserManagerDataService::GetSysRes(std::vector<CSysRes>& vRes)
{
	vRes.clear();
	//
	CString csSQL;
	csSQL.Format(_T("SELECT res_id,res_name,res_class,content_type,filename,author,version from SYS_RESOURCE"));

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	int iCount = pTab->GetRowCount();
	for (int i = 0;i < iCount;i++)
	{
		CSysRes res;
		res.m_csResID = pTab->GetStringField(i, _T("res_id"));
		res.m_csName = pTab->GetStringField(i, _T("res_name"));
		res.m_csResClass = pTab->GetStringField(i, _T("res_class"));
		res.m_csContentType = pTab->GetStringField(i, _T("content_type"));
		res.m_csFileName = pTab->GetStringField(i, _T("filename"));
		res.m_csAuthor = pTab->GetStringField(i, _T("author"));
		res.m_csVersion = pTab->GetStringField(i, _T("version"));

		vRes.push_back(res);
	}
	return true;
}

bool CUserManagerDataService::DeleteAllSysRes()
{
	CString csSQL;
	csSQL.Format(_T("Truncate Table SYS_RESOURCE"));

	return m_pDB->ExecuteQuery(csSQL) > 0;
}

bool CUserManagerDataService::DelSysRes(const CString& csResID)
{
	if (csResID.IsEmpty())
		return false;

	CString csSQL;
	csSQL.Format(_T("Delete From SYS_RESOURCE where res_id = '%s'"),csResID);

	return m_pDB->ExecuteQuery(csSQL) > 0;

}

bool CUserManagerDataService::AddSysRes(const CSysRes& res)
{
	CString csSQL;
	csSQL.Format(_T("INSERT INTO SYS_RESOURCE (res_id,res_name,res_class,content_type,filename,DEVELOP_DATE,org_id,author,version) \
          VALUES('%s', '%s', '%s', '%s', '%s', to_date('%s','yyyy-mm-dd'), '%s', '%s', '%s')") \
		, res.m_csResID, 
		res.m_csName,
		res.m_csResClass, 
		res.m_csContentType, 
		res.m_csFileName,
		res.m_dtDevelop.Format(_T("%Y-%m-%d")),
		res.m_csOrgID,
		res.m_csAuthor,
		res.m_csVersion);

	return m_pDB->ExecuteQuery(csSQL) > 0;
}

bool CUserManagerDataService::EditSysRes(const CSysRes& res)
{
	CString csSQL;
	csSQL.Format(_T("UPDATE SYS_RESOURCE Set \
			  res_name='%s',\
			  res_class='%s',\
			 content_type='%s',\
			filename='%s',\
			DEVELOP_DATE=to_date('%s','yyyy-mm-dd'),\
			org_id='%s',\
			author='%s',\
			version='%s' WHERE res_id = '%s'"), \
		res.m_csName,
		res.m_csResClass,
		res.m_csContentType,
		res.m_csFileName,
		res.m_dtDevelop.Format(_T("%Y-%m-%d")),
		res.m_csOrgID,
		res.m_csAuthor,
		res.m_csVersion,
		res.m_csResID);

	return m_pDB->ExecuteQuery(csSQL) > 0;
}

bool CUserManagerDataService::UploadSysRes(const CSysRes& res, const CString& csFileName)
{
	if (res.m_csResID.IsEmpty())
		return false;

	CString csSQL;
	csSQL.Format(_T("SELECT content from SYS_RESOURCE where res_id = '%s'"),res.m_csResID);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	COleVariant out;
	if (!CUserUtility::PutFileIntoVariant(&out, csFileName))
		return false;

	pTab->SetFieldValue(0, 0, out);

	return true;
}

bool CUserManagerDataService::GetSysResBasic(CSysRes& res)
{
	CString csSQL;
	csSQL.Format(_T("SELECT res_id,res_name,res_class,content_type,filename,author,version,develop_date from SYS_RESOURCE where res_id = '%s'"),res.m_csResID);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	int iCount = pTab->GetRowCount();
	if (iCount == 1)
	{
		const int i = 0;
		res.m_csResID = pTab->GetStringField(i, _T("res_id"));
		res.m_csName = pTab->GetStringField(i, _T("res_name"));
		res.m_csResClass = pTab->GetStringField(i, _T("res_class"));
		res.m_csContentType = pTab->GetStringField(i, _T("content_type"));
		res.m_csFileName = pTab->GetStringField(i, _T("filename"));
		res.m_csAuthor = pTab->GetStringField(i, _T("author"));
		res.m_csVersion = pTab->GetStringField(i, _T("version"));
		res.m_dtDevelop = pTab->GetDateField(i, _T("develop_date"));
		return true;
	}

	return false;
}