#pragma once

///////////////////////////////////////////////////////////////////////////////
///                                                                            
///  @file     UserManagerDataAccess.h                                                       
///  @brief    用户管理模块数据访问接口（所有对数据的访问都应写在此文件中）                                                                             
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
   数据访问接口（单例模式）
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
	static CUserManagerDataService*		m_pSingleton;  ///<数据访问实例

public:
	/** 初始化数据访问接口
	@param csConn 数据库连接串
	@param nType  数据库类型
	*/
	bool DBInit(const CString& csConn, int nType);

	/**  释放数据库访问中介者 */
	void FreeDB();

public:
	/** 查询部门信息 */
	std::shared_ptr<CDataTableMediator> GetOrgInfo();
	/** 通过部门名称查询部门信息 */
	std::shared_ptr<CDataTableMediator> GetOrgInfoUseOrgName(CString OrgName);
	/** 根据部门ID获取信息 */
	std::shared_ptr<CDataTableMediator> GetOrgInfoUseOrgID(CString OrgID);
	/** 添加部门信息 */
	BOOL InsertOrgInfo(COrgInfo OrgInfo);
	/** 删除部门信息 */
	BOOL DeleteOrgInfo(CString OrgID);
	/** 删除部门子节点 */
	void DeleteChildOrgInfo(CString ParentID);
	/** 更新部门信息 */
	BOOL UpdateOrgInfo(COrgInfo OrgInfo);
	/** 获取根部门信息 */
	BOOL GetDeptNode(const CString& csParent,vector<COrgInfo>& vDept);
public:
	/** 获取用户信息 */
	CDataTableMediator* GetBranchUser();
	/** 添加用户信息 */
	BOOL InsertUserInfo(CUserInfo UserInfo);
	/** 删除用户 */
	BOOL DeleteUserInfo(CString UserID);
	/** 获取用户信息通过用户ID */
	CDataTableMediator* GetUserInfoUserUserID(CString UserID);
	/** 更新用户信息 */
	BOOL UpdateUserInfo(CUserInfo UserInfo);

public:
	/** 获取角色信息 */
	std::shared_ptr<CDataTableMediator> GetRoleInfo();
	/** 添加用户角色信息表 */
	BOOL InsertUserRoleInfo(CString UserID,CString UserRole);
	
public:  ///<系统资源数据访问

	/**获取系统资源基本信息 */
	bool GetSysRes(std::vector<CSysRes>& vRes);

	/** 清空系统资源信息 */
	bool DeleteAllSysRes();

	/** 删除特定系统资源信息*/
	bool DelSysRes(const CString& csResID);

	/** 新增系统资源*/
	bool AddSysRes(const CSysRes& res);

	/** 编辑系统资源*/
	bool EditSysRes(const CSysRes& res);

	/** 上传系统资源*/
	bool UploadSysRes(const CSysRes& res, const CString& csFileName);

	/** 获取系统资源信息*/
	bool GetSysResBasic(CSysRes& res);

	/** 获取上传内容 */
	bool GetUploadSysRes(const CString& csResID, BYTE*& pBuf, int& nSize);

public:  ///<系统模块数据访问

	/** 获取系统模块树信息*/
	bool GetSysModeNode(const CString& csParentID, vector<CSysMod>& vNode);

	/** 获取系统模块树信息*/
	bool SaveSysModeInfo(CStringArray& vSQL);

	/** 获取系统模块基本信息*/
	bool GetSysModeBasic(CSysMod& mod);
private:
	CDbUtilityMediator*  m_pDB;  ///<数据访问中介者
};