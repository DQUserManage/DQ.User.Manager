#pragma once


/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 陈昌健
* 创建日期： 2018-7-3
* 功能描述： 用户信息类
*
********************************************************************/
class EXPORT_USER_MANAGER CUserInfo
{
public:
	CUserInfo();
	~CUserInfo();

private:
	///< 用户ID
	CString m_UserID;

	///< 部门ID
	CString m_OrgName;

	///< 部门ID
	CString m_OrgID;

	///< 用户名称
	CString m_UserName;

	///< 性别
	CString m_UserSex;

	///< 登录密码
	CString m_UserPw;

	///< 邮箱
	CString m_UserEmail;

	///< 电话
	CString m_UserTelephone;

	///< 传真
	CString m_UserFax;

	///< 手机
	CString m_UserMobile;

	///< QQ号
	CString m_UserQQ;

	///< MSN号
	CString m_UserMSN;

	///< 简介
	CString m_Description;

public:
	/** 设置用户ID */
	void SetUserID(CString UserID) { m_UserID = UserID; }
	/** 获取用户ID */
	CString GetUserID() { return m_UserID; }

	/** 设置部门ID */
	void SetOrgID(CString OrgID) { m_OrgID = OrgID; }
	/** 获取部门ID */
	CString GetOrgID() { return m_OrgID; }

	/** 设置部门ID */
	void SetOrgName(CString OrgName) { m_OrgName = OrgName; }
	/** 获取用户ID */
	CString GetOrgName() { return m_OrgName; }

	/** 设置用户ID */
	void SetUserName(CString UserName) { m_UserName = UserName; }
	/** 获取用户ID */
	CString GetUserNames() { return m_UserName; }

	/** 设置用户ID */
	void SetUserSex(CString UserSex) { m_UserSex = UserSex; }
	/** 获取用户ID */
	CString GetUserSex() { return m_UserSex; }

	/** 设置用户ID */
	void SetUserPw(CString UserPw) { m_UserPw = UserPw; }
	/** 获取用户ID */
	CString GetUserPw() { return m_UserPw; }

	/** 设置用户ID */
	void SetUserEmail(CString UserEmail) { m_UserEmail = UserEmail; }
	/** 获取用户ID */
	CString GetUserEmail() { return m_UserEmail; }

	/** 设置用户ID */
	void SetUserTelephone(CString UserTelephone) { m_UserTelephone = UserTelephone; }
	/** 获取用户ID */
	CString GetUserTelephone() { return m_UserTelephone; }

	/** 设置用户ID */
	void SetUserFax(CString UserFax) { m_UserFax = UserFax; }
	/** 获取用户ID */
	CString GetUserFax() { return m_UserFax; }

	/** 设置用户ID */
	void SetUserMobile(CString UserMobile) { m_UserMobile = UserMobile; }
	/** 获取用户ID */
	CString GetUserMobile() { return m_UserMobile; }

	/** 设置用户ID */
	void SetUserQQ(CString UserQQ) { m_UserQQ = UserQQ; }
	/** 获取用户ID */
	CString GetUserQQ() { return m_UserQQ; }

	/** 设置用户ID */
	void SetUserMSN(CString UserMSN) { m_UserMSN = UserMSN; }
	/** 获取用户ID */
	CString GetUserMSN() { return m_UserMSN; }

	/** 设置用户ID */
	void SetDescription(CString Description) { m_Description = Description; }
	/** 获取用户ID */
	CString GetDescription() { return m_Description; }
};
