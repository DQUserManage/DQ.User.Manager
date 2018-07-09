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

	m_GridCtrl.EnableMarkSortedColumn(FALSE);
	m_GridCtrl.EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	m_GridCtrl.EnableRowHeader(TRUE);
	m_GridCtrl.EnableLineNumbers();
	m_GridCtrl.SetClearInplaceEditOnEnter(FALSE);
	m_GridCtrl.EnableInvertSelOnCtrl();
	m_GridCtrl.SetScalingRange(0.1, 4.0);

	m_GridCtrl.InsertColumn(0, _T("ѡ��"), globalUtils.ScaleByDPI(40));
	m_GridCtrl.InsertColumn(1, _T("�û�ID"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(2, _T("����ID"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(3, _T("�û�����"), globalUtils.ScaleByDPI(100));

	//��ѯ���ݿ��ȡ�û���Ϣ
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetBranchUser());

	CBCGPGridRow* pRow;
	for (int i = 0; i < pTab->GetRowCount(); i++)
	{
		pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

		/*�����к�*/
		pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
		pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_ID"));
		pRow->GetItem(2)->SetValue((_variant_t)pTab->GetStringField(i, L"ORG_ID"));
		pRow->GetItem(3)->SetValue((_variant_t)pTab->GetStringField(i, L"USER_NAME"));

		m_GridCtrl.AddRow(pRow, FALSE);
	}

	m_GridCtrl.AdjustLayout();

	return TRUE;
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
		BOOL ResultRole;
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
			pRow->GetItem(1)->SetValue((_variant_t)UserInfo.GetUserID());
			pRow->GetItem(2)->SetValue((_variant_t)UserInfo.GetOrgID());
			pRow->GetItem(3)->SetValue((_variant_t)UserInfo.GetUserNames());

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
				UserID = m_GridCtrl.GetRow(i)->GetItem(1)->GetValue();

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
	CDlg_AddUser dlg;

	CBCGPGridRow* pRow = NULL;
	CUserInfo UserInfo;
	CString UserID = L"";
	CBCGPGridRow* pCurSelRow = m_GridCtrl.GetCurSel();
	if (pCurSelRow == NULL)
	{
		MessageBox(L"û��ѡ��ɾ������");
	}
	else
	{
		for (int i = m_GridCtrl.GetRowCount() - 1; i >= 0; i--)
		{
			if (m_GridCtrl.IsRowSelected(i))
			{
				UserID = m_GridCtrl.GetRow(i)->GetItem(1)->GetValue();
				pRow = m_GridCtrl.GetRow(i);
				break;
			}
		}
	}

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
			pRow->GetItem(1)->SetValue((_variant_t)UserInfo.GetUserID());
			pRow->GetItem(2)->SetValue((_variant_t)UserInfo.GetOrgID());
			pRow->GetItem(3)->SetValue((_variant_t)UserInfo.GetUserNames());

			m_GridCtrl.AdjustLayout();
		}
		else
			MessageBox(L"���ݲ���������ʧ��");
	}


}


