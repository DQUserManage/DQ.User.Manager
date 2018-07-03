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