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

#include "CSharpNameSpace.h"
#include "DBStructPublic.h"

/********************************************************************
* Copyright (C), ����Ǫ��������������������޹�˾
*
* �� �� �ߣ� ����˳
* �������ڣ� 2017-03-15
* ���������� �����б���
*
********************************************************************/
class CParameterList
{
public:
	CParameterList(void);
	~CParameterList(void);
public:
	gcroot<DbUtility^> m_db;	///<���ݿ����Ӷ���
private:
	CArray <ParameterInfo, ParameterInfo> m_ParameterList;	///<�����б�
public:	
	/** ��ղ��� */
	void		Clear();
	/** ��ȡ�������� */
	int			GetCount();
	/** ��Ӳ��� */
	void		AddParameter(CString mParameterName,COleVariant  mParameterValue);
	void		AddParameter(CString mParameterName, byte *pByte, int iByteSize);
	/** ��ȡ�����б� */
	List<DbParameter^>^ GetList();
};

/** @}*/
/** @}*/