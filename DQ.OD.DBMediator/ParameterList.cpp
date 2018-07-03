#include "stdafx.h"
#include "ParameterList.h"


CParameterList::CParameterList(void)
{
	m_ParameterList.RemoveAll();
	m_ParameterList.FreeExtra();
}


CParameterList::~CParameterList(void)
{
	Clear();
}

/** 获取参数个数 */
int		CParameterList::GetCount()
{
	return (int)m_ParameterList.GetCount();
}
/** 添加参数 */
void	CParameterList::AddParameter(CString mParameterName,COleVariant  mParameterValue)
{
	ParameterInfo para;
	para.s_sName = mParameterName;
	para.s_sValue = mParameterValue;
	m_ParameterList.Add(para);
}
void	CParameterList::AddParameter(CString mParameterName, byte *pByte, int iByteSize)
{
	ParameterInfo para;
	para.s_sName = mParameterName;
	para.s_pByteValue = pByte;
	para.s_iByteSize = iByteSize;
	m_ParameterList.Add(para);
}
/** 清空参数 */
void	CParameterList::Clear()
{
	int iCount = (int)m_ParameterList.GetCount();
	for (int i = 0; i < iCount; i++)
	{
		ParameterInfo &para = m_ParameterList.GetAt(i);
		if (para.s_pByteValue)
		{
			delete[] para.s_pByteValue;
			para.s_pByteValue = NULL;
			para.s_iByteSize = 0;
		}
	}
	m_ParameterList.RemoveAll();
	m_ParameterList.FreeExtra();
}
/** 获取参数列表 */
List<DbParameter^>^ CParameterList::GetList()
{
	List<DbParameter^> ^ list = gcnew List<DbParameter^>();
	for(int i=0;i<m_ParameterList.GetCount();i++)
	{
		ParameterInfo para=m_ParameterList.GetAt(i);
		if (para.s_pByteValue)
		{
			cli::array< byte >^ byteArray = gcnew cli::array< byte >(para.s_iByteSize);
			Marshal::Copy((System::IntPtr)(para.s_pByteValue), byteArray, 0, para.s_iByteSize);
			list->Add(m_db->CreateDbParameter( gcnew System::String(para.s_sName), byteArray));
		}
		else
			list->Add(m_db->CreateDbParameter( gcnew System::String(para.s_sName), CDbToolKit::ValToObject(para.s_sValue)));
	}
	return(list);
}