#include "stdafx.h"
#include "SysRes.h"

CSysRes::CSysRes()
{
	m_csResID.Empty();
	m_csName.Empty();
	m_csResClass.Empty();
	m_csContentType.Empty();
	m_csFileName.Empty();
	m_csAuthor.Empty();
	m_csVersion.Empty();
	m_csOrgID.Empty();
}

CSysRes::~CSysRes()
{

}

CSysRes::CSysRes(const CSysRes& rhs)
{
	operator=(rhs);
}

CSysRes& CSysRes::operator=(const CSysRes& rhs)
{
	if (this != &rhs)
	{
		m_csResID = rhs.m_csResID;
		m_csName = rhs.m_csName;
		m_csResClass = rhs.m_csResClass;
		m_csContentType = rhs.m_csContentType;
		m_csFileName = rhs.m_csFileName;
		m_csAuthor = rhs.m_csAuthor;
		m_csVersion = rhs.m_csVersion;
		m_dtDevelop = rhs.m_dtDevelop;
		m_csOrgID = rhs.m_csOrgID;
	}
	return *this;
}