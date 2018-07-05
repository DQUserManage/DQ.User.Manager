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
		BYTE *pBuf = (BYTE*)malloc(file.GetLength());
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