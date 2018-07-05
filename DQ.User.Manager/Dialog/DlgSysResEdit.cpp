#include "stdafx.h"
#include "DlgSysResEdit.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CDlgSysResEdit, CUserDialogModelBase)

CDlgSysResEdit::CDlgSysResEdit(CSysRes& res, bool bEdit,CWnd* pParent /*=NULL*/)
	: CUserDialogModelBase(IDD_RES_EDIT, pParent)
	, m_SysRes(res)
	, m_bEdit(bEdit)
{

}

CDlgSysResEdit::~CDlgSysResEdit()
{
}

void CDlgSysResEdit::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogModelBase::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_NAME, m_SysRes.m_csName);
	DDX_Text(pDX, IDC_EDT_CLASS, m_SysRes.m_csResClass);
	DDX_Text(pDX, IDC_EDT_CONTENT_TYPE, m_SysRes.m_csContentType);
	DDX_Control(pDX, IDC_EDT_UPLOAD, m_edtUpload);
	DDX_Text(pDX, IDC_EDT_FILENAME, m_SysRes.m_csFileName);
	DDX_Text(pDX, IDC_EDT_AUTHOR, m_SysRes.m_csAuthor);
	DDX_Text(pDX, IDC_EDT_VERSION, m_SysRes.m_csVersion);
	DDX_Control(pDX, IDC_BTN_DATE, m_btnDate);
	DDX_Control(pDX, IDC_EDT_ORG, m_edtOrg);
}


BEGIN_MESSAGE_MAP(CDlgSysResEdit, CUserDialogModelBase)
	ON_BN_CLICKED(IDOK, &CDlgSysResEdit::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgSysResEdit::OnInitDialog()
{
	CUserDialogModelBase::OnInitDialog();

	CString csTitle;
	csTitle.Format(_T("系统资源 - %s"), m_bEdit ? _T("编辑") : _T("新建"));
	SetWindowText(csTitle);

	InitControl();

	UpdateData(FALSE);

	return TRUE;  
}

void CDlgSysResEdit::InitControl()
{
	UINT stateFlags = CBCGPDateTimeCtrl::DTM_DATE|
		CBCGPDateTimeCtrl::DTM_SPIN|
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR;

	const UINT stateMask =
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME |
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE |
		CBCGPDateTimeCtrl::DTM_SECONDS;

	m_btnDate.SetState(stateFlags, stateMask);
	m_btnDate.m_monthFormat = 2;
	m_btnDate.m_type2DigitsInYear = FALSE;

	m_edtUpload.EnableFileBrowseButton();
	m_edtOrg.EnableBrowseButton();

	if (m_bEdit)
		m_btnDate.SetDate(m_SysRes.m_dtDevelop);
}

void CDlgSysResEdit::OnBnClickedOk()
{
	if (!UpdateData())
	{
		UpdateData(FALSE);
		return;
	}
	//
	if (m_SysRes.m_csName.IsEmpty())
	{
		CUserUtility::ShowMessageBox(_T("系统资源名称不能为空!"));
		return;
	}
	//部门ID
	m_SysRes.m_csOrgID = m_edtOrg.m_csDeptID;
	//提交日期
	m_SysRes.m_dtDevelop = m_btnDate.GetDate();

	bool res = false;
	if (m_bEdit)
		res = CUserManagerDataService::GetInstance()->EditSysRes(m_SysRes);
	else
	{
		m_SysRes.m_csResID = CUserUtility::GenerateUniqueStr(20);
		res = CUserManagerDataService::GetInstance()->AddSysRes(m_SysRes);
	}

	CString csFileName;
	m_edtUpload.GetWindowText(csFileName);
	if (res && !csFileName.IsEmpty())
		CUserManagerDataService::GetInstance()->UploadSysRes(m_SysRes, csFileName);

	if (!res)
	{
		CUserUtility::ShowMessageBox(_T("系统资源信息编辑失败!"));
		return;
	}

	OnOK();
}
