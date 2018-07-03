#include "stdafx.h"
#include "Utility.h"

CString CUserUtility::GenerateUniqueStr(int nLen)
{
	CString csDst;

	if (nLen <= 0)
		return csDst; 

	CString csSrc = _T("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

	for (int i = 0;i < nLen;i++)
	{
		CString csTmp(csSrc.GetAt(rand() % csSrc.GetLength()));
		csDst += csTmp;
		csSrc.Replace(csTmp, _T(""));
	}

	return csDst;
}