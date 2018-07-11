// Dlg_UserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_UserInfo.h"
#include "resource.h"
#include "Dlg_AddOrg.h"
#include "Dlg_AddUser.h"

// CDlg_UserInfo �Ի���

IMPLEMENT_DYNAMIC(CDlg_UserInfo, CUserDialogBase)

CDlg_UserInfo::CDlg_UserInfo(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_USER_INFO, pParent)
{
}

CDlg_UserInfo::~CDlg_UserInfo()
{
}

void CDlg_UserInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CDlg_UserInfo, CUserDialogBase)
	ON_BN_CLICKED(IDC_BTN_ADD_USER, &CDlg_UserInfo::OnBnClickedBtnAddUser)
	ON_BN_CLICKED(IDC_BTN_DEL_USER, &CDlg_UserInfo::OnBnClickedBtnDelUser)
	ON_BN_CLICKED(IDC_BTN_UPDATE_USER, &CDlg_UserInfo::OnBnClickedBtnUpdateUser)
	ON_BN_CLICKED(IDC_BTN_USER_ALL_SELECT, &CDlg_UserInfo::OnBnClickedBtnUserAllSelect)
	ON_BN_CLICKED(IDC_BTN_REVERT, &CDlg_UserInfo::OnBnClickedBtnRevert)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK, OnDblClk)
END_MESSAGE_MAP()


