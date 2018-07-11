// Dlg_OrgInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_OrgInfo.h"
#include "resource.h"
#include "Dlg_AddOrg.h"
#include "../Utility/Utility.h"

#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm>  
using namespace std;


// CDlg_OrgInfo �Ի���

IMPLEMENT_DYNAMIC(CDlg_OrgInfo, CUserDialogBase)

CDlg_OrgInfo::CDlg_OrgInfo(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ORG_INFO, pParent)
{

}

CDlg_OrgInfo::~CDlg_OrgInfo()
{
}

void CDlg_OrgInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_USER_ORG, m_tOrgTree);
}


BEGIN_MESSAGE_MAP(CDlg_OrgInfo, CUserDialogBase)
	ON_NOTIFY(NM_CLICK, IDC_TREE_USER_ORG, &CDlg_OrgInfo::OnNMClickTreeUserOrg)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_USER_ORG, &CDlg_OrgInfo::OnNMRClickTreeUserOrg)
	ON_COMMAND(ID_ADD_ORG, &CDlg_OrgInfo::OnAddOrg)
	ON_COMMAND(ID_DEL_ORG, &CDlg_OrgInfo::OnDelOrg)
	ON_COMMAND(ID_UPDATE_ORG_NAME, &CDlg_OrgInfo::OnUpdateOrgName)

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_USER_ORG, &CDlg_OrgInfo::OnTvnSelchangedTreeUserOrg)
END_MESSAGE_MAP()


// CDlg_OrgInfo ��Ϣ�������
BOOL CDlg_OrgInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();


	std::shared_ptr<CDataTableMediator> pTable = CUserManagerDataService::GetInstance()->GetOrgInfo();

	//����������ؼ�
	FillBranchTree(pTable.get(), L"", TVI_ROOT);

	//�������ؼ����ŵ�ѡ�������ʾ������Ա
	ShowBranchUser();

	InitLayout();

	return TRUE;
}

void CDlg_OrgInfo::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_tOrgTree);

	UpdateLayout(layout);
}

void CDlg_OrgInfo::FillBranchTree(CDataTableMediator* pTable, CString sParentID, HTREEITEM hRoot)
{
	vector<CUserInfo> VecUserInfo;
	COrgInfo OrgInfo;
	if (!pTable)
		return;
	CString sFilter = L"";
	if (sParentID.Trim() == "")
		sFilter = L"Isnull(PARENT_ID,'')=''";
	else
		sFilter = L"PARENT_ID='" + sParentID + L"'";

	CDataTableMediator *pTempTable = pTable->FilterReturnTable(sFilter);
	if (!pTempTable)
		return;

	int iCount = pTempTable->GetRowCount();
	for (int i = 0; i < iCount; i++)
	{
		OrgInfo.SetDescription(pTempTable->GetStringField(i, L"DESCRIPTION"));
		OrgInfo.SetLeader(pTempTable->GetStringField(i, L"LEADER"));
		OrgInfo.SetLevel(pTempTable->GetStringField(i, L"ORG_LEVEL"));
		OrgInfo.SetOrgID(pTempTable->GetStringField(i, L"ORG_ID"));
		OrgInfo.SetOrgName(pTempTable->GetStringField(i, L"ORG_NAME"));
		OrgInfo.SetParentID(pTempTable->GetStringField(i, L"PARENT_ID"));
		OrgInfo.SetShortName(pTempTable->GetStringField(i, L"SHORT_NAME"));

		m_VecOrgInfo.push_back(OrgInfo);

		HTREEITEM hParent = m_tOrgTree.InsertItem(pTempTable->GetStringField(i, L"ORG_NAME"), hRoot);
		//m_tOrgTree.SetItemData(hParent, (DWORD_PTR)new CString(pTempTable->GetStringField(i, L"ORG_ID")));

		FillBranchTree(pTable, pTempTable->GetStringField(i, L"ORG_ID"), hParent);
	}
}

void CDlg_OrgInfo::ShowBranchUser()
{
	CPoint point;
	UINT uFlag;
	//��ȡ��Ļ�������
	GetCursorPos(&point);
	//ת���ɿͻ�����
	m_tOrgTree.ScreenToClient(&point);
	//������CtreeCtrl�����Ĺ��ĵ�ǰλ�ú;��
	HTREEITEM SelectItem = m_tOrgTree.HitTest(point, &uFlag);
	CString ItemText = m_tOrgTree.GetItemText(SelectItem);
	//����ѡ�еĽڵ� ��ȡ���Ŷ�Ӧ���û�
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetBranchUser());
	if (pTab)
	{
		int RowCount = pTab->GetRowCount();
		/*ͬʱɾ���к���*/
		m_GridCtrl.DeleteAllColumns();
		m_GridCtrl.RemoveAll();

		m_GridCtrl.InsertColumn(0, _T("�û�ID"), globalUtils.ScaleByDPI(60));
		m_GridCtrl.InsertColumn(1, _T("����ID"), globalUtils.ScaleByDPI(100));
		m_GridCtrl.InsertColumn(2, _T("�û�����"), globalUtils.ScaleByDPI(80));

		CBCGPGridRow* pRow;
		for (int i = 0; i < RowCount; i++)
		{
			pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

			/*�����к�*/
			pRow->GetItem(0)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_ID"));
			pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"ORG_ID"));
			pRow->GetItem(2)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_NAME"));

			m_GridCtrl.AddRow(pRow, FALSE);
		}
		m_GridCtrl.AdjustLayout();
	}
}


