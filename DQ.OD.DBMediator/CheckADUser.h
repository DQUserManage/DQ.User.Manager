#pragma once


class AFX_EXT_CLASS CCheckADUser
{
public:
	CCheckADUser(void);
	~CCheckADUser(void);
public:
	/** 验证用户信息 */
	static bool	CheckADUser(CString & strUserName,CString & strPassword,CString & strADServiceAddress,CString & strDBConstring);
};

