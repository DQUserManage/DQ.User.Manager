#include "stdafx.h"
#include "DlgSysMod.h"
#include "resource.h"
#include "DlgModeInfo.h"

IMPLEMENT_DYNAMIC(CDlgSysMod, CUserDialogBase)

CDlgSysMod::CDlgSysMod(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_SYS_MOD, pParent)
{

}

CDlgSysMod::~CDlgSysMod()
{
}

void CDlgSysMod::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOD_TREE, m_wndMod);
}


BEGIN_MESSAGE_MAP(CDlgSysMod, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlgSysMod::OnBnClickedOk)
	ON_NOTIFY(NM_RCLICK, IDC_MOD_TREE, &CDlgSysMod::OnNMRClickModTree)
	//
	ON_COMMAND(IDM_ADD_MOD, OnAdd)
	ON_COMMAND(IDM_EDT_MOD, OnEdt)
	ON_COMMAND(IDM_DEL_MOD, OnDel)
	ON_COMMAND(IDM_MOVE_TOP, OnTop)
	ON_COMMAND(IDM_MOVE_UP,  OnUp)
	ON_COMMAND(IDM_MOVE_DOWN, OnDown)
	ON_COMMAND(IDM_MOVE_BOTTOM, OnBottom)

END_MESSAGE_MAP()

BOOL CDlgSysMod::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	InitLayout();
	InitMod();

	UpdateData(FALSE);

	return TRUE;  
}

void CDlgSysMod::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_wndMod)
		<< (pane(HORIZONTAL)
			<< itemGrowing(HORIZONTAL)
			<< item(IDOK, NORESIZE)
			<< item(IDCANCEL, NORESIZE));

	UpdateLayout(layout);
}

void CDlgSysMod::InitMod()
{
	m_wndMod.SetRedraw(FALSE);

	m_wndMod.DeleteAllItems();
	m_Ids.RemoveAll();

	std::vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(_T(""), vMode);
	for (size_t i = 0;i < vMode.size();i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hRoot = m_wndMod.InsertItem(info.m_csName,TVI_ROOT);
		m_Ids[hRoot] = info;

		FillModeTree(hRoot, info.m_csModID);
		
		m_wndMod.Expand(hRoot, TVE_EXPAND);
	}

	m_wndMod.SetRedraw(TRUE);
}

void CDlgSysMod::FillModeTree(HTREEITEM hParent, const CString& csParent)
{
	std::vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(csParent, vMode);
	for (size_t i = 0;i < vMode.size();i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hItem = m_wndMod.InsertItem(info.m_csName, hParent);
		m_Ids[hItem] = info;

		FillModeTree(hItem, info.m_csModID);
	}
}

void CDlgSysMod::OnNMRClickModTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	UINT uFlags = 0;
	HTREEITEM hItem = m_wndMod.HitTest(pt, &uFlags);

	if (hItem != NULL)
		m_wndMod.Select(hItem, TVGN_CARET);
	else
		m_wndMod.Select(NULL, TVGN_CARET);

	//弹出右键菜单
	PopupMenu(hItem);

	*pResult = 0;
}

void CDlgSysMod::PopupMenu(HTREEITEM hItem)
{
	CPoint pt;
	GetCursorPos(&pt);

	HMENU hMenu = NULL;
	hMenu = ::CreatePopupMenu();
	if (NULL == hItem)
		AppendMenu(hMenu, MF_STRING, IDM_ADD_MOD, _T("新建"));
	else
	{
		AppendMenu(hMenu, MF_STRING, IDM_ADD_MOD, _T("新建"));
		AppendMenu(hMenu, MF_STRING, IDM_EDT_MOD, _T("修改"));
		AppendMenu(hMenu, MF_STRING, IDM_DEL_MOD, _T("删除"));

		AppendMenu(hMenu, MF_SEPARATOR, 0,_T(""));

		AppendMenu(hMenu, MF_STRING, IDM_MOVE_TOP, _T("移置顶部"));
		AppendMenu(hMenu, MF_STRING, IDM_MOVE_UP, _T("上移"));
		AppendMenu(hMenu, MF_STRING, IDM_MOVE_DOWN, _T("下移"));
		AppendMenu(hMenu, MF_STRING, IDM_MOVE_BOTTOM, _T("移置底部"));
	}

	CBCGPPopupMenu *pMenu = new CBCGPPopupMenu();
	pMenu->SetAutoDestroy();
	pMenu->Create(this, pt.x, pt.y, hMenu, FALSE, TRUE);
}

