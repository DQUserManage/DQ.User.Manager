// Dlg_RoleInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_RoleInfo.h"
#include "resource.h"
#include "Dlg_AddRoleInfo.h"


// CDlg_RoleInfo �Ի���

IMPLEMENT_DYNAMIC(CDlg_RoleInfo, CUserDialogBase)

CDlg_RoleInfo::CDlg_RoleInfo(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ROLE_INFO, pParent)
{

}

CDlg_RoleInfo::~CDlg_RoleInfo()
{
}

void CDlg_RoleInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlg_RoleInfo, CUserDialogBase)
	ON_BN_CLICKED(IDC_BTN_ADD_ROLE, &CDlg_RoleInfo::OnBnClickedBtnAddRole)
	ON_BN_CLICKED(IDC_BTN_DEL_ROLE, &CDlg_RoleInfo::OnBnClickedBtnDelRole)
	ON_BN_CLICKED(IDC_BTN_UPDATE_ROLE_INFO, &CDlg_RoleInfo::OnBnClickedBtnUpdateRoleInfo)
	ON_BN_CLICKED(IDC_BTN_ROLE_ALL_SELECT, &CDlg_RoleInfo::OnBnClickedBtnRoleAllSelect)
	ON_BN_CLICKED(IDC_BTN_ROLE_REVERT, &CDlg_RoleInfo::OnBnClickedBtnRoleRevert)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK, OnDblClk)
END_MESSAGE_MAP()


