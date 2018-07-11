// Dlg_AddRoleInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg_AddRoleInfo.h"
#include "resource.h"


// CDlg_AddRoleInfo �Ի���

IMPLEMENT_DYNAMIC(CDlg_AddRoleInfo, CUserDialogBase)

CDlg_AddRoleInfo::CDlg_AddRoleInfo(CWnd* pParent /*=NULL*/)
	: CUserDialogBase(IDD_DLG_ADD_ROLE, pParent)
{
	m_OperateType = -1;
}

CDlg_AddRoleInfo::~CDlg_AddRoleInfo()
{
}

void CDlg_AddRoleInfo::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROLE_NAME, m_eRoleName);
	DDX_Control(pDX, IDC_TREE_ROLE_POWER, m_wndMod);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_eDescription);
}


BEGIN_MESSAGE_MAP(CDlg_AddRoleInfo, CUserDialogBase)
	ON_BN_CLICKED(IDOK, &CDlg_AddRoleInfo::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ROLE_POWER, &CDlg_AddRoleInfo::OnNMClickTreeRolePower)
END_MESSAGE_MAP()


// CDlg_AddRoleInfo ��Ϣ�������
BOOL CDlg_AddRoleInfo::OnInitDialog()
{
	CUserDialogBase::OnInitDialog();

	//��ʼ����ɫȨ��
	std::vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(_T(""), vMode);
	for (size_t i = 0; i < vMode.size(); i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hRoot = m_wndMod.InsertItem(info.m_csName, TVI_ROOT);

		m_wndMod.SetItemData(hRoot, (DWORD_PTR)new CString(info.m_csModID));
		FillModeTree(hRoot, info.m_csModID);
	}


	//�޸Ľ�ɫ��Ϣʱ ��ʼ��ѡ��
	if (m_OperateType == 1)
	{
		this->SetWindowText(_T("�޸Ľ�ɫ��Ϣ"));

		m_eRoleName.SetWindowText(m_RoleInfo.GetRoleName());
		m_eDescription.SetWindowText(m_RoleInfo.GetRemark());
		
		//��ѯ��ɫ��Ӧģ��
		std::shared_ptr<CDataTableMediator> pTab(CUserManagerDataService::GetInstance()->GetSysModeInfoUseRoleId(m_RoleInfo.GetRoleID()));

		if (pTab->GetRowCount() > 0)
		{
			m_wndMod.ModifyStyle(TVS_CHECKBOXES, 0);
			m_wndMod.ModifyStyle(0, TVS_CHECKBOXES);

			HTREEITEM hParent = m_wndMod.GetFirstVisibleItem();
			SetTreeNodeSel(pTab.get(), L"", hParent);
		}
	}
	else
		this->SetWindowText(_T("��ӽ�ɫ��Ϣ"));

	return TRUE;
}


/** �������ڵ�ѡ�� */
void	CDlg_AddRoleInfo::SetTreeNodeSel(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot)
{
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

	CString sName = L"";
	CString sItemText = L"";
	int iCount = pTempTable->GetRowCount();
	for (int i = 0; i < iCount; i++)
	{
		sName = pTempTable->GetStringField(i, L"RES_NAME");
		HTREEITEM hTemp = hRoot;
		while (hTemp)
		{
			sItemText = m_wndMod.GetItemText(hTemp);
			if (sName == sItemText)
			{
				BOOL bCheck = m_wndMod.GetCheck(hTemp);     //��ȡ��ǰ��ѡ״̬
				m_wndMod.SetCheck(hTemp);
				bCheck = m_wndMod.GetCheck(hTemp);     //��ȡ��ǰ��ѡ״̬

				SetTreeNodeSel(pTable, pTempTable->GetStringField(i, L"NODE_ID"), m_wndMod.GetChildItem(hTemp));
				break;
			}
			hTemp = m_wndMod.GetNextSiblingItem(hTemp);
		}
	}
}


void CDlg_AddRoleInfo::FillModeTree(HTREEITEM hParent, const CString& csParent)
{
	std::vector<CSysMod> vMode;
	CUserManagerDataService::GetInstance()->GetSysModeNode(csParent, vMode);
	for (size_t i = 0; i < vMode.size(); i++)
	{
		CSysMod& info = vMode[i];

		HTREEITEM hItem = m_wndMod.InsertItem(info.m_csName, hParent);

		m_wndMod.SetItemData(hItem, (DWORD_PTR)new CString(info.m_csModID));
		FillModeTree(hItem, info.m_csModID);
	}
}


