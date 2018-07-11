
#include "stdafx.h"
#include "DlgSelRes.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CDlgSelRes, CUserDialogBase)

CDlgSelRes::CDlgSelRes(const CString& csResID, CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_SEL_RES, pParent)
	, m_csResID(csResID)
{
	m_pSelRow = nullptr;
}

CDlgSelRes::~CDlgSelRes()
{
}

void CDlgSelRes::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelRes, CUserDialogBase)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK, OnDblClk)
	ON_BN_CLICKED(IDOK, &CDlgSelRes::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgSelRes::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	InitControl();
	InitLayout();
	InitData();

	UpdateData(FALSE);

	return TRUE;  
}

void CDlgSelRes::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_wndRes)
		<<(pane(HORIZONTAL)<<itemGrowing(HORIZONTAL)<<item(IDOK,NORESIZE)<<item(IDCANCEL,NORESIZE));

	UpdateLayout(layout);
}

void CDlgSelRes::InitControl()
{
	CRect rcDummy;
	if (!m_wndRes.Create(WS_BORDER | WS_CHILD | WS_VISIBLE, rcDummy, this, 1000))
		return;

	m_wndRes.InsertColumn(0, _T("资源ID"), 80);
	m_wndRes.InsertColumn(1, _T("资源名称"), 80);
	m_wndRes.InsertColumn(2, _T("资源分类"), 80);
	m_wndRes.InsertColumn(3, _T("内容类型"), 80);
	m_wndRes.InsertColumn(4, _T("文件名"), 80);
	m_wndRes.InsertColumn(5, _T("作者"), 80);
	m_wndRes.InsertColumn(6, _T("版本"), 80);
	//
	m_wndRes.EnableColumnAutoSize();
	m_wndRes.EnableRowHeader();
	m_wndRes.EnableLineNumbers();
	m_wndRes.SetWholeRowSel();
	m_wndRes.SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	m_wndRes.EnableHeader(TRUE, 0);
	m_wndRes.SetReadOnly();

	for (int i = 0; i < m_wndRes.GetColumnCount(); ++i)
		m_wndRes.SetHeaderAlign(i, HDF_CENTER);

	m_wndRes.SetColumnVisible(0, FALSE);
}

void CDlgSelRes::InitData()
{
	m_pSelRow = nullptr;
	//
	std::vector<CSysRes> vRes;
	CUserManagerDataService::GetInstance()->GetSysRes(vRes);

	m_wndRes.RemoveAll();
	for (size_t i = 0;i < vRes.size();i++)
	{
		CSysRes& res = vRes[i];

		CBCGPGridRow* pRow = m_wndRes.CreateRow(m_wndRes.GetColumnCount());

		pRow->GetItem(0)->SetValue((LPCTSTR)res.m_csResID);
		pRow->GetItem(1)->SetValue((LPCTSTR)res.m_csName);
		pRow->GetItem(2)->SetValue((LPCTSTR)res.m_csResClass);
		pRow->GetItem(3)->SetValue((LPCTSTR)res.m_csContentType);
		pRow->GetItem(4)->SetValue((LPCTSTR)res.m_csFileName);
		pRow->GetItem(5)->SetValue((LPCTSTR)res.m_csAuthor);
		pRow->GetItem(6)->SetValue((LPCTSTR)res.m_csVersion);

		if (res.m_csResID.CompareNoCase(m_csResID) == 0)
			m_pSelRow = pRow;

		m_wndRes.AddRow(pRow, FALSE);
	}
	m_wndRes.AdjustLayout();
	//
	if (m_pSelRow)
		m_wndRes.SetCurSel(m_pSelRow, TRUE);
}

LRESULT CDlgSelRes::OnDblClk(WPARAM wParam, LPARAM lParam)
{
	CBCGPGridItem* pItem = (CBCGPGridItem*)(lParam);

	if (!pItem)
		return 0L;

	CBCGPGridRow* pRow = pItem->GetParentRow();

	m_csResID = (LPCTSTR)(_bstr_t)pRow->GetItem(0)->GetValue();
	m_csResName = (LPCTSTR)(_bstr_t)pRow->GetItem(1)->GetValue();

	OnOK();

	return 1L;
}

void CDlgSelRes::OnBnClickedOk()
{
	CBCGPGridRow* pRow = m_wndRes.GetCurSel();

	if (!pRow)
		return;

	m_csResID = (LPCTSTR)(_bstr_t)pRow->GetItem(0)->GetValue();
	m_csResName = (LPCTSTR)(_bstr_t)pRow->GetItem(1)->GetValue();

	OnOK();
}
