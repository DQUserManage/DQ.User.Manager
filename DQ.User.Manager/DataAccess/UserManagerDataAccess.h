#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     UserManagerDataAccess.h                                                       
///  @brief    �û�����ģ�����ݷ��ʽӿڣ����ж����ݵķ��ʶ�Ӧд�ڴ��ļ��У�                                                                             
///  @author   lqt                                                                                                        
///  @version  1.0.0                                                
///  @date     2018.06.28                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////

class CDbUtilityMediator;
class CDataTableMediator;

#include <vector>
#include <memory>
using namespace std;

/**
   ���ݷ��ʽӿڣ�����ģʽ��
*/
class EXPORT_USER_MANAGER CUserManagerDataService
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
	/** ��ѯ������Ϣ */
	std::shared_ptr<CDataTableMediator> GetOrgInfo();
	/** ͨ���������Ʋ�ѯ������Ϣ */
	std::shared_ptr<CDataTableMediator> GetOrgInfoUseOrgName(CString OrgName);
	/** ���ݲ���ID��ȡ��Ϣ */
	std::shared_ptr<CDataTableMediator> GetOrgInfoUseOrgID(CString OrgID);
	/** ��Ӳ�����Ϣ */
	BOOL InsertOrgInfo(COrgInfo OrgInfo);
	/** ɾ��������Ϣ */
	BOOL DeleteOrgInfo(CString OrgID);
	/** ɾ�������ӽڵ� */
	void DeleteChildOrgInfo(CString ParentID);
	/** ���²�����Ϣ */
	BOOL UpdateOrgInfo(COrgInfo OrgInfo);
	/** ��ȡ��������Ϣ */
	BOOL GetDeptNode(const CString& csParent,vector<COrgInfo>& vDept);
public:
	/** ��ȡ�û���Ϣ */
	CDataTableMediator* GetBranchUser();
	/** ����û���Ϣ */
	BOOL InsertUserInfo(CUserInfo UserInfo);
	/** ɾ���û� */
	BOOL DeleteUserInfo(CString UserID);
	/** ��ȡ�û���Ϣͨ���û�ID */
	CDataTableMediator* GetUserInfoUserUserID(CString UserID);
	/** �����û���Ϣ */
	BOOL UpdateUserInfo(CUserInfo UserInfo);

public:
	/** ��ȡ��ɫ��Ϣ */
	std::shared_ptr<CDataTableMediator> GetRoleInfo();
	/** ����û���ɫ��Ϣ�� */
	BOOL InsertUserRoleInfo(CString UserID,CString UserRole);
	
public:  ///<ϵͳ��Դ���ݷ���

	/**��ȡϵͳ��Դ������Ϣ */
	bool GetSysRes(std::vector<CSysRes>& vRes);

	/** ���ϵͳ��Դ��Ϣ */
	bool DeleteAllSysRes();

	/** ɾ���ض�ϵͳ��Դ��Ϣ*/
	bool DelSysRes(const CString& csResID);

	/** ����ϵͳ��Դ*/
	bool AddSysRes(const CSysRes& res);

	/** �༭ϵͳ��Դ*/
	bool EditSysRes(const CSysRes& res);

	/** �ϴ�ϵͳ��Դ*/
	bool UploadSysRes(const CSysRes& res, const CString& csFileName);

	/** ��ȡϵͳ��Դ��Ϣ*/
	bool GetSysResBasic(CSysRes& res);

	/** ��ȡ�ϴ����� */
	bool GetUploadSysRes(const CString& csResID, BYTE*& pBuf, int& nSize);

public:  ///<ϵͳģ�����ݷ���

	/** ��ȡϵͳģ������Ϣ*/
	bool GetSysModeNode(const CString& csParentID, vector<CSysMod>& vNode);

	/** ��ȡϵͳģ������Ϣ*/
	bool SaveSysModeInfo(CStringArray& vSQL);

	/** ��ȡϵͳģ�������Ϣ*/
	bool GetSysModeBasic(CSysMod& mod);
private:
	CDbUtilityMediator*  m_pDB;  ///<���ݷ����н���
};