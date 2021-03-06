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


std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetOrgInfoUseOrgID(CString OrgID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("SELECT * FROM SYS_ORGNIZATION where ORG_ID = '%s'"), OrgID);
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


CDataTableMediator* CUserManagerDataService::GetBranchUser()
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select * from SYS_USER t "));
	CDataTableMediator* pTab = m_pDB->ExecuteTable(sSql);
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


CDataTableMediator* CUserManagerDataService::GetUserInfoUserUserID(CString UserID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("SELECT * FROM SYS_USER where USER_ID = '%s'"), UserID);
	CDataTableMediator* pTab = m_pDB->ExecuteOrclTable(sSql);
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

BOOL CUserManagerDataService::GetDeptNode(const CString& csParent, vector<COrgInfo>& vDept)
{
	vDept.clear();
	//
	CString csSQL;

	if (csParent.IsEmpty())
		csSQL.Format(_T("SELECT * from SYS_ORGNIZATION where nvl(PARENT_ID,' ')=' ' order by org_name"));
	else
		csSQL.Format(_T("SELECT * from SYS_ORGNIZATION where trim(PARENT_ID)='%s' order by org_name"),csParent);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	int iCount = pTab->GetRowCount();
	for (int i = 0;i < iCount;i++)
	{
		COrgInfo OrgInfo;
		OrgInfo.SetDescription(pTab->GetStringField(i, L"DESCRIPTION"));
		OrgInfo.SetLeader(pTab->GetStringField(i, L"LEADER"));
		OrgInfo.SetLevel(pTab->GetStringField(i, L"ORG_LEVEL"));
		OrgInfo.SetOrgID(pTab->GetStringField(i, L"ORG_ID"));
		OrgInfo.SetOrgName(pTab->GetStringField(i, L"ORG_NAME"));
		OrgInfo.SetParentID(pTab->GetStringField(i, L"PARENT_ID"));
		OrgInfo.SetShortName(pTab->GetStringField(i, L"SHORT_NAME"));

		vDept.push_back(OrgInfo);
	}
	return true;
}

//----------------------------------------------

std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetRoleInfo()
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select t.*, t.rowid from SYS_ROLE t "));
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	if (!pTab)
		return NULL;

	return pTab;
}

std::shared_ptr<CDataTableMediator> CUserManagerDataService::GetRoleInfoUseID(CString RoleID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select t.*, t.rowid from SYS_ROLE t where ROLE_ID='%s'"), RoleID);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	if (!pTab)
		return NULL;

	return pTab;
}

BOOL CUserManagerDataService::UpdateRoleInfo(CRoleInfo RoleInfo)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	//更新角色信息
	sSql.Format(_T("update SYS_ROLE set ROLE_ID='%s', ROLE_NAME='%s', DESCRIPTION='%s' where ROLE_ID='%s'"),
		RoleInfo.GetRoleID(), RoleInfo.GetRoleName(), RoleInfo.GetRemark(), RoleInfo.GetRoleID());
	m_pDB->ExecuteQuery(sSql);

	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}

BOOL CUserManagerDataService::DelUserRoleInfo(CString UserID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("delete from SYS_USER_ROLE where USER_ID='%s'"), UserID);

	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}

CDataTableMediator* CUserManagerDataService::GetUserRoleInfo(CString UserID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select t.*, t.rowid from SYS_USER_ROLE t where USER_ID='%s'"), UserID);
	CDataTableMediator* pTab = m_pDB->ExecuteTable(sSql);
	if (!pTab)
		return NULL;

	return pTab;
}

BOOL CUserManagerDataService::InsertUserRoleInfo(CString UserID,CString UserRole)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("insert into SYS_USER_ROLE(USER_ID,ROLE_ID) values('%s','%s')"),UserID, UserRole);

	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}

BOOL CUserManagerDataService::InsertRoleInfo(CRoleInfo RoleInfo)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("insert into SYS_ROLE(ROLE_ID,ROLE_NAME,DESCRIPTION) values('%s','%s','%s')"), RoleInfo.GetRoleID(), RoleInfo.GetRoleName(), RoleInfo.GetRemark());

	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}

BOOL CUserManagerDataService::DelPowerRoleInfo(CRoleInfo RoleInfo)
{
	CString sSql = L"";
	// 删除角色所有与权限的对应
	sSql.Format(L"delete from SYS_ROLE_PERMISSION where ROLE_ID='%s'", RoleInfo.GetRoleID());
	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}

BOOL CUserManagerDataService::InsertPowerRoleInfo(CRoleInfo RoleInfo, CString RolePower)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("insert into SYS_ROLE_PERMISSION(ROLE_ID,NODE_ID) values('%s','%s')"), RoleInfo.GetRoleID(), RolePower);

	int count = m_pDB->ExecuteQuery(sSql);
	if (count == -1)
		return FALSE;

	return TRUE;
}

BOOL CUserManagerDataService::DeleteRoleInfo(CString RoleID)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	int count;
	//查看是否有其他表用到了用户ID
	//1.用户角色对应表
	sSql.Format(_T("select * from SYS_USER_ROLE where ROLE_ID = '%s'"), RoleID);
	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteTable(sSql));
	if (!pTab)
	{
		//Do Nothing
	}
	else
	{
		//存在数据 删除用户角色表中对应的用户ID数据
		sSql.Format(_T("delete from SYS_USER_ROLE where ROLE_ID = '%s'"), RoleID);
		m_pDB->ExecuteQuery(sSql);
	}

	//2.角色权限对应表
	sSql.Format(_T("select * from SYS_ROLE_PERMISSION where ROLE_ID = '%s'"), RoleID);
	std::shared_ptr<CDataTableMediator> pTable (m_pDB->ExecuteTable(sSql));
	if (!pTable)
	{
		//Do Nothing
	}
	else
	{
		//存在数据 删除用户角色表中对应的用户ID数据
		sSql.Format(_T("delete from SYS_ROLE_PERMISSION where ROLE_ID = '%s'"), RoleID);
		m_pDB->ExecuteQuery(sSql);
	}

	sSql.Format(_T("delete from SYS_ROLE where ROLE_ID = '%s'"), RoleID);
	count = m_pDB->ExecuteQuery(sSql);
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