// CDlg_RoleInfo ��Ϣ�������
BOOL CDlg_RoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	CRect rGridRect;
	GetDlgItem(IDC_STATIC_SHOW_ROLE)->GetWindowRect(rGridRect);
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
	m_GridCtrl.InsertColumn(1, _T("��ɫID"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(2, _T("��ɫ"), globalUtils.ScaleByDPI(100));
	m_GridCtrl.InsertColumn(3, _T("��ע"), globalUtils.ScaleByDPI(100));

	//��ѯ���ݿ��ȡ�û���Ϣ
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetRoleInfo());

	CBCGPGridRow* pRow;
	for (int i = 0; i < pTab->GetRowCount(); i++)
	{
		pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

		/*�����к�*/
		pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
		pRow->GetItem(1)->SetValue((_variant_t)pTab->GetStringField(i, L"ROLE_ID"));
		pRow->GetItem(2)->SetValue((_variant_t)pTab->GetStringField(i, L"ROLE_NAME"));
		pRow->GetItem(3)->SetValue((_variant_t)pTab->GetStringField(i, L"DESCRIPTION"));

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


void CDlg_RoleInfo::InitLayout()
{
	CPane layout = pane(VERTICAL)
		<< item(&m_GridCtrl)
		<< (pane(HORIZONTAL)
			<< item(IDC_BTN_ROLE_ALL_SELECT, NORESIZE)
			<< item(IDC_BTN_ROLE_REVERT, NORESIZE)
			<< itemGrowing(HORIZONTAL)
			<< item(IDC_BTN_ADD_ROLE, NORESIZE)
			<< item(IDC_BTN_DEL_ROLE, NORESIZE)
			<< item(IDC_BTN_UPDATE_ROLE_INFO, NORESIZE));
			
	UpdateLayout(layout);
}


void CDlg_RoleInfo::OnBnClickedBtnAddRole()
{
	CDlg_AddRoleInfo dlg;
	dlg.SetOperateType(0);
	if (dlg.DoModal() == IDOK)
	{
		vector<CString> RolePower = dlg.GetRolePower();
		CString RoleID = CUserUtility::GenerateUniqueStr(10);

		CRoleInfo RoleInfo = dlg.GetRoleInfo();

		RoleInfo.SetRoleID(RoleID);

		//��ӽ�ɫ������
		BOOL Result = CUserManagerDataService::GetInstance()->InsertRoleInfo(RoleInfo);

		BOOL ResultPower = TRUE;
		//��ӽ�ɫ--Ȩ�� TODO:
		for (int i = 0; i < RolePower.size(); i++)
		{
			ResultPower = CUserManagerDataService::GetInstance()->InsertPowerRoleInfo(RoleInfo, RolePower[i]);
			if (!ResultPower)
				break;
		}

		if (Result && ResultPower)
		{
			CBCGPGridRow* pRow;
			pRow = m_GridCtrl.CreateRow(m_GridCtrl.GetColumnCount());

			/*�����к�*/
			pRow->ReplaceItem(0, new CBCGPGridCheckItem(FALSE));
			pRow->GetItem(1)->SetValue((_variant_t)RoleInfo.GetRoleID());
			pRow->GetItem(2)->SetValue((_variant_t)RoleInfo.GetRoleName());
			pRow->GetItem(3)->SetValue((_variant_t)RoleInfo.GetRemark());

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


void CDlg_RoleInfo::OnBnClickedBtnDelRole()
{
	CString RoleID = L"";
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
				RoleID = m_GridCtrl.GetRow(i)->GetItem(1)->GetValue();

				BOOL Result = CUserManagerDataService::GetInstance()->DeleteRoleInfo(RoleID);
				if (Result)
					m_GridCtrl.RemoveRow(i);
				else
					MessageBox(L"���ݲ���������ʧ��");
			}
		}
	}
}


void CDlg_RoleInfo::OnBnClickedBtnUpdateRoleInfo()
{
	CBCGPGridRow* pRow = NULL;
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


void CDlg_RoleInfo::OnBnClickedBtnRoleAllSelect()
{
	for (int i = 0; i < m_GridCtrl.GetRowCount(); i++)
	{
		CBCGPGridRow* pRow = m_GridCtrl.GetRow(i);
		((CBCGPGridCheckItem*)(pRow->GetItem(0)))->SetValue(true);
	}
}


void CDlg_RoleInfo::OnBnClickedBtnRoleRevert()
{
	for (int i = 0; i < m_GridCtrl.GetRowCount(); i++)
	{
		CBCGPGridRow* pRow = m_GridCtrl.GetRow(i);

		bool bVal = ((CBCGPGridCheckItem*)(pRow->GetItem(0)))->GetValue();
		((CBCGPGridCheckItem*)(pRow->GetItem(0)))->SetValue(!bVal);
	}
}


LRESULT CDlg_RoleInfo::OnDblClk(WPARAM wParam, LPARAM lParam)
{
	CBCGPGridItem* pItem = (CBCGPGridItem*)(lParam);

	if (!pItem)
		return 0L;

	CBCGPGridRow* pRow = pItem->GetParentRow();
	EditInfo(pRow);

	return 1L;
}


void CDlg_RoleInfo::EditInfo(CBCGPGridRow* pRow)
{
	CDlg_AddRoleInfo dlg;
	dlg.SetOperateType(1);

	CString RoleID = L"";
	RoleID = pRow->GetItem(1)->GetValue();
	std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetRoleInfoUseID(RoleID));

	CRoleInfo RoleInfo;
	RoleInfo.SetRoleID(pTab->GetStringField(0, L"ROLE_ID"));
	RoleInfo.SetRoleName(pTab->GetStringField(0, L"ROLE_NAME"));
	RoleInfo.SetRemark(pTab->GetStringField(0, L"DESCRIPTION"));

	dlg.SerRoleInfo(RoleInfo);
	if (dlg.DoModal() == IDOK)
	{
		//��������
		vector<CString> RolePower = dlg.GetRolePower();

		RoleInfo = dlg.GetRoleInfo();

		//���½�ɫ��Ϣ
		BOOL Result = CUserManagerDataService::GetInstance()->UpdateRoleInfo(RoleInfo);

		//���½�ɫ--Ȩ�� �û���ɫ:
		for (int i = 0; i < RolePower.size(); i++)
		{
			//��ɾ�������
			Result = CUserManagerDataService::GetInstance()->DelPowerRoleInfo(RoleInfo);
			Result = CUserManagerDataService::GetInstance()->InsertPowerRoleInfo(RoleInfo, RolePower[i]);
			if (!Result)
				break;
		}

		if (Result)
		{
			/*�����к�*/
			pRow->ReplaceItem(0, new CBCGPGridCheckItem(TRUE));
			pRow->GetItem(1)->SetValue((_variant_t)RoleInfo.GetRoleID());
			pRow->GetItem(2)->SetValue((_variant_t)RoleInfo.GetRoleName());
			pRow->GetItem(3)->SetValue((_variant_t)RoleInfo.GetRemark());

			m_GridCtrl.AdjustLayout();
		}
		else
			MessageBox(L"���ݲ���������ʧ��");

	}
}


