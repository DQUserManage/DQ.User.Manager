
#include "stdafx.h"
#include "UserDialogBase.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(CUserDialogBase, ETSLayoutDialog)

CUserDialogBase::CUserDialogBase(UINT nID,CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(nID, pParent)
{

}

CUserDialogBase::~CUserDialogBase() 
{
}

void CUserDialogBase::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserDialogBase, ETSLayoutDialog)
END_MESSAGE_MAP()


// CUserDialogBase message handlers

BOOL CUserDialogBase::OnInitDialog()
{
	ETSLayoutDialog::OnInitDialog();
	EnableVisualManagerStyle();

	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),TRUE);
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),FALSE);

	return TRUE;  
}

// CUserDialogModelBase dialog

IMPLEMENT_DYNAMIC(CUserDialogModelBase, CBCGPDialog)

CUserDialogModelBase::CUserDialogModelBase(UINT nID,CWnd* pParent /*=NULL*/)
: CBCGPDialog(nID, pParent)
{

}

CUserDialogModelBase::~CUserDialogModelBase()
{
}

void CUserDialogModelBase::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserDialogModelBase, CBCGPDialog)
END_MESSAGE_MAP()


// CUserDialogModelBase message handlers

BOOL CUserDialogModelBase::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	EnableVisualManagerStyle();

	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),TRUE);
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),FALSE);

	return TRUE;  
}

