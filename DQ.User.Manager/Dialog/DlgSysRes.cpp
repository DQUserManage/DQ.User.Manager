
#include "stdafx.h"
#include "DlgSysRes.h"
#include "DlgSysResEdit.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CDlgSysRes, CUserDialogBase)

CDlgSysRes::CDlgSysRes(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_SYS_RES, pParent)
{

}

CDlgSysRes::~CDlgSysRes()
{
}

void CDlgSysRes::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSysRes, CUserDialogBase)
	ON_BN_CLICKED(IDC_BTN_ADD, &CDlgSysRes::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CDlgSysRes::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDlgSysRes::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_DELALL, &CDlgSysRes::OnBnClickedBtnDelall)
	ON_BN_CLICKED(IDC_BTN_ALL, &CDlgSysRes::OnBnClickedBtnAll)
	ON_BN_CLICKED(IDC_BTN_REVERT, &CDlgSysRes::OnBnClickedBtnRevert)
	//
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnDblClk)
END_MESSAGE_MAP()


BOOL CDlgSysRes::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	InitControl();
	InitLayout();
	InitSysRes();

	UpdateData(FALSE);

	return TRUE;
}

void CDlgSysRes::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_wndRes)
		<< (pane(HORIZONTAL)
		<< item(IDC_BTN_ALL, NORESIZE)
		<< item(IDC_BTN_REVERT, NORESIZE)
		<< itemGrowing(HORIZONTAL)
		<< item(IDC_BTN_ADD, NORESIZE)
		<< item(IDC_BTN_EDIT, NORESIZE)
		<< item(IDC_BTN_DEL, NORESIZE)
		<< item(IDC_BTN_DELALL, NORESIZE));

	UpdateLayout(layout);
}

BOOL CDlgSysRes::InitControl()
{
	CRect rcDummy;
	if (!m_wndRes.Create(WS_BORDER | WS_CHILD | WS_VISIBLE, rcDummy, this, 1000))
		return FALSE;

	m_wndRes.InsertColumn(0, _T("资源ID"), 80);
	m_wndRes.InsertColumn(1, _T("选择"), 50);
	m_wndRes.InsertColumn(2, _T("资源名称"), 80);
	m_wndRes.InsertColumn(3, _T("资源分类"), 80);
	m_wndRes.InsertColumn(4, _T("内容类型"), 80);
	m_wndRes.InsertColumn(5, _T("文件名"), 80);
	m_wndRes.InsertColumn(6, _T("作者"), 80);
	m_wndRes.InsertColumn(7, _T("版本"), 80);
	//
	m_wndRes.EnableColumnAutoSize();
	m_wndRes.EnableRowHeader();
	m_wndRes.EnableLineNumbers();
	m_wndRes.SetWholeRowSel();
	m_wndRes.SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	m_wndRes.EnableHeader(TRUE, 0);

	for (int i = 0; i < m_wndRes.GetColumnCount(); ++i)
		m_wndRes.SetHeaderAlign(i, HDF_CENTER);

	m_wndRes.SetColumnVisible(0, FALSE);

	return TRUE;
}

BOOL CDlgSysRes::InitSysRes()
{
	std::vector<CSysRes> vRes;
	CUserManagerDataService::GetInstance()->GetSysRes(vRes);

	m_wndRes.RemoveAll();
	for (size_t i = 0;i < vRes.size();i++)
	{
		CSysRes& res = vRes[i];

		CBCGPGridRow* pRow = m_wndRes.CreateRow(m_wndRes.GetColumnCount());

		pRow->GetItem(0)->SetValue((LPCTSTR)res.m_csResID);
		pRow->ReplaceItem(1, new CBCGPGridCheckItem(false));
		pRow->GetItem(2)->SetValue((LPCTSTR)res.m_csName);
		pRow->GetItem(3)->SetValue((LPCTSTR)res.m_csResClass);
		pRow->GetItem(4)->SetValue((LPCTSTR)res.m_csContentType);
		pRow->GetItem(5)->SetValue((LPCTSTR)res.m_csFileName);
		pRow->GetItem(6)->SetValue((LPCTSTR)res.m_csAuthor);
		pRow->GetItem(7)->SetValue((LPCTSTR)res.m_csVersion);

		for (int j = 2;j <= 7;j++)
		{
			pRow->GetItem(j)->AllowEdit(FALSE);
			pRow->GetItem(j)->SetReadOnly(TRUE);
		}

		m_wndRes.AddRow(pRow, FALSE);
	}
	m_wndRes.AdjustLayout();

	return TRUE;
}

void CDlgSysRes::OnBnClickedBtnAdd()
{
	CUserManagerResLock res(gInst);

	CSysRes sysRes;
	CDlgSysResEdit dlg(sysRes);
	if (dlg.DoModal() != IDOK)
		return;

	InitSysRes();
}

LRESULT CDlgSysRes::OnDblClk(WPARAM wParam, LPARAM lParam)
{
	CBCGPGridItem* pItem = (CBCGPGridItem*)(lParam);

	if (!pItem)
		return 0L;

	CBCGPGridRow* pRow = pItem->GetParentRow();
	EditSysRes(pRow);

	return 1L;
}

void CDlgSysRes::OnBnClickedBtnEdit()
{
	CBCGPGridRow* pRow = m_wndRes.GetCurSel();
	if (!pRow)
		return;

	EditSysRes(pRow);
}

void CDlgSysRes::EditSysRes(CBCGPGridRow* pRow)
{
	CSysRes sysRes;
	sysRes.m_csResID = (LPCTSTR)(_bstr_t)pRow->GetItem(0)->GetValue();
	if (!CUserManagerDataService::GetInstance()->GetSysResBasic(sysRes))
	{
		CUserUtility::ShowMessageBox(_T("获取系统资源信息失败!"));
		return;
	}

	CUserManagerResLock res(gInst);

	CDlgSysResEdit dlg(sysRes, true);
	if (dlg.DoModal() != IDOK)
		return;

	InitSysRes();
}


void CDlgSysRes::OnBnClickedBtnDel()
{
	CBCGPGridRow* pRow = m_wndRes.GetCurSel();
	if (!pRow)
		return;
	if (CUserUtility::ShowMessageBox(_T("确定要删除此系统资源吗?"), MB_YESNO) == IDNO)
		return;

	CString csResID(pRow->GetItem(0)->GetValue());
	CUserManagerDataService::GetInstance()->DelSysRes(csResID);
	m_wndRes.RemoveRow(pRow->GetRowId());
	m_wndRes.AdjustLayout();
}


void CDlgSysRes::OnBnClickedBtnDelall()
{
	if (CUserUtility::ShowMessageBox(_T("确定要清空系统资源吗?"), MB_YESNO) == IDNO)
		return;

	CUserManagerDataService::GetInstance()->DeleteAllSysRes();

	m_wndRes.RemoveAll();
}

void CDlgSysRes::OnBnClickedBtnAll()
{
	for (int i = 0;i < m_wndRes.GetRowCount(); i++)
	{
		CBCGPGridRow* pRow = m_wndRes.GetRow(i);
		((CBCGPGridCheckItem*)(pRow->GetItem(1)))->SetValue(true);
	}
}


void CDlgSysRes::OnBnClickedBtnRevert()
{
	for (int i = 0;i < m_wndRes.GetRowCount(); i++)
	{
		CBCGPGridRow* pRow = m_wndRes.GetRow(i);
		
		bool bVal = ((CBCGPGridCheckItem*)(pRow->GetItem(1)))->GetValue();
		((CBCGPGridCheckItem*)(pRow->GetItem(1)))->SetValue(!bVal);
	}
}