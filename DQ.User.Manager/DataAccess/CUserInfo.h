#pragma once


/********************************************************************
* Copyright (C), ����Ǫ��������������������޹�˾
*
* �� �� �ߣ� �²���
* �������ڣ� 2018-7-3
* ���������� �û���Ϣ��
*
********************************************************************/
class EXPORT_USER_MANAGER CUserInfo
{
public:
	CUserInfo();
	~CUserInfo();

private:
	///< �û�ID
	CString m_UserID;

	///< ����ID
	CString m_OrgName;

	///< ����ID
	CString m_OrgID;

	///< �û�����
	CString m_UserName;

	///< �Ա�
	CString m_UserSex;

	///< ��¼����
	CString m_UserPw;

	///< ����
	CString m_UserEmail;

	///< �绰
	CString m_UserTelephone;

	///< ����
	CString m_UserFax;

	///< �ֻ�
	CString m_UserMobile;

	///< QQ��
	CString m_UserQQ;

	///< MSN��
	CString m_UserMSN;

	///< ���
	CString m_Description;

public:
	/** �����û�ID */
	void SetUserID(CString UserID) { m_UserID = UserID; }
	/** ��ȡ�û�ID */
	CString GetUserID() { return m_UserID; }

	/** ���ò���ID */
	void SetOrgID(CString OrgID) { m_OrgID = OrgID; }
	/** ��ȡ����ID */
	CString GetOrgID() { return m_OrgID; }

	/** ���ò���ID */
	void SetOrgName(CString OrgName) { m_OrgName = OrgName; }
	/** ��ȡ�û�ID */
	CString GetOrgName() { return m_OrgName; }

	/** �����û�ID */
	void SetUserName(CString UserName) { m_UserName = UserName; }
	/** ��ȡ�û�ID */
	CString GetUserNames() { return m_UserName; }

	/** �����û�ID */
	void SetUserSex(CString UserSex) { m_UserSex = UserSex; }
	/** ��ȡ�û�ID */
	CString GetUserSex() { return m_UserSex; }

	/** �����û�ID */
	void SetUserPw(CString UserPw) { m_UserPw = UserPw; }
	/** ��ȡ�û�ID */
	CString GetUserPw() { return m_UserPw; }

	/** �����û�ID */
	void SetUserEmail(CString UserEmail) { m_UserEmail = UserEmail; }
	/** ��ȡ�û�ID */
	CString GetUserEmail() { return m_UserEmail; }

	/** �����û�ID */
	void SetUserTelephone(CString UserTelephone) { m_UserTelephone = UserTelephone; }
	/** ��ȡ�û�ID */
	CString GetUserTelephone() { return m_UserTelephone; }

	/** �����û�ID */
	void SetUserFax(CString UserFax) { m_UserFax = UserFax; }
	/** ��ȡ�û�ID */
	CString GetUserFax() { return m_UserFax; }

	/** �����û�ID */
	void SetUserMobile(CString UserMobile) { m_UserMobile = UserMobile; }
	/** ��ȡ�û�ID */
	CString GetUserMobile() { return m_UserMobile; }

	/** �����û�ID */
	void SetUserQQ(CString UserQQ) { m_UserQQ = UserQQ; }
	/** ��ȡ�û�ID */
	CString GetUserQQ() { return m_UserQQ; }

	/** �����û�ID */
	void SetUserMSN(CString UserMSN) { m_UserMSN = UserMSN; }
	/** ��ȡ�û�ID */
	CString GetUserMSN() { return m_UserMSN; }

	/** �����û�ID */
	void SetDescription(CString Description) { m_Description = Description; }
	/** ��ȡ�û�ID */
	CString GetDescription() { return m_Description; }
};