void CDlgSysMod::OnAdd()
{
	CUserManagerResLock res(gInst);

	HTREEITEM hItem = m_wndMod.GetSelectedItem();

	CSysMod mod;
	mod.m_csModID = CUserUtility::GenerateUniqueStr(20);
	CDlgModeInfo dlg(mod);

	if (dlg.DoModal() != IDOK)
		return;

	m_wndMod.SetRedraw(FALSE);

	if (hItem == nullptr)
	{
		//添加根模块
		HTREEITEM hRoot = m_wndMod.InsertItem(mod.m_csName, TVI_ROOT);
		m_Ids[hRoot] = mod;
	}
	else
	{
		//添加子模块
		HTREEITEM hChild = m_wndMod.InsertItem(mod.m_csName, hItem);
		m_Ids[hChild] = mod;
	}

	m_wndMod.SetRedraw(TRUE);

}

void CDlgSysMod::OnEdt()
{
	HTREEITEM hItem = m_wndMod.GetSelectedItem();
	if (!hItem)
		return;

	CSysMod mod;
	if (!m_Ids.Lookup(hItem, mod))
		return;

	CDlgModeInfo dlg(mod,true);
	if (dlg.DoModal() != IDOK)
		return;

	m_wndMod.SetItemText(hItem, mod.m_csName);

	m_Ids[hItem] = mod;
}

void CDlgSysMod::OnDel()
{
	HTREEITEM hItem = m_wndMod.GetSelectedItem();
	if (!hItem)
		return;

	if (CUserUtility::ShowMessageBox(_T("确定要删除吗?"), MB_YESNO) == IDNO)
		return;

	m_wndMod.SetRedraw(FALSE);

	HTREEITEM hChild = m_wndMod.GetChildItem(hItem);
	while (hChild)
	{
		DeleteChildBranch(hChild);

		m_Ids.RemoveKey(hChild);
		hChild = m_wndMod.GetNextSiblingItem(hChild);
	}
	//
	m_Ids.RemoveKey(hItem);
	m_wndMod.DeleteItem(hItem);

	m_wndMod.SetRedraw(TRUE);
}

void CDlgSysMod::DeleteChildBranch(HTREEITEM hParent)
{
	HTREEITEM hChild = m_wndMod.GetChildItem(hParent);
	while (hChild)
	{
		DeleteChildBranch(hChild);

		m_Ids.RemoveKey(hChild);
		hChild = m_wndMod.GetNextSiblingItem(hChild);
	}
}

//--------------------------节点移动
HTREEITEM CDlgSysMod::CopyBranch(HTREEITEM hItem, CSysMod& mod, HTREEITEM hParent, HTREEITEM hAfter)
{
	HTREEITEM hNewItem = m_wndMod.InsertItem(mod.m_csName,hParent,hAfter);

	HTREEITEM hChild = m_wndMod.GetChildItem(hItem);
	while (hChild)
	{
		CSysMod info;
		if (!m_Ids.Lookup(hChild, info))
			return NULL;

		HTREEITEM hObj = m_wndMod.InsertItem(info.m_csName, hNewItem);
		m_Ids.RemoveKey(hChild);
		m_Ids[hObj] = info;

		if (!CopyChildBranch(hObj,hChild))
			return NULL;

		hChild = m_wndMod.GetNextSiblingItem(hChild);
	}
	return hNewItem;
}

BOOL CDlgSysMod::CopyChildBranch(HTREEITEM hParentNew, HTREEITEM hItem)
{
	HTREEITEM hChild = m_wndMod.GetChildItem(hItem);
	while (hChild)
	{
		CSysMod info;
		if (!m_Ids.Lookup(hChild, info))
			return FALSE;

		HTREEITEM hObj = m_wndMod.InsertItem(info.m_csName, hParentNew);
		m_Ids.RemoveKey(hChild);
		m_Ids[hObj] = info;

		if (!CopyChildBranch(hObj, hChild))
			return FALSE;

		hChild = m_wndMod.GetNextSiblingItem(hChild);
	}
	return TRUE;
}
//
void CDlgSysMod::OnTop()
{
	HTREEITEM hItem = m_wndMod.GetSelectedItem();
	if (!hItem)
		return;

	CSysMod mod;
	if (!m_Ids.Lookup(hItem, mod))
		return;
	
	HTREEITEM hParent = m_wndMod.GetParentItem(hItem);
	HTREEITEM hPrev = m_wndMod.GetPrevSiblingItem(hItem);

	if (!hPrev)
		return;
	
	m_wndMod.SetRedraw(FALSE);

	HTREEITEM hNewItem = CopyBranch(hItem,mod, hParent, TVI_FIRST);
	m_Ids[hNewItem] = mod;
	m_wndMod.SelectItem(hNewItem);

	m_Ids.RemoveKey(hItem);
	m_wndMod.DeleteItem(hItem);

	m_wndMod.SetRedraw(TRUE);
}

