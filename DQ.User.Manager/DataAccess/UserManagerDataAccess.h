#pragma once

#include"../COrgInfo.h"
#include"../CUserInfo.h"

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserManagerDataAccess.h                                                       ///  @brief    �û�����ģ�����ݷ��ʽӿڣ����ж����ݵķ��ʶ�Ӧд�ڴ��ļ��У�                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

class CDbUtilityMediator;
class CDataTableMediator;

/**   ���ݷ��ʽӿڣ�����ģʽ��*/class EXPORT_USER_MANAGER CUserManagerDataService
{
public:
	~CUserManagerDataService(void);
public:
	static CUserManagerDataService*		GetInstance(void);
	static void					        DestoryInstance(void);
private:
	CUserManagerDataService();
	CUserManagerDataService(const CUserManagerDataService& rhs) { operator=(rhs); }
	CUserManagerDataService& operator=(const CUserManagerDataService&) { return *this; }
private:
	static CUserManagerDataService*		m_pSingleton;  ///<���ݷ���ʵ��

public:
	/** ��ʼ�����ݷ��ʽӿ�
	@param csConn ���ݿ����Ӵ�
	@param nType  ���ݿ�����
	*/
	bool DBInit(const CString& csConn, int nType);

	/**  �ͷ����ݿ�����н��� */
	void FreeDB();

public:
	/** ���ݷ��ʼ򵥲���*/
	bool DoTest();

public:
	/** ��ѯ������Ϣ */
	CDataTableMediator* GetOrgInfo();
	/** ͨ���������Ʋ�ѯ������Ϣ */
	CDataTableMediator* GetOrgInfoUseOrgName(CString OrgName);
	/** ��Ӳ�����Ϣ */
	BOOL InsertOrgInfo(COrgInfo OrgInfo);
	/** ɾ��������Ϣ */
	BOOL DeleteOrgInfo(CString OrgID);
	/** ɾ�������ӽڵ� */
	void DeleteChildOrgInfo(CString ParentID);
	/** ���²�����Ϣ */
	BOOL UpdateOrgInfo(COrgInfo OrgInfo);

public:
	/** ��ȡ�û���Ϣ */
	CDataTableMediator* GetBranchUser(CString ItemTxt);
	/** ����û���Ϣ */
	BOOL InsertUserInfo(CUserInfo UserInfo);
	/** ɾ���û� */
	BOOL DeleteUserInfo(CString UserID);
	/** ��ȡ�û���Ϣͨ���û�ID */
	CDataTableMediator* GetUserInfoUserUserID(CString UserID);
	/** �����û���Ϣ */
	BOOL UpdateUserInfo(CUserInfo UserInfo);
	
private:
	CDbUtilityMediator*  m_pDB;  ///<���ݷ����н���
};