// CDlg_UserInfo ��Ϣ�������
BOOL CDlg_UserInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	CRect rGridRect;
	GetDlgItem(IDC_STATIC_SHOW_USER)->GetWindowRect(rGridRect);
	ScreenToClient(rGridRect);

	if (!m_GridCtrl.Create(WS_CHILD | WS_VISIBLE, rGridRect, this, 100))
		return FALSE;

	m_GridCtrl.InsertColumn(0, _T("ѡ��"), globalUtils.ScaleByDPI(40));
	m_GridCtrl.InsertColumn(1, _T("�û�����"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(2, _T("��������"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(3, _T("�û��Ա�"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(4, _T("�û�ID"), globalUtils.ScaleByDPI(100));

	m_GridCtrl.EnableColumnAutoSize();
	m_GridCtrl.EnableRowHeader();
	m_GridCtrl.EnableLineNumbers();
	m_GridCtrl.SetWholeRowSel();
	m_GridCtrl.SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	m_GridCtrl.EnableHeader(TRUE, 0);
	m_GridCtrl.SetColumnVisible(4, FALSE);

	//��ѯ���ݿ��ȡ�û���Ϣ
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetBranchUser());

	CBCGPGridRow* pRow;
	for (int i = 0; i < pTab->GetRowCount(); i++)
	{
		pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

		CString OrgID = pTab->GetStringField(i, L"ORG_ID");
		/** ���ݲ���ID��ȡ��Ϣ */
		std::shared_ptr<CDataTableMediator> pTableOrg(CUserManagerDataService::GetInstance()->GetOrgInfoUseOrgID(OrgID));
		/*�����к�*/
		pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
		pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_NAME"));
		pRow->GetItem(2)->SetValue((_variant_t)pTableOrg->GetStringField(0, L"ORG_NAME"));
		pRow->GetItem(3)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_SEX"));
		pRow->GetItem(4)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_ID"));

		for (int j = 1; j <= 3; j++)
		{
			pRow->GetItem(j)->AllowEdit(FALSE);
			pRow->GetItem(j)->SetReadOnly(TRUE);
		}

		m_GridCtrl.AddRow(pRow, FALSE);
	}

	m_GridCtrl.AdjustLayout();

	InitLayout();

	return TRUE;
}



void CDlg_UserInfo::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_GridCtrl)
		<< (pane(HORIZONTAL)
			<< item(IDC_BTN_USER_ALL_SELECT, NORESIZE)
			<< item(IDC_BTN_REVERT, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_BTN_ADD_USER, NORESIZE)
			<< item(IDC_BTN_DEL_USER, NORESIZE)
			<< item(IDC_BTN_UPDATE_USER, NORESIZE));

	UpdateLayout(layout);
}


void CDlg_UserInfo::OnBnClickedBtnAddUser()
{
	CDlg_AddUser dlg;
	std::shared_ptr<CDataTableMediator> pTab = CUserManagerDataService::GetInstance()->GetOrgInfo();

	dlg.SetOperatorType(0);

	CString UserID = CUserUtility::GenerateUniqueStr(10);
	dlg.SetUserID(UserID);
	if (pTab)
		dlg.SetOrgInfo(pTab.get());
	if (dlg.DoModal() == IDOK)
	{
		CUserInfo UserInfo = dlg.GetUserInfo();

		///����û���Ϣ
		BOOL Result = CUserManagerDataService::GetInstance()->InsertUserInfo(UserInfo);

		///����û�--��ɫ������:
		BOOL ResultRole = TRUE;
		vector<CString> UserRole = dlg.GetUserRoleId();
		for (int i = 0; i < UserRole.size(); i++)
		{
			ResultRole = CUserManagerDataService::GetInstance()->InsertUserRoleInfo(UserInfo.GetUserID(), UserRole[i]);
			if (!ResultRole)
				break;
		}

		if (Result && ResultRole)
		{
			CBCGPGridRow* pRow;
			pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

			pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
			pRow->GetItem(1)->SetValue((_variant_t)UserInfo.GetUserNames());
			pRow->GetItem(2)->SetValue((_variant_t)UserInfo.GetOrgName());
			pRow->GetItem(3)->SetValue((_variant_t)UserInfo.GetUserSex());
			pRow->GetItem(4)->SetValue((_variant_t)UserInfo.GetUserID());

			for (int j = 1; j <= 3; j++)
			{
				pRow->GetItem(j)->AllowEdit(FALSE);
				pRow->GetItem(j)->SetReadOnly(TRUE);
			}

			m_GridCtrl.AddRow(pRow, FALSE);
			m_GridCtrl.AdjustLayout();
		}
		else
			MessageBox(L"���ݲ���������ʧ��");
	}
}


void CDlg_UserInfo::OnBnClickedBtnDelUser()
{
	CString UserID = L"";
	CBCGPGridRow* pCurSelRow = m_GridCtrl.GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"ɾ������û��ѡ��ɾ������");
	}
	else
	{
		for (int i = m_GridCtrl.GetRowCount() - 1; i >= 0; i--)
		{
			pCurSelRow = m_GridCtrl.GetRow(i);
			if (((CBCGPGridCheckItem*)pCurSelRow->GetItem(0))->GetState() == 1)
			{
				UserID = pCurSelRow->GetItem(4)->GetValue();

				BOOL Result = CUserManagerDataService::GetInstance()->DeleteUserInfo(UserID);
				if (Result)
					m_GridCtrl.RemoveRow(i);
				else
					MessageBox(L"���ݲ���������ʧ��");
			}
		}
	}
}


void CDlg_UserInfo::OnBnClickedBtnUpdateUser()
{
	CBCGPGridRow* pRow = NULL;
	int i;
	CBCGPGridRow* pCurSelRow = m_GridCtrl.GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"û��ѡ��ɾ������");
	}
	else
	{
		for (i = m_GridCtrl.GetRowCount() - 1; i >= 0; i--)
		{
			pCurSelRow = m_GridCtrl.GetRow(i);
			if (((CBCGPGridCheckItem*)pCurSelRow->GetItem(0))->GetState() == 1)
			{
				pRow = m_GridCtrl.GetRow(i);
				break;
			}
		}
	}
	if (pRow == NULL)
	{
		MessageBox(_T("��ѡ��һ������"));
		return;
	}

	EditInfo(pRow);
}


