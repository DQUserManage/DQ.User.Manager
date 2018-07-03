#include "stdafx.h"
#include "ParameterListMediator.h"
#include "ParameterList.h"



CParameterListMediator::CParameterListMediator(void)
{
	m_pParameterList = new CParameterList();
}
CParameterListMediator::CParameterListMediator(CParameterList *	pParameterList)
{
	m_pParameterList = pParameterList;
}


CParameterListMediator::~CParameterListMediator(void)
{
	if (m_pParameterList)
		delete m_pParameterList;
}

/** 清空参数 */
void	CParameterListMediator::Clear()
{
	m_pParameterList->Clear();
}
/** 获取参数个数 */
int		CParameterListMediator::GetCount()
{
	return m_pParameterList->GetCount();
}
/** 添加参数 */
void	CParameterListMediator::AddParameter(CString mParameterName,COleVariant  mParameterValue)
{
	m_pParameterList->AddParameter(mParameterName, mParameterValue);
}
void	CParameterListMediator::AddParameter(CString mParameterName, byte *pByte, int iByteSize)
{
	m_pParameterList->AddParameter(mParameterName, pByte, iByteSize);
}
