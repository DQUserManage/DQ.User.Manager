#include "stdafx.h"
#include "Utility.h"

//** 获取时间（精确到毫秒级）*/
unsigned long long GetCurrentTimeMsec()
{
	struct timeval tv;
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;

	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tv.tv_sec = clock;
	tv.tv_usec = wtm.wMilliseconds * 1000;
	return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
}

CString CUserUtility::GenerateUniqueStr(int nLen)
{
	/*
	CString csDst;

	if (nLen <= 0)
		return csDst;

	CString csSrc = _T("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

	while(csDst.GetLength()<nLen)
	{
		CString csTmp(csSrc.GetAt(rand() % 62));
		if (csDst.Find(csTmp) == -1)
			csDst += csTmp;
	}

	return csDst;
	*/

	CString csDst;

	if (nLen <= 0)
		return csDst;

	CString csSrc = _T("aBcDeFgHiG2kLm3No4Pq5RsTuV0wXyZ1AbC6dEfG7hIgKlMnOpQ8rStUv9WxYz");
	int shift = rand() % csSrc.GetLength();
	csDst += csSrc.GetAt(shift);

	CString csNum;
	csNum.Format(_T("%I64d"), GetCurrentTimeMsec());
	int nNum = csNum.GetLength();
	if (nNum > nLen)  //如果数字串长度大于生成串长度,则截取部分数字串
	{
		int nStart = nNum - nLen + 1;
		for (int i = 0;i < nLen - 1;i++)
			csDst += csNum.Mid(nStart + i, 1);
	}
	else if (nNum < nLen) //如果数字串长度小于生成串长度,则补零
	{
		csDst += csNum;
		for (int i = 0;i < nLen - nNum - 1;i++)
			csDst.Insert(1, _T("0"));
	}

	//根据映射将数字替换为字符
	for (int i = 1;i < csDst.GetLength();i++) {
		int pos = (csDst.GetAt(i) - 48 + shift) % csSrc.GetLength();;
		csDst.SetAt(i, csSrc[pos]);
	}

	//针对重复的字符进行优化,将重复的字符替换之
	if (csDst.GetLength() > 2) {
		for (int i = 2;i < csDst.GetLength();i++) {
			if (csDst.GetAt(i) == csDst.GetAt(i - 1)) {
				//替换的字符要确保不在当前的映射范围之内
				csDst.SetAt(i - 1, csSrc[(shift + csSrc.GetLength() - i) % csSrc.GetLength()]);
			}
		}
	}

	return csDst;
}

int CUserUtility::ShowMessageBox(CString csMsg, UINT nBtn, CString csCaption, UINT nIcon)
{

	BCGP_MSGBOXPARAMS params;

	params.lpszCaption = csCaption;
	params.lpszText = csMsg;
	params.dwStyle = nBtn;
	params.dwStyle |= nIcon;

	UINT idAutoRespond = 0;
	params.puiAutoRespond = &idAutoRespond;
	params.bShowCheckBox = FALSE;
	params.bUseNativeControls = FALSE;
	params.bUseNativeCaption = params.bUseNativeControls;

	return BCGPMessageBoxIndirect(&params);
}

BOOL CUserUtility::IsFileExist(LPCTSTR lpszFilePath)
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = CreateFile(lpszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
	);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		bExist = TRUE;
	}

	return bExist;
}

BOOL CUserUtility::PutFileIntoVariant(COleVariant *ovData, const CString& csFileName)
{
	if (csFileName.IsEmpty() || !IsFileExist(csFileName))
		return FALSE;

	BOOL fRetVal = FALSE;

	CFile file;
	BYTE* pBuf = nullptr;
	try
	{
		file.Open(csFileName, CFile::modeRead);

		long nBufLen = file.GetLength();
		pBuf = (BYTE*)malloc(file.GetLength());
		file.SeekToBegin();
		file.Read(pBuf, nBufLen);

		VARIANT var;
		VariantInit(&var);
		var.vt = VT_ARRAY | VT_UI1;

		SAFEARRAYBOUND  rgsabound[1];
		rgsabound[0].cElements = nBufLen;
		rgsabound[0].lLbound = 0;
		var.parray = SafeArrayCreate(VT_UI1, 1, rgsabound);

		if (var.parray != NULL)
		{
			void * pArrayData = NULL;
			SafeArrayAccessData(var.parray, &pArrayData);
			memcpy(pArrayData, pBuf, nBufLen);

			SafeArrayUnaccessData(var.parray);

			*ovData = var;
			VariantClear(&var);
			fRetVal = TRUE;
		}
	}
	catch (...)
	{
	}

	if (file.m_hFile != INVALID_HANDLE_VALUE)
		file.Close();

	if (pBuf)
	{
		free(pBuf);
		pBuf = nullptr;
	}
	return fRetVal;
}