void CDlg_AddRoleInfo::OnBnClickedOk()
{
	CString RoleName, Description;

	m_eRoleName.GetWindowText(RoleName);
	m_eDescription.GetWindowText(Description);

	m_RoleInfo.SetRoleName(RoleName);
	m_RoleInfo.SetRemark(Description);

	HTREEITEM pRoot = m_wndMod.GetFirstVisibleItem();
	GetSelChildNode(&m_pCurRola, pRoot);

	CUserDialogBase::OnOK();
}

/** ��ȡѡ�е�Ҷ�ڵ� */
void	CDlg_AddRoleInfo::GetSelChildNode(vector<CString>* pRola, HTREEITEM pRoot)
{
	CString *pData = NULL;
	while (pRoot)
	{
		HTREEITEM pChild = m_wndMod.GetChildItem(pRoot);
		if (!pChild)
		{
			if (m_wndMod.GetCheck(pRoot) == 1)
			{
				pData = (CString *)m_wndMod.GetItemData(pRoot);
				if (pData)
				{
					pRola->push_back(*pData);
				}
			}
		}
		else
			GetSelChildNode(pRola, pChild);
		// ��ȡ��һ���ֵܽڵ�
		pRoot = m_wndMod.GetNextSiblingItem(pRoot);
	}
}


void CDlg_AddRoleInfo::OnNMClickTreeRolePower(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	UINT uFlag;   //�����йص�����Ե���Ϣ������
	HTREEITEM hTree;
	BOOL bCheck;
	GetCursorPos(&point);    //��ȡ��Ļ�������
	m_wndMod.ScreenToClient(&point);           //ת���ɿͻ�����
	hTree = m_wndMod.HitTest(point, &uFlag);    //������CtreeCtrl�����Ĺ��ĵ�ǰλ�ú;��

	if (hTree && (TVHT_ONITEMSTATEICON & uFlag))	//���и�ѡ��
	{
		m_wndMod.SelectItem(hTree);
		BOOL bCheckParent = TRUE;
		bCheck = m_wndMod.GetCheck(hTree);     //��ȡ��ǰ��ѡ״̬
		if (bCheck)
		{
			HTREEITEM hSiblingItem = m_wndMod.GetNextSiblingItem(hTree);
			while (hSiblingItem)
			{
				if (m_wndMod.GetCheck(hSiblingItem))
				{
					bCheckParent = FALSE;
					break;
				}
				hSiblingItem = m_wndMod.GetNextSiblingItem(hSiblingItem);
			}
			if (bCheckParent)
			{
				hSiblingItem = m_wndMod.GetPrevSiblingItem(hTree);
				while (hSiblingItem)
				{
					if (m_wndMod.GetCheck(hSiblingItem))
					{
						bCheckParent = FALSE;
						break;
					}
					hSiblingItem = m_wndMod.GetPrevSiblingItem(hSiblingItem);
				}
			}
		}
		if (bCheckParent)
			SetParentCheck(hTree, !bCheck);				// ���ø��ѡ
		SetChildCheck(hTree, !bCheck);               //�������ѡ״̬
	}

	*pResult = 0;
}


/** ���ø��ڵ�ѡ�� */
void	CDlg_AddRoleInfo::SetParentCheck(HTREEITEM hTree, BOOL bCheck)
{
	hTree = m_wndMod.GetParentItem(hTree);  //��ȡ������
	if (hTree)
	{
		m_wndMod.SetCheck(hTree, bCheck);
		SetParentCheck(hTree, bCheck);     //�ݹ����
	}
}

/** �����ӽڵ�ѡ�� */
void	CDlg_AddRoleInfo::SetChildCheck(HTREEITEM hTree, BOOL bCheck)
{
	hTree = m_wndMod.GetChildItem(hTree);  //��ȡ������
	while (hTree)
	{
		m_wndMod.SetCheck(hTree, bCheck);
		SetChildCheck(hTree, bCheck);     //�ݹ����
		hTree = m_wndMod.GetNextSiblingItem(hTree);    //��ȡ�ֵܵľ��
	}
}