void CDlgSysMod::OnUp()
{
	HTREEITEM hItem = m_wndMod.GetSelectedItem();
	if (!hItem)
		return;

	CSysMod mod;
	if (!m_Ids.Lookup(hItem, mod))
		return;

	HTREEITEM hParent = m_wndMod.GetParentItem(hItem);
	HTREEITEM hPrev = m_wndMod.GetPrevSiblingItem(hItem);

	if (!hPrev)
		return;

	HTREEITEM hPrevPrev = m_wndMod.GetPrevSiblingItem(hPrev);

	m_wndMod.SetRedraw(FALSE);

	HTREEITEM hNewItem = CopyBranch(hItem, mod, hParent, hPrevPrev == nullptr ? TVI_FIRST : hPrevPrev);
	m_Ids[hNewItem] = mod;
	m_wndMod.SelectItem(hNewItem);

	m_Ids.RemoveKey(hItem);
	m_wndMod.DeleteItem(hItem);

	m_wndMod.SetRedraw(TRUE);
}

void CDlgSysMod::OnDown()
{
	HTREEITEM hItem = m_wndMod.GetSelectedItem();
	if (!hItem)
		return;

	CSysMod mod;
	if (!m_Ids.Lookup(hItem, mod))
		return;

	HTREEITEM hParent = m_wndMod.GetParentItem(hItem);
	HTREEITEM hNext = m_wndMod.GetNextSiblingItem(hItem);

	if (!hNext)
		return;

	m_wndMod.SetRedraw(FALSE);

	HTREEITEM hNewItem = CopyBranch(hItem, mod, hParent, hNext);
	m_Ids[hNewItem] = mod;
	m_wndMod.SelectItem(hNewItem);

	m_Ids.RemoveKey(hItem);
	m_wndMod.DeleteItem(hItem);

	m_wndMod.SetRedraw(TRUE);
}

void CDlgSysMod::OnBottom()
{
	HTREEITEM hItem = m_wndMod.GetSelectedItem();
	if (!hItem)
		return;

	CSysMod mod;
	if (!m_Ids.Lookup(hItem, mod))
		return;

	HTREEITEM hParent = m_wndMod.GetParentItem(hItem);
	HTREEITEM hNext = m_wndMod.GetNextSiblingItem(hItem);

	if (!hNext)
		return;

	m_wndMod.SetRedraw(FALSE);

	HTREEITEM hNewItem = CopyBranch(hItem, mod, hParent, TVI_LAST);
	m_Ids[hNewItem] = mod;
	m_wndMod.SelectItem(hNewItem);

	m_Ids.RemoveKey(hItem);
	m_wndMod.DeleteItem(hItem);

	m_wndMod.SetRedraw(TRUE);
}

//保存
void CDlgSysMod::OnBnClickedOk()
{
	if (SaveModTree())
		CUserDialogBase::OnOK();
	else
	{
		CUserUtility::ShowMessageBox(_T("保存失败!"));
	}
}

bool CDlgSysMod::SaveModTree()
{
	HTREEITEM hRoot = m_wndMod.GetRootItem();

	CStringArray vSQL;

	CString csSQL;
	csSQL.Format(_T("TRUNCATE TABLE SYS_MODULE"));
	vSQL.Add(csSQL);

	int nOrder = 1;
	while (hRoot)
	{
		CSysMod mod;
		if (!m_Ids.Lookup(hRoot, mod))
			return false;

		csSQL.Format(_T("INSERT INTO SYS_MODULE (node_id,res_id,res_name,res_type,res_order) VALUES('%s','%s','%s','%s','%d')"),
			mod.m_csModID,
			mod.m_csResID,
			mod.m_csName,
			mod.m_csModType,
			nOrder);

		vSQL.Add(csSQL);

		//
		if (!SaveChildModTree(hRoot, mod.m_csModID,vSQL))
			return false;

		hRoot = m_wndMod.GetNextSiblingItem(hRoot);
		nOrder++;
	}

	return CUserManagerDataService::GetInstance()->SaveSysModeInfo(vSQL);
}

bool CDlgSysMod::SaveChildModTree(HTREEITEM hParent, const CString& csParent,CStringArray& vSQL)
{
	HTREEITEM hChild = m_wndMod.GetChildItem(hParent);
	int nOrder = 1;
	while (hChild)
	{
		CSysMod mod;
		if (!m_Ids.Lookup(hChild, mod))
			return false;

		CString csSQL;
		csSQL.Format(_T("INSERT INTO SYS_MODULE (node_id,res_id,res_name,res_type,res_order,parent_id) VALUES('%s','%s','%s','%s','%d','%s')"),
			mod.m_csModID,
			mod.m_csResID,
			mod.m_csName,
			mod.m_csModType,
			nOrder,
			csParent);
		vSQL.Add(csSQL);

		//
		if (!SaveChildModTree(hChild, mod.m_csModID, vSQL))
			return false;

		hChild = m_wndMod.GetNextSiblingItem(hChild);
		nOrder++;
	}
	return true;
}