void CDlg_OrgInfo::OnTvnSelchangedTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}



void CDlg_OrgInfo::OnNMClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowBranchUser();

	*pResult = 0;
}


void CDlg_OrgInfo::OnNMRClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	//��̬���ز˵�  
	CMenu menu;
	menu.LoadMenu(IDR_MENU_ORG_OPERATION);
	CPoint pt;
	GetCursorPos(&pt);
	m_tOrgTree.ScreenToClient(&pt);   //��������Ļ���꣬ת�������οؼ��Ŀͻ�������  
	UINT uFlags = 0;
	m_hItem = m_tOrgTree.HitTest(pt, &uFlags); //Ȼ�����������  
	if ((m_hItem != NULL) && (TVHT_ONITEM & uFlags))     //��������λ�����ڽڵ�λ������  
		m_tOrgTree.SelectItem(m_hItem);
	else
		m_tOrgTree.SelectItem(NULL);

	//���ݲ�ͬ���͵Ľڵ㵯���˵�  
	CMenu *psubmenu;
	m_tOrgTree.ClientToScreen(&pt);
	psubmenu = menu.GetSubMenu(0);
	psubmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);

	*pResult = 0;
}


void CDlg_OrgInfo::OnAddOrg()
{
	CDlg_AddOrg dlg;
	dlg.SetOperateType(0);
	if (dlg.DoModal() == IDOK)
	{
		COrgInfo OrgInfo = dlg.GetOrgInfo();
		CString TreeNodeName;
		if (m_hItem == NULL)
		{
			TreeNodeName = L"";
			m_hItem = TVI_ROOT;
		}
		else
			TreeNodeName = m_tOrgTree.GetItemText(m_hItem);

		//ͨ���ڵ����Ʊ���vector
		vector<COrgInfo>::iterator it = m_VecOrgInfo.begin();
		for (; it != m_VecOrgInfo.end(); it++)
		{
			if (it->GetOrgName() == TreeNodeName)
				break;
		}
		//�ҵ���������ID��Ϊ�½����ŵĸ��ڵ�ID δ�ҵ������½����ŵĸ��ڵ���Ϊ��
		CString TempOrgID = L"";
		if (it != m_VecOrgInfo.end())
			TempOrgID = it->GetOrgID();

		//���ø��ڵ�
		OrgInfo.SetParentID(TempOrgID);

		//����ӵĲ��� ���������ݿ�
		CString OrgID = CUserUtility::GenerateUniqueStr(10);
		OrgInfo.SetOrgID(OrgID);
		BOOL Result = CUserManagerDataService::GetInstance()->InsertOrgInfo(OrgInfo);
		if (Result)
		{
			m_tOrgTree.InsertItem(OrgInfo.GetOrgName(), m_hItem);
			m_VecOrgInfo.push_back(OrgInfo);
		}
		else
			MessageBox(L"���ݲ���������ʧ��");
	}
}


void CDlg_OrgInfo::OnDelOrg()
{
	CString TreeNodeName = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());

	vector<COrgInfo>::iterator it = m_VecOrgInfo.begin();
	for (; it != m_VecOrgInfo.end(); it++)
	{
		if (it->GetOrgName() == TreeNodeName)
			break;
	}
	if (it != m_VecOrgInfo.end())
	{
		//ɾ�����ݿ�����
		BOOL Result1 = CUserManagerDataService::GetInstance()->DeleteOrgInfo(it->GetOrgID());
		CUserManagerDataService::GetInstance()->DeleteChildOrgInfo(it->GetOrgID());
		if (Result1)
		{
			m_tOrgTree.DeleteItem(m_tOrgTree.GetSelectedItem());
			m_VecOrgInfo.erase(it);
		}
		else
			MessageBox(L"���ݲ���������ʧ��");
	}
}


void CDlg_OrgInfo::OnUpdateOrgName()
{
	CDlg_AddOrg dlg;
	dlg.SetOperateType(1);
	//���ݽڵ����� ��ȡ�ڵ���Ϣ
	CString TreeNodeName = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());
	vector<COrgInfo>::iterator it = m_VecOrgInfo.begin();
	for (; it != m_VecOrgInfo.end(); it++)
	{
		if (it->GetOrgName() == TreeNodeName)
			break;
	}
	if (it != m_VecOrgInfo.end())
	{
		dlg.SetOrgInfo(*it);
		if (dlg.DoModal() == IDOK)
		{
			COrgInfo OrgInfo = dlg.GetOrgInfo();

			//�������ݿ�����
			BOOL Result = CUserManagerDataService::GetInstance()->UpdateOrgInfo(OrgInfo);
			if (Result)
			{
				m_tOrgTree.SetFocus();
				HTREEITEM hSel = m_tOrgTree.GetSelectedItem();
				CEdit* pEdit = m_tOrgTree.EditLabel(hSel);
				pEdit->SetWindowText(OrgInfo.GetOrgName());
				m_tOrgTree.SetItemText(hSel, OrgInfo.GetOrgName());
				*it = OrgInfo;
			}
			else
				MessageBox(L"���ݲ���������ʧ��");
		}
	}
}