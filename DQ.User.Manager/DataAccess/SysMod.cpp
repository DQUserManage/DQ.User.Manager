#include "stdafx.h"
#include "SysMod.h"

CSysMod::CSysMod()
{
	m_csModID.Empty();
	m_csName.Empty();
	m_csModType.Empty();
	m_csResID.Empty();
	m_csResName.Empty();
	m_nOrder = -1;
}

CSysMod::~CSysMod()
{

}

CSysMod::CSysMod(const CSysMod& rhs)
{
	operator=(rhs);
}

CSysMod& CSysMod::operator=(const CSysMod& rhs)
{
	if (this != &rhs)
	{
		m_csModID = rhs.m_csModID;
		m_csName = rhs.m_csName;
		m_csModType = rhs.m_csModType;
		m_csResID = rhs.m_csResID;
		m_csResName = rhs.m_csResName;
		m_nOrder = rhs.m_nOrder;
	}
	return *this;
}