#include "stdafx.h"
#include "UserManagerDataAccess.h"




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


std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetOrgInfo()
{
	ASSERT(m_pDB != NULL);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(_T("SELECT * FROM SYS_ORGNIZATION")));
	if (!pTab)
		return NULL;

	return pTab;
}


std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetOrgInfoUseOrgName(CString OrgName)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("SELECT * FROM SYS_ORGNIZATION where ORG_NAME = '%s'"), OrgName);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(sSql));
	if (!pTab)
		return NULL;

	return pTab;
}


BOOL CUserManagerDataService::InsertOrgInfo(COrgInfo OrgInfo)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";

	sSql.Format(_T("insert into SYS_ORGNIZATION(ORG_ID,PARENT_ID,ORG_NAME,SHORT_NAME,ORG_LEVEL,LEADER,DESCRIPTION) values('%s','%s','%s','%s','%s','%s','%s')"),
		OrgInfo.GetOrgID(), OrgInfo.GetParentID(), OrgInfo.GetOrgName(), OrgInfo.GetShortName(), OrgInfo.GetLevel(), OrgInfo.GetLeader(), OrgInfo.GetDescription());
	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}


BOOL CUserManagerDataService::DeleteOrgInfo(CString OrgID)
{
	ASSERT(m_pDB != NULL);

	int count;
	CString sSql = L"";
	//判断部门下是否有员工 若有则删除员工
	sSql.Format(_T("select * from SYS_USER where ORG_ID = '%s'"), OrgID);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	if (!pTab)
	{
		//Do Nothing
	}
	else
	{
		//存在数据 删除用户角色表中对应的用户ID数据
		DeleteUserInfo(OrgID);
	}
	
	sSql.Format(_T("delete from SYS_ORGNIZATION where ORG_ID = '%s'"), OrgID);
	count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}


void CUserManagerDataService::DeleteChildOrgInfo(CString ParentID)
{
	CString sSql = L"";
	sSql.Format(_T("select t.*, t.rowid from SYS_ORGNIZATION t where PARENT_ID = '%s'"), ParentID);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	
	for (int i = 0; i < pTab->GetRowCount();i++)
	{
		CString OrgId = pTab->GetStringField(i, L"ORG_ID");
		DeleteOrgInfo(OrgId);
		DeleteChildOrgInfo(OrgId);
	}
}


BOOL CUserManagerDataService::UpdateOrgInfo(COrgInfo OrgInfo)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("update SYS_ORGNIZATION set ORG_NAME='%s', SHORT_NAME='%s', ORG_LEVEL='%s', LEADER='%s', DESCRIPTION='%s' where ORG_ID='%s'"),
		OrgInfo.GetOrgName(), OrgInfo.GetShortName(), OrgInfo.GetLevel(), OrgInfo.GetLeader(), OrgInfo.GetDescription(),OrgInfo.GetOrgID());
	
	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}


std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetBranchUser(CString ItemTxt)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select * from SYS_USER t where ORG_ID = (select ORG_ID from SYS_ORGNIZATION where ORG_NAME = '%s')"), ItemTxt);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	if (!pTab)
		return NULL;

	return pTab;
}


BOOL CUserManagerDataService::InsertUserInfo(CUserInfo UserInfo)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("insert into SYS_USER(USER_ID,ORG_ID,USER_NAME,USER_SEX,USER_PASSWORD,USER_EMAIL,USER_TELEPHONE,USER_FAX,USER_MOBILE,USER_QQ,USER_MSN,DESCRIPTION) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
		UserInfo.GetUserID(), UserInfo.GetOrgID(), UserInfo.GetUserNames(), UserInfo.GetUserSex(), UserInfo.GetUserPw(), UserInfo.GetUserEmail(), 
		UserInfo.GetUserTelephone(), UserInfo.GetUserFax(), UserInfo.GetUserMobile(), UserInfo.GetUserQQ(), UserInfo.GetUserMSN(), UserInfo.GetDescription());
	
	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}


BOOL CUserManagerDataService::DeleteUserInfo(CString UserID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	int count;
	//查看是否有其他表用到了用户ID
	//1.用户角色对应表
	sSql.Format(_T("select * from SYS_USER_ROLE where USER_ID = '%s'"), UserID);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	if (!pTab)
	{
		//Do Nothing
	}
	else
	{
		//存在数据 删除用户角色表中对应的用户ID数据
		sSql.Format(_T("delete from SYS_USER_ROLE where USER_ID = '%s'"), UserID);
		m_pDB->ExecuteQuery(sSql);
	}

	sSql.Format(_T("delete from SYS_USER where USER_ID = '%s'"), UserID);
	count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}


std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetUserInfoUserUserID(CString UserID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("SELECT * FROM SYS_USER where USER_ID = '%s'"), UserID);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(sSql));
	if (!pTab)
		return NULL;

	return pTab;
}


BOOL CUserManagerDataService::UpdateUserInfo(CUserInfo UserInfo)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("update SYS_USER set USER_ID='%s', ORG_ID='%s', USER_NAME='%s', USER_SEX='%s', USER_PASSWORD='%s', USER_EMAIL='%s', USER_TELEPHONE='%s', USER_FAX='%s', USER_MOBILE='%s', USER_QQ='%s', USER_MSN='%s', DESCRIPTION='%s' where USER_ID='%s'"),
		UserInfo.GetUserID(), UserInfo.GetOrgID(), UserInfo.GetUserNames(), UserInfo.GetUserSex(), UserInfo.GetUserPw(), UserInfo.GetUserEmail(),
		UserInfo.GetUserTelephone(), UserInfo.GetUserFax(), UserInfo.GetUserMobile(), UserInfo.GetUserQQ(), UserInfo.GetUserMSN(), UserInfo.GetDescription(), UserInfo.GetUserID());
	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
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
	csSQL.Format(_T("Delete From SYS_RESOURCE where res_id = '%s'"), csResID);

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
	csSQL.Format(_T("SELECT content from SYS_RESOURCE where res_id = '%s'"), res.m_csResID);

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
	csSQL.Format(_T("SELECT res_id,res_name,res_class,content_type,filename,author,version,develop_date from SYS_RESOURCE where res_id = '%s'"), res.m_csResID);

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