void CDlg_UserInfo::EditInfo(CBCGPGridRow* pRow)
{
	CDlg_AddUser dlg;
	CUserInfo UserInfo;

	CString UserID = L"";
	UserID = pRow->GetItem(4)->GetValue();
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetUserInfoUserUserID(UserID));
	if (pTab)
	{
		UserInfo.SetUserID(pTab->GetStringField(0, L"USER_ID"));
		UserInfo.SetOrgID(pTab->GetStringField(0, L"ORG_ID"));
		UserInfo.SetUserName(pTab->GetStringField(0, L"USER_NAME"));
		UserInfo.SetUserSex(pTab->GetStringField(0, L"USER_SEX"));
		UserInfo.SetUserPw(pTab->GetStringField(0, L"USER_PASSWORD"));
		UserInfo.SetUserEmail(pTab->GetStringField(0, L"USER_EMAIL"));
		UserInfo.SetUserTelephone(pTab->GetStringField(0, L"USER_TELEPHONE"));
		UserInfo.SetUserFax(pTab->GetStringField(0, L"USER_FAX"));
		UserInfo.SetUserMobile(pTab->GetStringField(0, L"USER_MOBILE"));
		UserInfo.SetUserQQ(pTab->GetStringField(0, L"USER_QQ"));
		UserInfo.SetUserMSN(pTab->GetStringField(0, L"USER_MSN"));
		UserInfo.SetDescription(pTab->GetStringField(0, L"DESCRIPTION"));

	}

	CString TreeNodeName;// = m_tOrgTree.GetItemText(m_tOrgTree.GetSelectedItem());
	dlg.SetOperatorType(1);
	dlg.SetUserInfo(UserInfo);
	UserID = UserInfo.GetUserID();
	dlg.SetUserID(UserID);
	CString OrgName = _T("");
	std::shared_ptr<CDataTableMediator> pTabOrg(CUserManagerDataService::GetInstance()->GetOrgInfoUseOrgID(UserInfo.GetOrgID()));
	dlg.SetOrgName(pTabOrg->GetStringField(0, L"ORG_NAME"));

	if (dlg.DoModal() == IDOK)
	{
		CUserInfo UserInfo = dlg.GetUserInfo();

		///�����û���Ϣ
		BOOL Result = CUserManagerDataService::GetInstance()->UpdateUserInfo(UserInfo);

		if (Result)
		{
			pRow->ReplaceItem(0, new CBCGPGridCheckItem(TRUE));
			pRow->GetItem(1)->SetValue((_variant_t)UserInfo.GetUserNames());
			pRow->GetItem(2)->SetValue((_variant_t)UserInfo.GetOrgName());
			pRow->GetItem(3)->SetValue((_variant_t)UserInfo.GetUserSex());
			pRow->GetItem(4)->SetValue((_variant_t)UserInfo.GetUserID());

			m_GridCtrl.AdjustLayout();
		}
		else
			MessageBox(L"���ݲ���������ʧ��");
	}
}


void CDlg_UserInfo::OnBnClickedBtnUserAllSelect()
{
	for (int i = 0; i < m_GridCtrl.GetRowCount(); i++)
	{
		CBCGPGridRow* pRow = m_GridCtrl.GetRow(i);
		((CBCGPGridCheckItem*)(pRow->GetItem(0)))->SetValue(true);
	}
}


void CDlg_UserInfo::OnBnClickedBtnRevert()
{
	for (int i = 0; i < m_GridCtrl.GetRowCount(); i++)
	{
		CBCGPGridRow* pRow = m_GridCtrl.GetRow(i);

		bool bVal = ((CBCGPGridCheckItem*)(pRow->GetItem(0)))->GetValue();
		((CBCGPGridCheckItem*)(pRow->GetItem(0)))->SetValue(!bVal);
	}
}


LRESULT CDlg_UserInfo::OnDblClk(WPARAM wParam, LPARAM lParam)
{
	CBCGPGridItem* pItem = (CBCGPGridItem*)(lParam);

	if (!pItem)
		return 0L;
	
	CBCGPGridRow* pRow = pItem->GetParentRow();
	int Line = pRow->GetLinesNumber();
	EditInfo(pRow);

	return 1L;
}


