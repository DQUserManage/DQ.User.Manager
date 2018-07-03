/**
* @defgroup 
* @author   ����˳
* @version  1.0
* @date     2017-03-15
* @{
*/


/**
* @file
* @brief
* @author   ����˳
* @date     2017-03-15
* @version  1.0
* @note
* @{
*/
#pragma once
//#include <vcclr.h> 

class CParameterList;

/********************************************************************
* Copyright (C), ����Ǫ��������������������޹�˾
*
* �� �� �ߣ� ����˳
* �������ڣ� 2017-03-15
* ���������� �����б��н���
*
********************************************************************/
class AFX_EXT_CLASS CParameterListMediator
{
public:
	CParameterListMediator(void);
	CParameterListMediator(CParameterList *	pParameterList);
	~CParameterListMediator(void);

private:
	CParameterList *	m_pParameterList;	///<�����б�

public:	
	/** ��ȡ�����б� */
	CParameterList * GetParameterList() { return m_pParameterList; }
	/** ��ղ��� */
	void		Clear();
	/** ��ȡ�������� */
	int			GetCount();
	/** ��Ӳ��� */
	void		AddParameter(CString mParameterName, COleVariant  mParameterValue);
	void		AddParameter(CString mParameterName, byte *pByte, int iByteSize);
};

/** @}*/
/** @}*/