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
#include "DBStructPublic.h"

class SDbUtility;
class CParameterListMediator;
class CDataTableMediator;
class CDataReaderMediator;

/********************************************************************
* Copyright (C), ����Ǫ��������������������޹�˾
*
* �� �� �ߣ� ����˳
* �������ڣ� 2017-03-15
* ���������� ���ݿ�����н���
*
********************************************************************/
class AFX_EXT_CLASS CDbUtilityMediator
{
public:
	CDbUtilityMediator(CString sConnect, DBConnectType eType);
	~CDbUtilityMediator(void);

private:
	SDbUtility *		m_pDbUtility;
	CString				m_sErrorMessage;		///<

	vector<CParameterListMediator *> m_vParameterList;

private:
	/** �����ʱ�����б� */
	void		ClearParameterList();
public:
	/** ���������б� */
	CParameterListMediator * CreateParameterList();
	/** �����ݱ� */
	CDataTableMediator*	ExecuteTable(CString SQL);
	/** �����ݱ� */
	CDataTableMediator*	ExecuteTable(CString SQL,CParameterListMediator* pList);
	/** �����ݱ� */
	CDataTableMediator*	ExecuteOrclTable(CString SQL);
	/** �����ݱ� */
	CDataTableMediator*	ExecuteOrclTable(CString SQL,CParameterListMediator* pList);
	/** ִ��SQL */
	int 				ExecuteQuery(CString SQL);
	/** ִ��SQL */
	int 				ExecuteQuery(CString SQL,CParameterListMediator* pList);
	/** ִ��SQL */
	int 				ExecuteQuery(CStringArray* SQLList);
	/** ִ��SQL */
	int					ExecuteScalar(CString SQL);
	/** ִ�д洢���� */
	void				ExecuteProcedure(CString sProcedureName, CParameterListMediator* pList);
	/** ִ��Sql��ȡ����� */
	CDataReaderMediator*ExecuteReader(CString SQL);

};

/** @}*/
/** @}*/