bool CUserManagerDataService::DelSysRes(CStringArray& vSQL)
{
	return m_pDB->ExecuteQuery(&vSQL) > 0;
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

	COleVariant out;
	if (!CUserUtility::PutFileIntoVariant(&out, csFileName))
		return false;

	CString csSQL;
	csSQL.Format(_T("Update SYS_RESOURCE set content = :blob_content where res_id = '%s'"), res.m_csResID);

	CParameterListMediator*  pList = m_pDB->CreateParameterList();
	pList->AddParameter(_T("blob_content"), out);

	return m_pDB->ExecuteQuery(csSQL, pList) > 0;

}

bool CUserManagerDataService::GetUploadSysRes(const CString& csResID, BYTE*& pBuf, int& nSize)
{
	CString csSQL;
	csSQL.Format(_T("SELECT content from SYS_RESOURCE where res_id = '%s'"), csResID);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	int iCount = pTab->GetRowCount();
	if (iCount != 1)
		return false;

	pBuf = pTab->GetBlobField(0, 0, nSize);

	return pBuf != nullptr;
}

bool CUserManagerDataService::GetSysResBasic(CSysRes& res)
{
	CString csSQL;
	csSQL.Format(_T("SELECT res_id,res_name,res_class,content_type,filename,author,version,develop_date,\
		(select org_name from SYS_ORGNIZATION where org_id = a.org_id) org_name ,a.org_id from SYS_RESOURCE a where res_id = '%s'"), res.m_csResID);

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
		res.m_csOrgName = pTab->GetStringField(i, _T("org_name"));
		res.m_csOrgID = pTab->GetStringField(i, _T("org_id"));
		return true;
	}

	return false;
}

//---------------------------------------------------------------
bool CUserManagerDataService::GetSysModeNode(const CString& csParentID, vector<CSysMod>& vMode)
{
	vMode.clear();
	//
	CString csSQL;

	if (csParentID.IsEmpty())
		csSQL.Format(_T("SELECT * from SYS_MODULE where nvl(PARENT_ID,' ')=' ' order by RES_ORDER"));
	else
		csSQL.Format(_T("SELECT * from SYS_MODULE where trim(PARENT_ID)='%s' order by RES_ORDER"), csParentID);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	int iCount = pTab->GetRowCount();
	for (int i = 0;i < iCount;i++)
	{
		CSysMod info;
		info.m_csModID = pTab->GetStringField(i, _T("NODE_ID"));
		info.m_csName = pTab->GetStringField(i, _T("RES_NAME"));
		info.m_csModType = pTab->GetStringField(i, _T("RES_TYPE"));
		info.m_csResID = pTab->GetStringField(i, _T("RES_ID"));

		vMode.push_back(info);
	}
	return true;
}

bool CUserManagerDataService::SaveSysModeInfo(CStringArray& vSQL)
{
	return m_pDB->ExecuteQuery(&vSQL) > 0;
}

bool CUserManagerDataService::GetSysModeBasic(CSysMod& mod)
{
	CString csSQL;
	csSQL.Format(_T("SELECT node_id,a.res_name,a.res_type,a.res_id\
(select res_name from SYS_RESOURCE where res_id = a.res_id) org_name from SYS_MODULE a where node_id = '%s'"), mod.m_csModID);

	std::shared_ptr<CDataTableMediator> pTab(m_pDB->ExecuteOrclTable(csSQL));
	if (!pTab)
		return false;

	int iCount = pTab->GetRowCount();
	if (iCount == 1)
	{
		const int i = 0;
		mod.m_csName = pTab->GetStringField(i, _T("res_name"));
		mod.m_csModType = pTab->GetStringField(i, _T("res_type"));
		mod.m_csResID = pTab->GetStringField(i, _T("res_id"));
		mod.m_csResName = pTab->GetStringField(i, _T("org_name"));
		return true;
	}

	return false;
}

CDataTableMediator* CUserManagerDataService::GetSysModeInfoUseRoleId(CString RolD)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select DISTINCT NODE_ID, RES_NAME, PARENT_ID, RES_TYPE from SYS_MODULE start with  NODE_ID in (SELECT NODE_ID FROM SYS_ROLE_PERMISSION where ROLE_ID='%s') connect by NODE_ID = prior PARENT_ID order by PARENT_ID"), RolD);
	CDataTableMediator* pTab = m_pDB->ExecuteTable(sSql);
	if (!pTab)
		return NULL;

	return pTab;
}

CDataTableMediator* CUserManagerDataService::GetSysModeInfo(CString ModlD)
{
	ASSERT(m_pDB != NULL);

	CString sSql = L"";
	sSql.Format(_T("select t.*, t.rowid from SYS_MODULE t where NODE_ID='%s'"), ModlD);
	CDataTableMediator* pTab = m_pDB->ExecuteTable(sSql);
	if (!pTab)
		return NULL;

	return pTab;
}
