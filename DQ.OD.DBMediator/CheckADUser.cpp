#include "stdafx.h"
#include "CheckADUser.h"

#include "CSharpNameSpace.h"



CCheckADUser::CCheckADUser(void)
{
}


CCheckADUser::~CCheckADUser(void)
{

}

bool	CCheckADUser::CheckADUser(CString & strUserName,CString & strPassword,CString & strADServiceAddress,CString & strDBConstring)
{
	CheckADUserHelp ^ checkADUser = gcnew CheckADUserHelp();

	strDBConstring = checkADUser->CheckADUser(gcnew String(strUserName),gcnew String(strPassword),gcnew String(strADServiceAddress));

	if (strDBConstring.IsEmpty())
		return false;

	return true;
}