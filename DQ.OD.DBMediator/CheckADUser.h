#pragma once


class AFX_EXT_CLASS CCheckADUser
{
public:
	CCheckADUser(void);
	~CCheckADUser(void);
public:
	/** ��֤�û���Ϣ */
	static bool	CheckADUser(CString & strUserName,CString & strPassword,CString & strADServiceAddress,CString & strDBConstring);
};

